#pragma once

#include "GasaCommon.h"
#include "GameFramework/Character.h"

#include "GasaCharacter.generated.h"

UCLASS(Abstract)
class GASA_API AGasaCharacter : public ACharacter
{
	GENERATED_BODY()
public:
#pragma region Camera
	UPROPERTY(EditAnywhere, Category="Camera")
	UCameraComponent* Camera;
	
	UPROPERTY(EditAnywhere, Category="Camera")
	USpringArmComponent* CamSpringArm;
#pragma endregion Camera
	
#pragma region Combat
	UPROPERTY(EditAnywhere, Category="Combat")
	TObjectPtr<USkeletalMeshComponent> Weapon;
#pragma endregion Combat

	// This will be implemented in the base until it needs to be lifted into an abstraction.
#pragma region Highlighting
	void SetHighlight( EHighlight desired );

	UFUNCTION(BlueprintCallable)
	FORCEINLINE void Highlight() { SetHighlight(EHighlight::Disabled); };
	
	UFUNCTION(BlueprintCallable)
	FORCEINLINE void Dehighlight() { SetHighlight(EHighlight::Disabled); };
#pragma endregion Highlighting
	
	AGasaCharacter();
	
#pragma region Actor
	void BeginPlay() override;
#pragma endregion Actor
};
