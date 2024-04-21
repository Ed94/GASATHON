#pragma once

#include "GasaCommon.h"
#include "WidgetController.generated.h"

UCLASS(BlueprintType)
class GASA_API UWidgetController : public UObject
{
	GENERATED_BODY()
public:

	UPROPERTY(BlueprintReadOnly, Category="Player")
	TObjectPtr<APlayerController> Controller;

	UPROPERTY(BlueprintReadOnly, Category="Player")
	TObjectPtr<APlayerState> PlayerState;

	UPROPERTY(BlueprintReadOnly, Category="Player")
	TObjectPtr<UAbilitySystemComponent> AbilitySystem;
	
	UPROPERTY(BlueprintReadOnly, Category="Player")
	TObjectPtr<UAttributeSet> Attributes;
};
