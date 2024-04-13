#include "CameraMount.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"


ACameraMount::ACameraMount()
{
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>("Root");
	
	CamSpringArm = CreateDefaultSubobject<USpringArmComponent>("Camera Spring Arm");
	CamSpringArm->SetupAttachment(RootComponent);
	CamSpringArm->SetRelativeRotation( FQuat::MakeFromEuler(FVector(0.0, -35.0, 0.0)));
	CamSpringArm->TargetArmLength  = 400.0f;
	CamSpringArm->bDoCollisionTest = true;

	CamSpringArm->bInheritPitch = false;
	CamSpringArm->bInheritYaw   = false;
	CamSpringArm->bInheritRoll  = false;
	
	Camera = CreateDefaultSubobject<UCameraComponent>("Camera");
	Camera->SetupAttachment(CamSpringArm);
}

void ACameraMount::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}
