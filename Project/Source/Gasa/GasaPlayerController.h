#pragma once

#include "GasaCommon.h"
#include "GameFramework/PlayerController.h"

#include "GasaPlayerController.generated.h"


UCLASS(Blueprintable)
class GASA_API AGasaPlayerController : public APlayerController
{
	GENERATED_BODY()
public:

#pragma region Input
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	AGasaCharacter* HoverPrev;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	AGasaCharacter* HoverCurr;
	
	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputMappingContext> IMC;

	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputAction> IA_Move;
#pragma endregion Input
	
	AGasaPlayerController();

	void Move(FInputActionValue const& ActionValue);
	
#pragma region PlayerController
	void PlayerTick(float DeltaTime) override;
	
	void SetupInputComponent() override;
#pragma endregion PlayerController

#pragma region Actor
	void BeginPlay() override;
#pragma endregion Actor
};
