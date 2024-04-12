#include "GasaPlayerController.h"

#include "Engine/LocalPlayer.h"
#include "EnhancedInputSubsystems.h"

AGasaPlayerController::AGasaPlayerController()
{
	bReplicates = true;
}

void AGasaPlayerController::BeginPlay()
{
	Super::BeginPlay();

	check(IMC);
	UEnhancedInputLocalPlayerSubsystem*
	EILP_Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	check(EILP_Subsystem);
	EILP_Subsystem->AddMappingContext(IMC, 0);
	{
		bShowMouseCursor   = true;
		DefaultMouseCursor = EMouseCursor::Default;
		FInputModeGameAndUI MouseMode;
		MouseMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
		MouseMode.SetHideCursorDuringCapture(false);
		SetInputMode(MouseMode);
	}
}
