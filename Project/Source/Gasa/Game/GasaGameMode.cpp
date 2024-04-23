#include "GasaGameMode.h"

#include "Online/CoreOnline.h"
#include "GasaGameInstance.h"
#include "GasaGameState.h"
#include "GasaPlayerController.h"
#include "Engine/Player.h"
#include "GameFramework/GameSession.h"
#include "GameFramework/GameState.h"
#include "GameFramework/PlayerState.h"
#include "OnlineSubsystem.h"
using namespace Gasa;

#pragma region Game Framework
void AGasaGameMode::OnGameFrameworkInitialized()
{
	NetLog("OnGameFrameworkInitialized");
	
	BP_OnGameFrameworkInitialized();
	if (MatchState == MatchState::WaitingToStart && ReadyToStartMatch())
		StartMatch();
}

void AGasaGameMode::OwningClient_OnGameFrameworkInitialized(AGasaPlayerController* PC)
{
	NetLog("OwningClient_OnGameFrameworkInitialized");
	HandleStartingNewPlayer(PC);
}
#pragma endregion Game Framework

#pragma region GameMode
void AGasaGameMode::HandleStartingNewPlayer_Implementation(APlayerController* NewPlayer)
{
	Super::HandleStartingNewPlayer_Implementation(NewPlayer);
	if (NewPlayer)
		NewPlayer->bBlockInput = false;
}

bool AGasaGameMode::ReadyToStartMatch_Implementation()
{
	if ( ! GetGameInstance<UGasaGameInstance>()->IsGameFrameworkInitialized()) 
	{
		return false;
	}
	
	// Super::ReadyToStartMatch();
	{
		// If bDelayed Start is set, wait for a manual match start
		if (bDelayedStart)
		{
			return false;
		}

		// By default start when we have > 0 players
		if (GetMatchState() == MatchState::WaitingToStart)
		{
			if (NumPlayers + NumBots > 0)
			{
				return true;
			}
		}
		return false;
	}
}
#pragma endregion GameMode

#pragma region GameModeBase
void AGasaGameMode::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	NetLog("EndPlay");
}

void AGasaGameMode::FinishRestartPlayer(AController* NewPlayer, const FRotator& StartRotation)
{
	// Super::FinishRestartPlayer(NewPlayer, StartRotation);
	{
		NewPlayer->Possess(NewPlayer->GetPawn());

		// If the Pawn is destroyed as part of possession we have to abort
		if (!IsValid(NewPlayer->GetPawn()))
		{
			FailedToRestartPlayer(NewPlayer);
		}
		else
		{
			// Set initial control rotation to starting rotation rotation
			NewPlayer->ClientSetRotation(NewPlayer->GetPawn()->GetActorRotation(), true);

			FRotator NewControllerRot = StartRotation;
			NewControllerRot.Roll = 0.f;
			NewPlayer->SetControlRotation(NewControllerRot);

			SetPlayerDefaults(NewPlayer->GetPawn());

			K2_OnRestartPlayer(NewPlayer);
		}
	}
}

void AGasaGameMode::GenericPlayerInitialization(AController* C)
{
	NetLog("GenericPlayerInitialization: " + C->GetName());
	
	// AGameMode::GenericPlayerInitialization(C);
	{
		APlayerController* PC = Cast<APlayerController>(C);
		if (PC != nullptr)
		{
			// Moved to: void AGasaGameMode::SetPlayerDefaults(APawn* PlayerPawn)
			// InitializeHUDForPlayer(Cast<APlayerController>(C));
				
			// Notify the game that we can now be muted and mute others
			UpdateGameplayMuteList(PC);

			if (GameSession != nullptr)
			{
				// Tell the player to enable voice by default or use the push to talk method
				PC->ClientEnableNetworkVoice(!GameSession->RequiresPushToTalk());
			}

			ReplicateStreamingStatus(PC);

			bool HidePlayer = false, HideHUD = false, DisableMovement = false, DisableTurning = false;

			// Check to see if we should start in cinematic mode (matinee movie capture)
			if (ShouldStartInCinematicMode(PC, HidePlayer, HideHUD, DisableMovement, DisableTurning))
			{
				PC->SetCinematicMode(true, HidePlayer, HideHUD, DisableMovement, DisableTurning);
			}
		}
	}
}

