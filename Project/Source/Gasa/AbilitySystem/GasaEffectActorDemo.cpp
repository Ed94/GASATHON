#include "GasaEffectActorDemo.h"

#include "AbilitySystemInterface.h"
#include "GasaAttributeSet.h"
#include "GasaAttributeSet_Inlines.h"
#include "Components/SphereComponent.h"


AGasaEffectActorDemo::AGasaEffectActorDemo()
{
	PrimaryActorTick.bCanEverTick = false;

	Mesh   = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	Sphere = CreateDefaultSubobject<USphereComponent>("Sphere");

	SetRootComponent(Mesh);
	Sphere->SetupAttachment(Mesh);
}

void AGasaEffectActorDemo::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent
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
	MutAttributes->SetMana( MutAttributes->GetMana() - 25.f );
	Destroy();
}

void AGasaEffectActorDemo::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent
	, AActor* OtherActor
	, UPrimitiveComponent* OtherComp
	, int32 OtherBodyIndex)
{
}

void AGasaEffectActorDemo::BeginPlay()
{
	Super::BeginPlay();
}

void AGasaEffectActorDemo::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	Sphere->OnComponentBeginOverlap.AddUniqueDynamic(this, &ThisClass::OnOverlapBegin);
	Sphere->OnComponentEndOverlap.AddUniqueDynamic(this, &ThisClass::OnOverlapEnd);
}
