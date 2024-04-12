#include "GasaPlayerController.h"

#include "Engine/LocalPlayer.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

AGasaPlayerController::AGasaPlayerController()
{
	bReplicates = true;
}

void AGasaPlayerController::Move(FInputActionValue const& ActionValue)
{
#if 0
	FVector2D AxisV     = ActionValue.Get<FVector2D>();
	FRotator ControlRot = GetControlRotation();
	FRotator YawRot     = FRotator(0.f, ControlRot.Yaw, 0.f);

	FVector FwdDir   = FRotationMatrix(YawRot).GetUnitAxis(EAxis::X);
	FVector RightDir = FRotationMatrix(YawRot).GetUnitAxis(EAxis::Y);

	APawn* Pawn = GetPawn<APawn>();
	if (Pawn)
	{
		Pawn->AddMovementInput(FwdDir,   AxisV.Y);
		Pawn->AddMovementInput(RightDir, AxisV.X);
	}
#else
	FVector2f AxisV = FVector2f(ActionValue.Get<FVector2D>());
	FQuat // FQuat isomorphic to FRotor (Hypothetical Def)
	ControlRotor = GetControlRotation().Quaternion();
	// ControlRotor.Normalize();  // The Quaternion should always be a versor with UE...

	FQuat4f
	YawRotor = FQuat4f(FVector3f::UpVector, ControlRotor.GetAngle());
	// YawRotor.Normalize(); // The Quaternion should always be a versor with UE...

	FVector3f FwdDir   = YawRotor.RotateVector(FVector3f::ForwardVector);
	FVector3f RightDir = YawRotor.RotateVector(FVector3f::RightVector);

	APawn* PPawn = GetPawn<APawn>();
	if (PPawn)
	{
		PPawn->AddMovementInput(FVector(FwdDir),   AxisV.Y);
		PPawn->AddMovementInput(FVector(RightDir), AxisV.X);
	}
#endif
}

#pragma region PlayerController
void AGasaPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	UEnhancedInputComponent*
	EIC = CastChecked<UEnhancedInputComponent>(InputComponent);
	{
		EIC->BindAction(IA_Move, ETriggerEvent::Triggered, this, &ThisClass::Move);	
	}
}
#pragma endregion PlayerController

#pragma region Actor
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
#pragma endregion Actor
