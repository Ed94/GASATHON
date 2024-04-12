#include "GasaCharacter.h"

AGasaCharacter::AGasaCharacter()
{
	PrimaryActorTick.bCanEverTick = false;

	Weapon = CreateDefaultSubobject<USkeletalMeshComponent>("Weapon");
	Weapon->SetupAttachment(GetMesh(), FName("WeaponAttach"));
	Weapon->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void AGasaCharacter::BeginPlay()
{
	Super::BeginPlay();
}
