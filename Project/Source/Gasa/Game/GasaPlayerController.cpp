#include "GasaPlayerController.h"
#include "GasaPlayerController_Inlines.h"
#include "Networking/GasaNetLibrary_Inlines.h"

#include "AbilitySystemComponent.h"
#include "Engine/LocalPlayer.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Characters/GasaCharacter.h"
#include "Characters/PlayerCharacter.h"
#include "Components/CapsuleComponent.h"
#include "Interfaces/NetworkPredictionInterface.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Net/UnrealNetwork.h"
#include "GameFramework/PawnMovementComponent.h"

#include "GasaDevOptions.h"
#include "GasaGameInstance.h"
#include "GasaGameState.h"
#include "GasaPlayerState.h"
#include "Actors/CameraMount.h"
#include "UI/GasaHUD.h"
#include "UI/WidgetController.h"
using namespace Gasa;

AGasaPlayerController::AGasaPlayerController()
{
	PrimaryActorTick.bCanEverTick = true;
	bAutoManageActiveCameraTarget = false;

	// Replication
	bReplicates = true;
}

void AGasaPlayerController::OnSeamlessTravelStart()
{
}

#pragma region GameFramework
void AGasaPlayerController::Client_CheckIfOwnerReady()
{
	if (IsServer())
		return;
	
	UGasaGameInstance* GI = GetGameInstance<UGasaGameInstance>();
	if ( ! GI->IsGameFrameworkInitialized() || PlayerState == NULL || ! IsValid(GetPawn()))
		return;
	
	NetOwner_OnReady();
}

void AGasaPlayerController::NetOwner_OnReady()
{
	NetLog("Net Owner of controller is ready to play.");
	if ( ! IsNetOwner() || bNetOwnerReady)
		return;
	
	BP_NetOwner_OnReady();
	Event_NetOwner_OnReady.Broadcast(this);
	bNetOwnerReady = true;

	AGasaGameState* GS = Cast<AGasaGameState>(GetWorld()->GetGameState());
	if (GS)
		GS->NotifyPlayerPawnReady(GetPawn());

	if (IsClient())
		ServerRPC_R_NotifyOwningClientReady();

	AGasaPlayerState* PS         = GetPlayerState();
	APlayerCharacter* PlayerChar = GetPawn<APlayerCharacter>();
	{
		PlayerChar->AbilitySystem = PS->AbilitySystem;
		PlayerChar->Attributes    = PS->Attributes;
		PlayerChar->AbilitySystem->InitAbilityActorInfo(PS, this);
		Cam->AttachToActor(PlayerChar, FAttachmentTransformRules::KeepRelativeTransform);
	}
}

void AGasaPlayerController::OnGameFrameworkInitialized()
{
	NetLog("Received game framework initialization.");
	if (IsNetOwner())
	{
		Server_SetNetOwner_GameFrameworkInitialized();
		Client_CheckIfOwnerReady();
	}

	AGasaGameState* GS = GetGameState(this);
	NullGuard_DEV(GS, Log, "OnGameFrameworkInitialized: GS is null");
	GS->Event_OnSeamlessTravelStart.AddDynamic( this, & ThisClass::OnSeamlessTravelStart );
	
	BP_OnGameFrameworkInitialized();
}

void AGasaPlayerController::OnPawnReady()
{
	NetLog("Player is ready.");

	// Originally: Super::OnPossess(PawnToPossess);
	{
		ChangeState(NAME_Playing);
		if (bAutoManageActiveCameraTarget)
		{
			AutoManageActiveCameraTarget(GetPawn());
			ResetCameraMode();
		}
	}

	// Override this and add your own conditions...
	BP_OnPawnReady();

	if (IsServer() && IsNetOwner())
	{
		// The server host doesn't have to wait for the player state to replicate.
		NetOwner_OnReady();
	}
}

