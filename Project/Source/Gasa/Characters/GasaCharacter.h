#pragma once

#include "GasaCommon.h"
#include "GameFramework/Character.h"

#include "GasaCharacter.generated.h"

UENUM(BlueprintType)
enum class EHighlight : uint8
{
	Disabled,
	Enabled,
};

UCLASS(Abstract)
class GASA_API AGasaCharacter : public ACharacter
{
	GENERATED_BODY()
public:
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
	
#pragma region Actor
	void BeginPlay() override;

	void Tick(float DeltaSeconds) override;
#pragma endregion Actor
};
