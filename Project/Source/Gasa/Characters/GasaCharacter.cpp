#include "GasaCharacter.h"

#include "Game/GasaLevelScriptActor.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/KismetSystemLibrary.h"

void AGasaCharacter::SetHighlight(EHighlight Desired)
{
	HighlightState = Desired;
}

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
}

void AGasaCharacter::BeginPlay()
{
	Super::BeginPlay();
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