TSubclassOf<APlayerController> AGasaGameMode::GetPlayerControllerClassToSpawnForSeamlessTravel(APlayerController* PreviousPlayerController)
{
	NetLog("GetPlayerControllerClassToSpawnForSeamlessTravel: " + PreviousPlayerController->GetName());
	return Super::GetPlayerControllerClassToSpawnForSeamlessTravel(PreviousPlayerController);
}

void AGasaGameMode::HandleSeamlessTravelPlayer(AController*& Controller)
{
	NetLog("HandleSeamlessTravelPlayer: " + Controller->GetName());
	
	// Super::HandleSeamlessTravelPlayer( C );

	UE_LOG(LogGameMode, Log, TEXT(">> GameMode::HandleSeamlessTravelPlayer: %s "), * Controller->GetName());

	APlayerController* PC             = Cast<APlayerController>(Controller);
	UClass*            PCClassToSpawn = GetPlayerControllerClassToSpawnForSeamlessTravel(PC);
	// FUniqueNetIdRepl StoredNativePlatformUniqueNetId = C->GetPlayerState<AGasaPlayerState>()->NativePlatformUniqueNetId;

	if (PC && PC->GetClass() != PCClassToSpawn)
	{
		if (PC->Player != nullptr)
		{
			// We need to spawn a new PlayerController to replace the old one
			APlayerController* const NewPC = SpawnPlayerControllerCommon(PC->IsLocalPlayerController()
				? ROLE_SimulatedProxy
				: ROLE_AutonomousProxy, PC->GetFocalLocation(), PC->GetControlRotation(), PCClassToSpawn);
			if (NewPC == nullptr)
			{
				NetLog(FString::Printf(
					TEXT("Failed to spawn new PlayerController for %s (old class %s)"), *PC->GetHumanReadableName(), *PC->GetClass()->GetName())
					, ELogV::Warning
				);
				PC->Destroy();
				return;
			}
			else
			{
				PC->SeamlessTravelTo(NewPC);
				NewPC->SeamlessTravelFrom(PC);
				SwapPlayerControllers(PC, NewPC);
				PC = NewPC;
				Controller = NewPC;
			}
		}
		else
		{
			PC->Destroy();
		}
	}
	else
	{
		// clear out data that was only for the previous game
		Controller->PlayerState->Reset();
		// create a new PlayerState and copy over info; this is necessary because the old GameMode may have used a different PlayerState class
		APlayerState* OldPlayerState = Controller->PlayerState;
		Controller->InitPlayerState();
		OldPlayerState->SeamlessTravelTo( Controller->PlayerState);
		// we don"t need the old PlayerState anymore
		//@fixme: need a way to replace PlayerStates that doesn't cause incorrect "player left the game"/"player entered the game" messages
		OldPlayerState->Destroy();
	}

	InitSeamlessTravelPlayer(Controller);

	// Initialize hud and other player details, shared with PostLogin
	GenericPlayerInitialization(Controller);
	
	if (AGasaGameState* GS = GetGameState<AGasaGameState>())
	{
#if 0
		UGasaGameInstance* GI = GetGameInstance<UGasaGameInstance>();
		int32 NumConnections = GI->SessionSettings.bPublicGame
			? GI->SessionSettings.PublicConnections
			: GI->SessionSettings.PrivateConnections;
		if (GS->OnlinePlayers.Num() < NumConnections)
			GS->OnlinePlayers.Init( nullptr, NumConnections );
		
		for (AGasaPlayerState* & PS : GS->OnlinePlayers)
		{
			if (PS == nullptr)
			{
				PS = C->GetPlayerState<ASlipgatePlayerState>();
				PS->SgID = GS->OnlinePlayers.Find( PS );
				break;
			}
		}
#endif
	}

	// Controller->GetPlayerState<AGasaPlayerState>()->NativePlatformUniqueNetId = StoredNativePlatformUniqueNetId;
	NetLog(FString::Printf(TEXT("HandleSeamlessTravelPlayer: %s"), * Controller->GetName()) );

#if 0
	if (PC)
		PC->Event_NetOwner_OnGameplayFrameworkInitialized.AddDynamic(this, &ThisClass::OwningClient_OnGameFrameworkInitialized);
#endif
}

