#include "GasaCharacter.h"

#include "AbilitySystemComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/KismetSystemLibrary.h"

#include "AbilitySystem/GasaAbilitySystemComponent.h"
#include "AbilitySystem/GasaAttributeSet.h"
#include "Components/SkeletalMeshComponent.h"
#include "Engine/PostProcessVolume.h"
#include "Game/GasaGameInstance.h"
#include "Game/GasaLevelScriptActor.h"
#include "Game/GasaPlayerController.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Networking/GasaNetLibrary_Inlines.h"
using namespace Gasa;

AGasaCharacter::AGasaCharacter()
{
	PrimaryActorTick.bCanEverTick = false;

	HighlightColor = FLinearColor(0.8, 0.32, 0.05f, 1.f);

	UCharacterMovementComponent*
	Movement = GetCharacterMovement();
	Movement->bOrientRotationToMovement = true;
	Movement->bConstrainToPlane         = true;
	Movement->bSnapToPlaneAtStart       = true;
	Movement->RotationRate              = FRotator(0.0, 400.f, 0.0);

	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll  = false;
	bUseControllerRotationYaw   = false;

	USceneComponent*        root_component = GetRootComponent();
	USkeletalMeshComponent* mesh           = GetMesh();

	Weapon = CreateDefaultSubobject<USkeletalMeshComponent>("Weapon");
	Weapon->SetupAttachment(mesh, FName("WeaponAttach"));
	Weapon->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	if (bAutoAbilitySystem)
	{
		AbilitySystem = CreateDefaultSubobject<UGasaAbilitySystemComp>("Ability System");
		AbilitySystem->SetIsReplicated(true);
		AbilitySystem->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);
		
		Attributes = CreateDefaultSubobject<UGasaAttributeSet>("Attributes");
	}

	// Replication
	
	bReplicates            = false;
	bNetLoadOnClient       = true;
	NetDormancy            = DORM_Awake;
	NetCullDistanceSquared = NetCullDist_Medium;
	NetUpdateFrequency     = 30.0f;
	MinNetUpdateFrequency  = 5.0f;
	NetPriority            = 2.0f;

	ACharacter::SetReplicateMovement(true);
}

#pragma region Ability System
void AGasaCharacter::ApplyEffectToSelf(TSubclassOf<UGameplayEffect> GE, float Level)
{
	UAbilitySystemComponent* ASC = GetAbilitySystemComponent();
	ensure(ASC);
	ensure(GE);
	FGameplayEffectContextHandle Context = ASC->MakeEffectContext(); Context.AddSourceObject(this);
	FGameplayEffectSpecHandle    Spec    = ASC->MakeOutgoingSpec(GE, Level, Context );
	ASC->ApplyGameplayEffectSpecToTarget( * Spec.Data, ASC );
}

void AGasaCharacter::InitDefaultAttributes()
{
	UAbilitySystemComponent* ASC = GetAbilitySystemComponent();
	ensure(ASC);

	ensure(DefaultVitalAttributes);
	ensure(DefaultPrimaryAttributes);
	ensure(DefaultSecondaryAttributes);

	FGameplayEffectContextHandle Context = ASC->MakeEffectContext();
	Context.AddSourceObject(this);

	FGameplayEffectSpecHandle SpecPrimary   = ASC->MakeOutgoingSpec(DefaultPrimaryAttributes,   1.0f, Context );
	FGameplayEffectSpecHandle SpecSecondary = ASC->MakeOutgoingSpec(DefaultSecondaryAttributes, 1.0f, Context );
	FGameplayEffectSpecHandle SpecVital     = ASC->MakeOutgoingSpec(DefaultVitalAttributes,     1.0f, Context );
	ASC->ApplyGameplayEffectSpecToTarget( * SpecPrimary.Data,   ASC );
	ASC->ApplyGameplayEffectSpecToTarget( * SpecSecondary.Data, ASC );
	ASC->ApplyGameplayEffectSpecToTarget( * SpecVital.Data,     ASC );
}
#pragma endregion Ability System

#pragma region GameFramework
void AGasaCharacter::Controller_OnPawnPossessed()
{
	NetLog("Controller confirmed possession.");

	// Do stuff here that you needed to wait for the player controller be aware of you for.
	BP_Controller_OnPawnPossessed();

	if (Event_OnPawnReady.IsBound())
		Event_OnPawnReady.Broadcast();	
}

void AGasaCharacter::ServerRPC_R_NotifyClientPawnReady_Implementation()
{
	Event_OnPawnReady.Broadcast();
}
#pragma endregion GameFramework

#pragma region Highlight
void AGasaCharacter::SetHighlight(EHighlight Desired)
{
	HighlightState = Desired;
}
#pragma endregion Highlight