void AGasaPlayerController::Server_SetupOnPawnReadyBinds(APawn* PawnToBindTo)
{
	if (IsClient())
		return;
#if 0
	if (PawnToBindTo->IsA(AGasaPawn::StaticClass()))
	{
		Cast<AGasaPawn>(PawnToBindTo)->Event_OnPawnReady.AddUniqueDynamic(this, & ThisClass::OnPawnReady);
	}
	else
#endif
	if (PawnToBindTo->IsA(AGasaCharacter::StaticClass()))
	{
		Cast<AGasaCharacter>(PawnToBindTo)->Event_OnPawnReady.AddUniqueDynamic(this, & ThisClass::OnPawnReady);
	}
}

void AGasaPlayerController::Server_SetNetOwner_GameFrameworkInitialized()
{
	if (IsClient())
	{
		ServerRPC_R_SetNetOwner_GameFrameworkInitialized();
		return;
	}
	
	bNetOwner_GameFrameworkInitialized = true;
	if (Event_NetOwner_OnGameFrameworkInitialized.IsBound())
	{
		Event_NetOwner_OnGameFrameworkInitialized.Broadcast(this);
		Event_NetOwner_OnGameFrameworkInitialized.Clear();
	}
}

void AGasaPlayerController::ServerRPC_R_NotifyOwningClientReady_Implementation()
{
	NetLog("Net Owner Ready: Notified via RPC.");

	BP_NetOwner_OnReady();
	bNetOwnerReady = true;
	Event_NetOwner_OnReady.Broadcast(this);
	Event_NetOwner_OnReady.Clear();
	
	AGasaGameState* GS = GetGameState(this);

	if (GS)
		GS->NotifyPlayerPawnReady(GetPawn());
}

void AGasaPlayerController::ServerRPC_R_SetNetOwner_GameFrameworkInitialized_Implementation()
{
	Server_SetNetOwner_GameFrameworkInitialized();
}
#pragma endregion GameFramework

#pragma region Input
void AGasaPlayerController::Move(FInputActionValue const& ActionValue)
{
	APawn* pawn = GetPawn<APawn>();
	if (pawn == nullptr )
		return;

// Note(Ed): I did the follow optimization for practice, they are completely unnecessary for this context.
#if 0
	FVector2D AxisV     = ActionValue.Get<FVector2D>();
	FRotator ControlRot = GetControlRotation();
	FRotator YawRot     = FRotator(0.f, ControlRot.Yaw, 0.f);

	FVector FwdDir   = FRotationMatrix(YawRot).GetUnitAxis(EAxis::X);
	FVector RightDir = FRotationMatrix(YawRot).GetUnitAxis(EAxis::Y);

	PPawn->AddMovementInput(FwdDir,   AxisV.Y);
	PPawn->AddMovementInput(RightDir, AxisV.X);
#else
	FVector2f AxisV = FVector2f(ActionValue.Get<FVector2D>());

	FQuat4f // FQuat isomorphic to FRotor (Hypothetical Def)
	ControlRotor = FQuat4f(GetControlRotation().Quaternion());
	// ControlRotor.Normalize();  // The Quaternion should always be a versor with UE...

	FVector3f HorizontalForward = ControlRotor.RotateVector(FVector3f::ForwardVector);
	// HorizontalForward.Normalize();

	// TODO(Ed): Profile which is faster just to know... (atan2 vs FindBetweenVectors)
	// HorizontalForward.Z = 0;
	// FQuat4f
	// YawRotor = FQuat4f::FindBetweenVectors(FVector3f::ForwardVector, HorizontalForward);
	// YawRotor.Normalize(); // The Quaternion should always be a versor with UE...

	// Need only one axis of rotation so this might be a possible optimization
	float   YawAngle = FMath::Atan2(HorizontalForward.Y, HorizontalForward.X);
	FQuat4f YawRotor = FQuat4f(FVector3f::UpVector, YawAngle);

	// Rotate the combined input by the yaw rotor to get the movement direction
	FVector MoveDir = (FVector) YawRotor.RotateVector( FVector3f(AxisV.Y, AxisV.X, 0.f));
	pawn->AddMovementInput( MoveDir );
#endif
}
#pragma endregion Input