void AGasaGameMode::InitializeHUDForPlayer_Implementation(APlayerController* NewPlayer)
{
	// Super::InitializeHUDForPlayer_Implementation(NewPlayer);
	NewPlayer->ClientSetHUD(HUDClass);
}

void AGasaGameMode::InitSeamlessTravelPlayer(AController* NewController)
{
	if (NewController)
		NewController->bBlockInput = true;
	
	// GameMode::InitSeamlessTravelPlayer(NewController);
	{
		// AGameModeBase::InitSeamlessTravelPlayer(NewController);
		{
			APlayerController* NewPC = Cast<APlayerController>(NewController);

			FString ErrorMessage;
			if (!UpdatePlayerStartSpot(NewController, TEXT(""), ErrorMessage))
				NetLog(FString::Printf( TEXT("InitSeamlessTravelPlayer: %s"), *ErrorMessage), ELogV::Warning);

			if (NewPC != nullptr)
			{
				NewPC->PostSeamlessTravel();

				if (MustSpectate(NewPC))
				{
					NewPC->StartSpectatingOnly();
				}
				else
				{
					NewPC->bPlayerIsWaiting = true;
					NewPC->ChangeState(NAME_Spectating);
					NewPC->ClientGotoState(NAME_Spectating);
				}
			}
		}

		APlayerController* NewPC = Cast<APlayerController>(NewController);

		if (NewPC != nullptr)
		{
			SetSeamlessTravelViewTarget(NewPC);

			if (!MustSpectate(NewPC))
			{
				NumPlayers++;
				NumTravellingPlayers--;
			}
		}
		else
		{
			NumBots++;
		}
	}
	NetLog("InitSeamlessTravelPlayer: " + NewController->GetName());
}

void AGasaGameMode::HandleMatchAborted()
{
	Super::HandleMatchAborted();
	NetLog("HandleMatchAborted");
}

void AGasaGameMode::Logout(AController* Exiting)
{
	Super::Logout(Exiting);

	Event_OnLogout.Broadcast(Cast<AGasaPlayerController>(Exiting));
	NetLog("User Logged out: " + Exiting->GetName());

	if (AGasaGameState* GS = Cast<AGasaGameState>(GetWorld()->GetGameState()))
	{
#if 0
		int32 Index = GS->OnlinePlayers.Find(Exiting->GetPlayerState<AGasaGameState>());
		if (Index == INDEX_NONE)
		{
			NetLog("Could not find exiting player state in online players!", ELogV::Error);
			return;
		}
		GS->OnlinePlayers[Index] = nullptr;
#endif

#if 0
		IOnlineSessionPtr const SessionInterface = Online::GetSessionInterface(GetWorld());
		if ( ! SessionInterface.IsValid())
		{
			NetLog("DestoryCurrentSession: Could not get the session interface.", ELogV::Warning);
			return;
		}
#endif
	}
}

void AGasaGameMode::PreLogin(const FString& Options, const FString& Address, const FUniqueNetIdRepl& UniqueId, FString& ErrorMessage)
{
	Super::PreLogin(Options, Address, UniqueId, ErrorMessage);
	// TODO(Ed): Refuse players if the server is full.
}

