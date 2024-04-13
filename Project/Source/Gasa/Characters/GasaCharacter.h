#pragma once

#include "AbilitySystemInterface.h"
#include "GameFramework/Character.h"

#include "GasaCommon.h"
#include "Game/GasaPlayerState.h"

#include "GasaCharacter.generated.h"

UENUM(BlueprintType)
enum class EHighlight : uint8
{
	Disabled,
	Enabled,
};

UCLASS(Abstract)
class GASA_API AGasaCharacter : public ACharacter
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
	
#pragma region Combat
	UPROPERTY(EditAnywhere, Category="Combat")
	TObjectPtr<USkeletalMeshComponent> Weapon;
#pragma endregion Combat

#pragma region Highlighting
	static constexpr float HighlightStencilDepth = 256.0;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Highlighting")
	EHighlight HighlightState;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Highlighting")
	FLinearColor HighlightColor;

	UFUNCTION(BlueprintCallable, Category="Highlighting")
	void SetHighlight( EHighlight Desired );

	UFUNCTION(BlueprintCallable, Category="Highlighting")
	FORCEINLINE void Highlight() { SetHighlight(EHighlight::Enabled); };
	
	UFUNCTION(BlueprintCallable, Category="Highlighting")
	FORCEINLINE void Dehighlight() { SetHighlight(EHighlight::Disabled); };
#pragma endregion Highlighting

	AGasaCharacter();

	FORCEINLINE AGasaPlayerState* GetGasaPlayerState() { return GetPlayerState<AGasaPlayerState>(); }
	
#pragma region IAbilitySystem
	FORCEINLINE UAttributeSet*           GetAttributes()                            { return Attributes; }
	FORCEINLINE UAbilitySystemComponent* GetAbilitySystemComponent() const override { return AbilitySystem; }
#pragma endregion IAbilitySystem

#pragma region Pawn
	void PossessedBy(AController* NewController) override;

	void OnRep_PlayerState() override;
#pragma endregion Pawn
	
#pragma region Actor
	void BeginPlay() override;

	void Tick(float DeltaSeconds) override;
#pragma endregion Actor
};

namespace Gasa
{
	// UGasaAbilitySystemComp* GetAbilitySystem(AGasaCharacter* Object)
	// {
	// 	
	// }
}
