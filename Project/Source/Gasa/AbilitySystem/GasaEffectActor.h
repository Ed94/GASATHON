#pragma once

#include "GasaCommon.h"
#include "Actors/GasaActor.h"
#include "GameFramework/Actor.h"

#include "GasaEffectActor.generated.h"

UENUM(BlueprintType)
enum class EEffectUsagePolicy : uint8
{
	None               = 0 UMETA(Hidden),
	ApplyOnOverlap     = bit(0),
	ApplyOnEndOverlap  = bit(1),
	RemoveOnOverlap    = bit(3),
	RemoveOnEndOverlap = bit(4),
};

constexpr int32 DefaultEffectUsagePolicy = (int32(EEffectUsagePolicy::RemoveOnEndOverlap));

UCLASS()
class GASA_API AGasaEffectActor : public AGasaActor
{
	GENERATED_BODY()
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay Effects")
	TSubclassOf<UGameplayEffect> InstantEffectClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay Effects", meta=(Bitmask, BitmaskEnum = EEffectUsagePolicy))
	int32 InstantEffectUsage;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay Effects")
	TSubclassOf<UGameplayEffect> DurationEffectClass;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay Effects", meta=(Bitmask, BitmaskEnum = EEffectUsagePolicy))
	int32 DurationEffectUsage;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay Effects")
	TSubclassOf<UGameplayEffect> InfiniteEffectClass;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay Effects", meta=(Bitmask, BitmaskEnum = EEffectUsagePolicy))
	int32 InfiniteEffectUsage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay Effects")
	bool bDestroyOnEffectRemoval = false;
	
	AGasaEffectActor();

	UFUNCTION(BlueprintCallable, Category = "Gameplay Effects")
	void ApplyEffectToActor(AActor* Actor, TSubclassOf<UGameplayEffect> EffectClass );

	UFUNCTION(BlueprintCallable)
	void OnOverlap(AActor* Actor);

	UFUNCTION(BlueprintCallable)
	void OnEndOverlap(AActor* Actor);
};

