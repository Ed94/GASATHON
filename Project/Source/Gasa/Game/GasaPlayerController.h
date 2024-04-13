#pragma once

#include "GasaCommon.h"
#include "GameFramework/PlayerController.h"

#include "GasaPlayerController.generated.h"


UCLASS(Blueprintable)
class GASA_API AGasaPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
#pragma region Camera
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<ACameraMount> CamClass;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<ACameraMount> Cam;
#pragma endregion Camera

		// This will be implemented in the base until it needs to be lifted into an abstraction.
#if 0
#pragma region Highlighting
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Highlighting")
	EHighlight HighlightState;
	
	UFUNCTION(BlueprintCallable, Category="Highlighting")
	void SetHighlight( EHighlight Desired );

	UFUNCTION(BlueprintCallable, Category="Highlighting")
	FORCEINLINE void Highlight() { SetHighlight(EHighlight::Enabled); };
	
	UFUNCTION(BlueprintCallable, Category="Highlighting")
	FORCEINLINE void Dehighlight() { SetHighlight(EHighlight::Disabled); };
#pragma endregion Highlighting
#endif
	
#pragma region Input
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<AGasaCharacter> HoverPrev;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<AGasaCharacter> HoverCurr;
	
	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputMappingContext> IMC;

	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputAction> IA_Move;
#pragma endregion Input
	
	AGasaPlayerController();

	void Move(FInputActionValue const& ActionValue);
	
#pragma region PlayerController
	void OnPossess(APawn* InPawn) override;

	void OnUnPossess() override;
	
	void PlayerTick(float DeltaTime) override;
	
	void SetupInputComponent() override;
#pragma endregion PlayerController

#pragma region Actor
	void BeginPlay() override;

	void PostInitializeComponents() override;

	void Tick(float DeltaSeconds) override;
#pragma endregion Actor
};

namespace Gasa
{
	inline
	AGasaPlayerController* GetPrimaryPlayerController(UObject* Context)
	{
		UWorld* World = GEngine->GetWorldFromContextObject(Context, EGetWorldErrorMode::LogAndReturnNull);
		if (World == nullptr)
		{
			Log("World is null... are you running in a proper context?", ELogV::Error);
			return nullptr;
		}
		return Cast<AGasaPlayerController>(World->GetFirstPlayerController());
	}
}