void AGasaGameMode::PostLogin(APlayerController* NewPlayer)
{
	// AGameMode::PostLogin(NewPlayer);
	{
		UWorld* World = GetWorld();

		// Update player count
		if (MustSpectate(NewPlayer))
			NumSpectators++;
		else if (World->IsInSeamlessTravel() || NewPlayer->HasClientLoadedCurrentWorld())
			NumPlayers++;
		else
			NumTravellingPlayers++;

		// Save network address for re-associating with reconnecting player, after stripping out port number
		FString Address = NewPlayer->GetPlayerNetworkAddress();
		int32   Pos     = Address.Find(TEXT(":"), ESearchCase::CaseSensitive);

		NewPlayer->PlayerState->SavedNetworkAddress = (Pos > 0) ? Address.Left(Pos) : Address;

		// Check if this player is reconnecting and already has PlayerState
		FindInactivePlayer(NewPlayer);	
	}

	// AGameModeBase::PostLogin(NewPlayer)
	{
		// Runs shared initialization that can happen during seamless travel as well
		GenericPlayerInitialization(NewPlayer);

		// Perform initialization that only happens on initially joining a server
		NewPlayer->ClientCapBandwidth(NewPlayer->Player->CurrentNetSpeed);

		if (MustSpectate(NewPlayer))
		{
			NewPlayer->ClientGotoState(NAME_Spectating);
		}
		else
		{
			// If NewPlayer is not only a spectator and has a valid ID, add him as a user to the replay.
			FUniqueNetIdRepl const&
				NewPlayerStateUniqueId = NewPlayer->PlayerState->GetUniqueId();
			if (NewPlayerStateUniqueId.IsValid())
			{
				GetGameInstance()->AddUserToReplay(NewPlayerStateUniqueId.ToString());
			}
		}

		if (GameSession)
		{
			GameSession->PostLogin(NewPlayer);
		}
	}

	if (AGasaGameState* GS = GetGameState<AGasaGameState>())
	{
		UGasaGameInstance* GI = GetGameInstance<UGasaGameInstance>();
		
#if 0
		int32 numconnections = GI->sessionsettings.bPublicGame
			? GI->SessionSettings.PublicConnections : GI->SessionSettings.PrivateConnections;
		
		if (GS->OnlinePlayers.Num() < NumConnections)
		{
			GS->OnlinePlayers.Init( nullptr, NumConnections );
		}
		
		for (AGasaPlayerState* & PS : GS->OnlinePlayers)
		{
			if (PS == nullptr)
			{
				PS = NewPlayer->GetPlayerState<AGasaPlayerState>();
				PS->GasaID = GS->OnlinePlayers.Find( PS );
				break;
			}
		}
#endif
	}

	// cont. AGameModeBase::PostLogin(NewPlayer)
	{
		// Notify Blueprints that a new player has logged in.  Calling it here, because this is the first time that the PlayerController can take RPCs
		DispatchPostLogin(NewPlayer);
	}

	AGasaPlayerController* PC = Cast<AGasaPlayerController>(NewPlayer);
	if (PC)
		PC->Event_NetOwner_OnGameFrameworkInitialized.AddDynamic(this, &ThisClass::OwningClient_OnGameFrameworkInitialized);
}

void AGasaGameMode::PostSeamlessTravel()
{
	Super::PostSeamlessTravel();
	NetLog("PostSeamlessTravel");
}

void AGasaGameMode::SetPlayerDefaults(APawn* PlayerPawn)
{
	InitializeHUDForPlayer(Cast<APlayerController>(PlayerPawn->GetController()));
	Super::SetPlayerDefaults(PlayerPawn);
}

void AGasaGameMode::SetSeamlessTravelViewTarget(APlayerController* PC)
{
	Super::SetSeamlessTravelViewTarget(PC);
	NetLog("SetSeamlessTravelViewTarget");
}

void AGasaGameMode::StartPlay()
{
	if (MatchState == MatchState::EnteringMap)
		SetMatchState(MatchState::WaitingToStart);
	
	// Start match is deferred until the framework is considered initialized.
	NetLog("StartPlay");
	
	UGasaGameInstance* GI = GetGameInstance<UGasaGameInstance>();
	GI->Event_OnGameFrameworkInitialized.AddDynamic(this, &ThisClass::OnGameFrameworkInitialized);
	GI->NotifyGameFrameworkClassReady(EGameFrameworkClassFlag::GameMode);

	// Not called yet, will wait for initialization of the framework.
	//Super::StartPlay();
}

void AGasaGameMode::StartToLeaveMap()
{
	NetLog("StartToLeaveMap");
	Super::StartToLeaveMap();
}

void AGasaGameMode::SwapPlayerControllers(APlayerController* OldPC, APlayerController* NewPC)
{
	NetLog("SwapPlayerControllers");
	NetLog("Old: " + OldPC->GetName());
	NetLog("New: " + NewPC->GetName());
	
	Super::SwapPlayerControllers(OldPC, NewPC);
}

APlayerController* AGasaGameMode::SpawnPlayerControllerCommon(ENetRole InRemoteRole, FVector const& SpawnLocation, FRotator const& SpawnRotation,
	TSubclassOf<APlayerController> InPlayerControllerClass)
{
	NetLog("SpawnPlayerControllerCommon");
	return Super::SpawnPlayerControllerCommon(InRemoteRole, SpawnLocation, SpawnRotation, InPlayerControllerClass);
}
#pragma endregion GameModeBase