#pragma region Pawn
void AGasaCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();
}

void AGasaCharacter::PossessedBy(AController* NewController)
{
	NetLog("Pawn possessed.");

	AController* OldController;
	
	// APawn::PossessedBy
	{
		SetOwner(NewController);
		OldController = Controller;
		Controller = NewController;

		ForceNetUpdate();

	#if UE_WITH_IRIS
		// The owning connection depends on the Controller having the new value.
		UpdateOwningNetConnection();
	#endif
		
		if (Controller->PlayerState != nullptr)
			SetPlayerState(Controller->PlayerState);

		if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
		{
			if (GetNetMode() != NM_Standalone)
			{
				SetReplicates(true);
				SetAutonomousProxy(true);
			}
		}
		else
			CopyRemoteRoleFrom(GetDefault<APawn>());
	}

	if (AGasaPlayerController* PC = Cast<AGasaPlayerController>(NewController))
	{
		PC->Event_OnPawnPossessed.AddUniqueDynamic(this, & ThisClass::Controller_OnPawnPossessed);
	}
	else
	{
		NetLog("Controller assigned to GasaCharacter is not derived from GasaPlayerController.", ELogV::Warning);
		NetLog("Controller: Name: " + NewController->GetName() + " Class: " + NewController->GetClass()->GetName(), ELogV::Warning);
	}

	// cont. APawn::PossessedBy
	{
		// Dispatch Blueprint event if necessary
		if (OldController != NewController)
		{
			ReceivePossessed(Controller);
			NotifyControllerChanged();
		}
	}

	// ACharacter::PossessedBy
	{
		// If we are controlled remotely, set animation timing to be driven by client's network updates. So timing and events remain in sync.
		if (GetMesh() && IsReplicatingMovement() && (GetRemoteRole() == ROLE_AutonomousProxy && GetNetConnection() != nullptr))
			GetMesh()->bOnlyAllowAutonomousTickPose = true;
	}

#if 1
//	if (bAutoAbilitySystem)
//	{
//		// Note(Ed): For the player character; this is manually called by the player controller in NetOwner_Ready()
//		AbilitySystem->InitAbilityActorInfo(this, this);
//		Cast<UGasaAbilitySystemComp>(AbilitySystem)->OnAbilityActorInfoSet();
//		
//		InitDefaultAttributes();
//	}
#endif
}

void AGasaCharacter::SetPlayerDefaults()
{
	Super::SetPlayerDefaults();
}

void AGasaCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}
#pragma endregion Pawn

#pragma region Actor
void AGasaCharacter::BeginPlay()
{
	Super::BeginPlay();

	// TODO(Ed): Find out if this is the best spot todo this
	// There is also OnPossessed, PostInitializeComponents, etc...
	if (bAutoAbilitySystem)
	{
		// Note(Ed): For the player character; this is manually called by the player controller in NetOwner_Ready()
		AbilitySystem->InitAbilityActorInfo(this, this);
		Cast<UGasaAbilitySystemComp>(AbilitySystem)->OnAbilityActorInfoSet();
		
		InitDefaultAttributes();
	}
}

void AGasaCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	
	USkeletalMeshComponent* mesh = GetMesh();
	switch (HighlightState)
	{
		case EHighlight::Disabled:
		{
			mesh->SetRenderCustomDepth(false);
			mesh->SetCustomDepthStencilValue(0.f);
			Weapon->SetRenderCustomDepth(false);
			Weapon->SetCustomDepthStencilValue(0.f);
		}	
		break;
		case EHighlight::Enabled:
		{
			mesh->SetRenderCustomDepth(true);
			mesh->SetCustomDepthStencilValue(HighlightStencilDepth);
			Weapon->SetRenderCustomDepth(true);
			Weapon->SetCustomDepthStencilValue(HighlightStencilDepth);

			APostProcessVolume* PPV     = Gasa::GetLevelActor(this)->GlobalPPV;
			TObjectPtr<UObject> Blendable = PPV->Settings.WeightedBlendables.Array[0].Object;
			UMaterialInstanceDynamic*
			MID = Cast<UMaterialInstanceDynamic>(Blendable);
			MID->SetVectorParameterValue("Depth Highlight Color", HighlightColor);
#if 0
			UCapsuleComponent* Capsule = GetCapsuleComponent();
			UKismetSystemLibrary::DrawDebugCapsule(this
				, Capsule->GetComponentLocation()
				, Capsule->GetScaledCapsuleHalfHeight()^
				, Capsule->GetScaledCapsuleRadius()
				, Capsule->GetComponentRotation()
				, HighlightColor
				, 0.f
				, 1.f
			);
#endif
		}
		break;
	}
}
#pragma endregion Actor

