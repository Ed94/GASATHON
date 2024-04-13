#pragma once


#include "AbilitySystemInterface.h"
#include "GameFramework/PlayerState.h"

#include "GasaCommon.h"

#include "GasaPlayerState.generated.h"

UCLASS(Blueprintable)
class GASA_API AGasaPlayerState : public APlayerState
	, public IAbilitySystemInterface
{
	GENERATED_BODY()
public:
#pragma region Ability System
	UPROPERTY(EditAnywhere, Category="Ability System")
	bool bAutoAbilitySystem = true;
	
	UPROPERTY(EditAnywhere, Category="Ability System")
	TObjectPtr<UAbilitySystemComponent> AbilitySystem;

	UPROPERTY(EditAnywhere, Category="Ability System")
	TObjectPtr<UAttributeSet> Attributes;
#pragma endregion Ability System
	
	AGasaPlayerState();

#pragma region IAbilitySystem
	FORCEINLINE UAttributeSet*           GetAttributes()                            { return Attributes; }
	FORCEINLINE UAbilitySystemComponent* GetAbilitySystemComponent() const override { return AbilitySystem; }
#pragma endregion IAbilitySystem
};
