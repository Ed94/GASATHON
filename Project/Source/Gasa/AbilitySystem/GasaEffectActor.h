﻿#pragma once

#include "GasaCommon.h"

#include "GasaEffectActor.generated.h"

UCLASS()
class GASA_API AGasaEffectActor : public AActor
{
	GENERATED_BODY()
public:

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UStaticMeshComponent> Mesh;
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USphereComponent> Sphere;
	
	AGasaEffectActor();

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