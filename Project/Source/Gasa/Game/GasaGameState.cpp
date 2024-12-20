﻿#include "GasaGameState.h"

#include "CogAll.h"
#include "CogWindowManager.h"
#include "GasaPlayerState.h"
#include "GasaGameInstance.h"
#include "Net/UnrealNetwork.h"
#include "Networking/GasaNetLibrary_Inlines.h"
using namespace Gasa;

AGasaGameState::AGasaGameState()
{
	// Enable ticking
    PrimaryActorTick.bCanEverTick = true;
    PrimaryActorTick.SetTickFunctionEnable(true);
    PrimaryActorTick.bStartWithTickEnabled = true;

	// Replication
	bReplicates            = true;
	bNetLoadOnClient       = false;
	NetDormancy            = DORM_Awake;
	NetCullDistanceSquared = NetCullDist_Default;
	NetUpdateFrequency     = 10.0f;
	MinNetUpdateFrequency  = 1.0f;
	NetPriority            = 5.0f;
}

#pragma region GameFramework
void AGasaGameState::OnGameFrameworkInitialized()
{
	NetLog("Received gameplay framework initialization.");
	if (IsServer())
	{
		if (PlayerArray.Num() > 0)
		{
			ListenServerHost = Cast<AGasaPlayerState>(PlayerArray[0]);
		}
		else
		{
			NetLog("Was not able to assign HostingPlayer!", ELogV::Error);
		}
	}
	BP_OnGameFrameworkInitialized();
}
#pragma endregion GameFramework

#pragma region Networking
void AGasaGameState::Client_OnRep_OnlinePlayers()
{
}
#pragma endregion Networking

#pragma region Seamless Travel
void AGasaGameState::Multicast_R_NotifySeamlessTravelEnd_Implementation()
{
	NetLog("Multicast_R_NotifySeamlessTravelEnd_Implementation");
	BP_Event_OnSeamlessTravelEnd.Broadcast();
	Event_OnSeamlessTravelEnd.Broadcast();
}
#pragma endregion Seamless Travel

#pragma region GameStateBase
void AGasaGameState::HandleBeginPlay()
{
	Super::HandleBeginPlay();
	NetLog("HandleBeginPlay: Directly called from GM");
}

void AGasaGameState::SeamlessTravelTransitionCheckpoint(bool bToTransitionMap)
{
	Super::SeamlessTravelTransitionCheckpoint(bToTransitionMap);
	NetLog("SeamlessTravelTransitionCheckpoint");
	NetLog(FString("ToTransitionMap: ") + FString(bToTransitionMap ? "true" : "false"));

	if (bToTransitionMap)
	{
		Event_OnSeamlessTravelStart.Broadcast();
	}
	else
	{
		Multicast_R_NotifySeamlessTravelEnd();
	}
}
#pragma endregion GameStateBase

#pragma region Actor
void AGasaGameState::BeginPlay()
{
	Super::BeginPlay();
	NetLog("BeginPlay");

	// Notified as initialized here as any possible components should also be initialized by this point.
	UGasaGameInstance*
	GI = GetGameInstance<UGasaGameInstance>();
	GI->Event_OnGameFrameworkInitialized.AddDynamic(this, & ThisClass::OnGameFrameworkInitialized);
	GI->NotifyGameFrameworkClassReady(EGameFrameworkClassFlag::GameState);
	
#if ENABLE_COG
	CogWindowManager = NewObject<UCogWindowManager>(this);
	CogWindowManagerRef = CogWindowManager;

	// Add all the built-in windows
	Cog::AddAllWindows(*CogWindowManager);
#endif //ENABLE_COG
}

void AGasaGameState::PostInitializeComponents()
{
	NetLog("PostInitializeComponents");
	Super::PostInitializeComponents();

	if ( ! GetWorld()->IsEditorWorld() && IsServer())
	{
		OnlinePlayers.Empty();
#if 0
		const auto GI = Cast<UGasaGameInstance>(GetGameInstance());
		if (GI != nullptr)
		{
			int32 NumConnections = GI->SessionSettings.bPublicGame
				? GI->SessionSettings.PublicConnections
				: GI->SessionSettings.PrivateConnections;
			OnlinePlayers.Init(nullptr, NumConnections);
		}
#endif
	}	
}

void AGasaGameState::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

#if ENABLE_COG
	if (CogWindowManager)
		CogWindowManager->Tick(DeltaSeconds);
#endif //ENABLE_COG
}
#pragma endregion Actor

#pragma region UObject
void AGasaGameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AGasaGameState, ListenServerHost);
	DOREPLIFETIME(AGasaGameState, OnlinePlayers);
}
#pragma endregion UObject