#pragma region PlayerController
bool AGasaPlayerController::CanRestartPlayer()
{
	bool BaseCheck = 
			PlayerState && 
			!PlayerState->IsOnlyASpectator() && 
			HasClientLoadedCurrentWorld() && 
			PendingSwapConnection  == NULL
		;

	return BaseCheck && bNetOwner_GameFrameworkInitialized;
}

void AGasaPlayerController::ClientSetHUD_Implementation(TSubclassOf<AHUD> NewHUDClass)
{
	Super::ClientSetHUD_Implementation(NewHUDClass);
	AGasaPlayerState*      PS   = GetPlayerState();
	AGasaHUD*              HUD  = GetHUD<AGasaHUD>();
	FWidgetControllerData  Data = { this, PS, PS->AbilitySystem, PS->Attributes };
	HUD->InitHostWidget(& Data);
}

void AGasaPlayerController::ClientUpdateLevelStreamingStatus_Implementation(FName PackageName, bool bNewShouldBeLoaded, bool bNewShouldBeVisible,
                                                                            bool bNewShouldBlockOnLoad, int32 LODIndex, FNetLevelVisibilityTransactionId TransactionId, bool bNewShouldBlockOnUnload)
{
	Super::ClientUpdateLevelStreamingStatus_Implementation(PackageName, bNewShouldBeLoaded, bNewShouldBeVisible, bNewShouldBlockOnLoad, LODIndex,
	                                                       TransactionId, bNewShouldBlockOnUnload);

	NetLog("ClientUpdateLevelStreamingStatus");
	NetLog(FString("PackageName            : ") + PackageName.ToString()); 
	NetLog(FString("NewShouldBeLoaded      : ") + FString(bNewShouldBeLoaded ? "true" : "false"));
	NetLog(FString("NewShouldBeVisible     : ") + FString(bNewShouldBeVisible ? "true" : "false"));
	NetLog(FString("bNewShouldBlockOnLoad  : ") + FString(bNewShouldBlockOnLoad ? "true" : "false"));
	NetLog(FString("bNewShouldBlockOnUnload: ") + FString(bNewShouldBlockOnUnload ? "true" : "false"));
	NetLog(FString("LODIndex               : ") + FString::FromInt( LODIndex ));	
}

// TODO(Ed): We need to setup Net Slime...
void AGasaPlayerController::OnPossess(APawn* PawnPossesed)
{
	// Super::OnPossess(PawnPossesed);
	{
		if (PawnPossesed && (PlayerState == NULL || !PlayerState->IsOnlyASpectator()) )
		{
			// ====================================================================Originally: Super::OnPossess(PawnToPossess);
			const bool bNewPawn = (GetPawn() != PawnPossesed);
			if (GetPawn() && bNewPawn)
				UnPossess();

			if (PawnPossesed->Controller != NULL)
				PawnPossesed->Controller->UnPossess();
			
			PawnPossesed->PossessedBy(this);

			// update rotation to match possessed pawn's rotation
			SetControlRotation( PawnPossesed->GetActorRotation() );
			SetPawn(PawnPossesed);

			check(GetPawn() != NULL);
			if (GetPawn() && GetPawn()->PrimaryActorTick.bStartWithTickEnabled)
				GetPawn()->SetActorTickEnabled(true);

			INetworkPredictionInterface* NetworkPredictionInterface = GetPawn()
				? Cast<INetworkPredictionInterface>(GetPawn()->GetMovementComponent())
				: nullptr;
			if (NetworkPredictionInterface)
				NetworkPredictionInterface->ResetPredictionData_Server();

			AcknowledgedPawn = NULL;

			// Local PCs will have the Restart() triggered right away in ClientRestart (via PawnClientRestart()), but the server should call Restart() locally for remote PCs.
			// We're really just trying to avoid calling Restart() multiple times.
			if (!IsLocalPlayerController())
				GetPawn()->Restart();

			ClientRestart(GetPawn());


		// Moved to: void AGasaPlayerController::OnPawnReady
		#if 0
			ChangeState( NAME_Playing );
			if (bAutoManageActiveCameraTarget)
			{
				AutoManageActiveCameraTarget(GetPawn());
				ResetCameraMode();
			}
		#endif
			//==========================================================End of=================== Originally: Super::OnPossess(PawnToPossess);

			NetLog("OnPossess");
			Server_SetupOnPawnReadyBinds(PawnPossesed);
			Event_OnPawnPossessed.Broadcast();
		}	
	}
}

