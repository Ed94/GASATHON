#pragma once

#include "GasaCommon.h"
#include "Actors/GasaActor.h"
#include "ActiveGameplayEffectHandle.h"
#include "GameFramework/Actor.h"

#include "GasaEffectActor.generated.h"

struct FActiveGameplayEffectHandle;

UENUM(BlueprintType)
enum class EInstantEffectUsagePolicy : uint8
{
	DoNotApply,
	ApplyOnOverlap,
	ApplyOnEndOverlap,
};

UENUM(BlueprintType, meta = (Bitflags, UseEnumValuesAsMaskValuesInEditor = "true"))
enum class EEffectUsagePolicy : uint8
{
	None               = 0 UMETA(Hidden),
	ApplyOnOverlap     = bit(0),
	ApplyOnEndOverlap  = bit(1),
	RemoveOnOverlap    = bit(2),
	RemoveOnEndOverlap = bit(3),
};

constexpr int32 DefaultEffectUsagePolicy = (int32(EEffectUsagePolicy::RemoveOnEndOverlap));

UCLASS()
class GASA_API AGasaEffectActor : public AGasaActor
{
	GENERATED_BODY()
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay Effects")
	TSubclassOf<UGameplayEffect> InstantEffectClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay Effects")
	EInstantEffectUsagePolicy InstantEffectUsage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay Effects")
	TSubclassOf<UGameplayEffect> DurationEffectClass;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay Effects", meta=(Bitmask, BitmaskEnum = "/Script/Gasa.EEffectUsagePolicy"))
	int32 DurationEffectUsage;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay Effects")
	TSubclassOf<UGameplayEffect> InfiniteEffectClass;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay Effects", meta=(Bitmask, BitmaskEnum = "/Script/Gasa.EEffectUsagePolicy"))
	int32 InfiniteEffectUsage;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay Effects")
	bool bDestroyOnEffectRemoval;

	TMap<FActiveGameplayEffectHandle, UAbilitySystemComponent*> ActiveEffectsToRemove;
	using ActiveEffectEntry = TTuple<FActiveGameplayEffectHandle, UAbilitySystemComponent*>;
	
	FActiveGameplayEffectHandle ActiveDuration;
	FActiveGameplayEffectHandle ActiveInfinite;

	AGasaEffectActor();

	UFUNCTION(BlueprintCallable, Category = "Gameplay Effects")
	void ApplyEffectToActor(AActor* Actor, TSubclassOf<UGameplayEffect> EffectClass, bool bRemoveOnEndOverlap = false);

	UFUNCTION(BlueprintCallable)
	void OnOverlap(AActor* Actor);

	UFUNCTION(BlueprintCallable)
	void OnEndOverlap(AActor* Actor);
};

