#include "GasaPlayerState.h"

#include "Networking/GasaNetLibrary_Inlines.h"
#include "GasaGameInstance.h"
#include "GasaPlayerController.h"
#include "AbilitySystem/GasaAbilitySystemComponent.h"
#include "AbilitySystem/GasaAttributeSet.h"

AGasaPlayerState::AGasaPlayerState()
{
	bAutoAbilitySystem = true;
	
	AbilitySystem = CreateDefaultSubobject<UGasaAbilitySystemComp>("Ability System");
	AbilitySystem->SetIsReplicated(true);
	AbilitySystem->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);
	
	Attributes = CreateDefaultSubobject<UGasaAttributeSet>("Attributes");
	
	// Replication
	NetUpdateFrequency = 100.f;
}

#pragma region GameFramework
void AGasaPlayerState::OnGameFrameworkInitialized()
{
	NetLog("Received game framework initialization.");
	BP_OnGameFrameworkInitialized();
}

void AGasaPlayerState::OnNetOwnerReady(AGasaPlayerController* PC)
{
	BP_OnNetOwnerReady();
}

void AGasaPlayerState::Reset()
{
	Super::Reset();
	NetLog("Reset");
}

#pragma endregion GameFramework

#pragma region PlayerState
void AGasaPlayerState::ClientInitialize(AController* NewOwner)
{
	Super::ClientInitialize(NewOwner);
	NetLog("Client Initialization: This is the OnRep for player state.");

	AGasaPlayerController* GasaPC = Cast<AGasaPlayerController>(NewOwner);
	if (GasaPC)
		GasaPC->Client_CheckIfOwnerReady();
}
#pragma endregion PlayerState

#pragma region Actor
void AGasaPlayerState::BeginPlay()
{
	NetLog("Begin Play");
	Super::BeginPlay();

	UGasaGameInstance* GI = GetGameInstance<UGasaGameInstance>();
	GI->Event_OnGameFrameworkInitialized.AddDynamic(this, & ThisClass::OnGameFrameworkInitialized);
	GI->NotifyGameFrameworkClassReady(EGameFrameworkClassFlag::PlayerState);
}

void AGasaPlayerState::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	NetLog("Post Initialization");
}

void AGasaPlayerState::RegisterPlayerWithSession(bool bWasFromInvite)
{
	Super::RegisterPlayerWithSession(bWasFromInvite);
	NetLog("RegisterPlayerWithSession");
	
	if (IsServer() && GetInstigatorController())
	{
		AGasaPlayerController* PC = Cast<AGasaPlayerController>(GetInstigatorController());
		PC->Event_NetOwner_OnReady.AddDynamic(this, & ThisClass::OnNetOwnerReady);
	}
}
#pragma endregion Actor

#pragma region UObject
void AGasaPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	
}
#pragma endregion UObject
