#include "GasaCharacter.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"

void AGasaCharacter::SetHighlight(EHighlight desired)
{
	
}

AGasaCharacter::AGasaCharacter()
{
	PrimaryActorTick.bCanEverTick = false;

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
