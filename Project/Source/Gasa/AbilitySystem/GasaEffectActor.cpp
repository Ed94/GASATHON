#include "GasaEffectActor.h"

#include "AbilitySystemInterface.h"
#include "GasaAttributeSet.h"
#include "GasaAttributeSet_Inlines.h"
#include "Components/SphereComponent.h"


AGasaEffectActor::AGasaEffectActor()
{
	PrimaryActorTick.bCanEverTick = false;

	Mesh   = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	Sphere = CreateDefaultSubobject<USphereComponent>("Sphere");

	SetRootComponent(Mesh);
	Sphere->SetupAttachment(Mesh);
}

void AGasaEffectActor::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent
	, AActor* OtherActor
	, UPrimitiveComponent* OtherComp
	, int32 OtherBodyIndex
	, bool bFromSweep
	, FHitResult const& SweepResult)
{
	// Demo of "restricted way"
	if ( ! OtherActor->Implements<UAbilitySystemInterface>())
		return;
	
	IAbilitySystemInterface* ASI = Cast<IAbilitySystemInterface>(OtherActor);
	if (ASI == nullptr)
		return;

	// TODO(Ed): Change this to use a gameplay effect instead
	UAbilitySystemComponent* AbilitySystem = ASI->GetAbilitySystemComponent();
	UGasaAttributeSet*       MutAttributes = const_cast<UGasaAttributeSet*>(Gasa::GetAttributeSet(AbilitySystem));
	
	MutAttributes->SetHealth( MutAttributes->GetHealth() + 25.f );
	Destroy();
}

void AGasaEffectActor::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent
	, AActor* OtherActor
	, UPrimitiveComponent* OtherComp
	, int32 OtherBodyIndex)
{
}

void AGasaEffectActor::BeginPlay()
{
	Super::BeginPlay();
}

void AGasaEffectActor::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	Sphere->OnComponentBeginOverlap.AddUniqueDynamic(this, &ThisClass::OnOverlapBegin);
	Sphere->OnComponentEndOverlap.AddUniqueDynamic(this, &ThisClass::OnOverlapEnd);
}
