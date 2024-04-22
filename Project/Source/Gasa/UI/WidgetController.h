#pragma once

#include "GasaCommon.h"
#include "WidgetController.generated.h"

USTRUCT(BlueprintType)
struct GASA_API FWidgetControllerData
{
	GENERATED_BODY()
public:
	FWidgetControllerData() = default;

	FWidgetControllerData
	( AGasaPlayerController*   Controller
	, AGasaPlayerState*        PlayerState
	, UAbilitySystemComponent* AbilitySystem
	, UAttributeSet*           Attributes )
	: Controller(Controller)
	, PlayerState(PlayerState)
	, AbilitySystem(AbilitySystem)
	, Attributes(Attributes)
	{}
	
	UPROPERTY(BlueprintReadOnly, Category="Player")
	TObjectPtr<AGasaPlayerController> Controller;

	UPROPERTY(BlueprintReadOnly, Category="Player")
	TObjectPtr<AGasaPlayerState> PlayerState;

	UPROPERTY(BlueprintReadOnly, Category="Player")
	TObjectPtr<UAbilitySystemComponent> AbilitySystem;
	
	UPROPERTY(BlueprintReadOnly, Category="Player")
	TObjectPtr<UAttributeSet> Attributes;
};

UCLASS(Blueprintable)
class GASA_API UWidgetController : public UObject
{
	GENERATED_BODY()
public:

	UPROPERTY(BlueprintReadOnly, Category="Player")
	FWidgetControllerData Data;

	UFUNCTION()
	virtual void BroadcastInitialValues() {};
	virtual void BindCallbacksToDependencies() {};
};
