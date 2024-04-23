#pragma once

#include "GasaCommon.h"
#include "Actors/GasaActor.h"
#include "GameFramework/Actor.h"

#include "GasaEffectActorDemo.generated.h"

// Old demonstration code used before part 37.
UCLASS()
class GASA_API AGasaEffectActorDemo : public AGasaActor
{
	GENERATED_BODY()
public:

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UStaticMeshComponent> Mesh;
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USphereComponent> Sphere;
	
	AGasaEffectActorDemo();

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent
		, AActor*              OtherActor
		, UPrimitiveComponent* OtherComp
		, int32                OtherBodyIndex
		, bool                 bFromSweep
		, FHitResult const&    SweepResult);

	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComponent
		, AActor*                          OtherActor
		, UPrimitiveComponent*             OtherComp
		, int32                            OtherBodyIndex);
	
#pragma region Actor
	void BeginPlay() override;
	
	void PostInitializeComponents() override;
#pragma endregion Actor
};
