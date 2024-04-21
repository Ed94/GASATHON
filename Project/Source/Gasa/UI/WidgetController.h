#pragma once

#include "GasaCommon.h"
#include "WidgetController.generated.h"

USTRUCT(BlueprintType)
struct GASA_API FWidgetControllerData
{
	GENERATED_BODY()

	FWidgetControllerData() = default;

	FWidgetControllerData(AGasaPlayerController*   Controller
						, AGasaPlayerState*        PlayerState
						, UAbilitySystemComponent* AbilitySystem
						, UAttributeSet*           Attributes )
#if 1
	: Controller(Controller)
	, PlayerState(PlayerState)
	, AbilitySystem(AbilitySystem)
	, Attributes(Attributes)
#endif
	{
#if 0
		this->Controller    = Controller;
		this->PlayerState   = PlayerState;
		this->AbilitySystem = AbilitySystem;
		this->Attributes    = Attributes;
#endif
	}
	
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
};
