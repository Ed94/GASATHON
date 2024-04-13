#include "GasaCharacter.h"

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

	CamSpringArm = CreateDefaultSubobject<USpringArmComponent>("Camera Spring Arm");
	CamSpringArm->SetupAttachment(root_component);
	CamSpringArm->SetRelativeRotation( FQuat::MakeFromEuler(FVector(0.0, -35.0, 0.0)));
	CamSpringArm->TargetArmLength = 400.0f;

	CamSpringArm->bInheritPitch = false;
	CamSpringArm->bInheritYaw   = false;
	CamSpringArm->bInheritRoll  = false;
	
	Camera = CreateDefaultSubobject<UCameraComponent>("Camera");
	Camera->SetupAttachment(CamSpringArm);

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
}