void AGasaPlayerController::OnRep_Pawn()
{
	Super::OnRep_Pawn();
	
	NetLog("OnRep_Pawn");
	Client_CheckIfOwnerReady();
}

void AGasaPlayerController::OnUnPossess()
{
	Super::OnUnPossess();
}

void AGasaPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	// Cursor Trace
	for (int32 do_once = 0; do_once != 1; ++ do_once)
	{
		FHitResult CursorHit;
		GetHitResultUnderCursor(ECC_Pawn, false, CursorHit);
		if (! CursorHit.bBlockingHit)
			break;

		HoverPrev = HoverCurr;
		HoverCurr = Cast<AGasaCharacter>(CursorHit.GetActor());
		if (HoverPrev == nullptr)
		{
			// We didn't have a prev to de-highlight so we just need to highlight newly detected character.
			if (HoverCurr)
				HoverCurr->Highlight();

			// No matter what we need to not go to the next case as there is no previous.
			break;
		}
		//else Previous is valid...

		// We are no longer hovering the previous with no new character, we just need to de-highlight previous.		
		if ( HoverCurr == nullptr )
			HoverPrev->Dehighlight();

		// We had a prev and curr change between frames. They both don't match; we need to switch highlighting.
		else if ( HoverPrev != HoverCurr )
		{
			HoverPrev->Dehighlight();
			HoverCurr->Highlight();
		}
	}
}

void AGasaPlayerController::PostSeamlessTravel()
{
	Super::PostSeamlessTravel();
}

void AGasaPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	UEnhancedInputComponent*
	EIC = CastChecked<UEnhancedInputComponent>(InputComponent);
	{
		EIC->BindAction(IA_Move, ETriggerEvent::Triggered, this, &ThisClass::Move);	
	}
}

void AGasaPlayerController::SpawnDefaultHUD()
{
	Super::SpawnDefaultHUD();
}
#pragma endregion PlayerController

#pragma region Actor
void AGasaPlayerController::BeginPlay()
{
	Super::BeginPlay();
	NetLog("BeginPlay");

	UGasaGameInstance* GI = GetGameInstance<UGasaGameInstance>();
	GI->Event_OnGameFrameworkInitialized.AddUniqueDynamic(this, & AGasaPlayerController::OnGameFrameworkInitialized);
	GI->NotifyGameFrameworkClassReady(EGameFrameworkClassFlag::PlayerController);

	if (IsLocalController())
	{
		check(IMC);
		
		UEnhancedInputLocalPlayerSubsystem*
		EILP_Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
		check(EILP_Subsystem);
		EILP_Subsystem->AddMappingContext(IMC, 0);
		{
			bShowMouseCursor   = true;
			DefaultMouseCursor = EMouseCursor::Default;
			FInputModeGameAndUI MouseMode;
			MouseMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
			MouseMode.SetHideCursorDuringCapture(false);
			SetInputMode(MouseMode);
		}
	}
}

void AGasaPlayerController::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	Cam = GetWorld()->SpawnActor<ACameraMount>(GetDevOptions()->Template_PlayerCamera.Get(), FActorSpawnParameters() );
	SetViewTarget(Cam);
}

void AGasaPlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

#if 0
	switch (HighlightState)
	{
		case EHighlight::Disabled:
		break;
		case EHighlight::Enabled:
		{
			UCapsuleComponent* Capsule = GetCapsuleComponent();
				
			UKismetSystemLibrary::DrawDebugCapsule(this
				, Capsule->GetComponentLocation()
				, Capsule->GetScaledCapsuleHalfHeight()
				, Capsule->GetScaledCapsuleRadius()
				, Capsule->GetComponentRotation()
				, HighlightColor
				, 0.f
				, 1.f
			);
		}
		break;
	}
#endif
}

void AGasaPlayerController::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AGasaPlayerController, bNetOwner_GameFrameworkInitialized);
}
#pragma endregion Actor
