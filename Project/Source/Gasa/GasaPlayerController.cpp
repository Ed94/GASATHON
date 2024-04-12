﻿#include "GasaPlayerController.h"

#include "Engine/LocalPlayer.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

AGasaPlayerController::AGasaPlayerController()
{
	bReplicates = true;
}

void AGasaPlayerController::Move(FInputActionValue const& ActionValue)
{
	APawn* pawn = GetPawn<APawn>();
	if (pawn == nullptr )
		return;
	
// Note(Ed): I did the follow optimization for practice, they are completely unnecessary for this context.
#if 0
	FVector2D AxisV     = ActionValue.Get<FVector2D>();
	FRotator ControlRot = GetControlRotation();
	FRotator YawRot     = FRotator(0.f, ControlRot.Yaw, 0.f);

	FVector FwdDir   = FRotationMatrix(YawRot).GetUnitAxis(EAxis::X);
	FVector RightDir = FRotationMatrix(YawRot).GetUnitAxis(EAxis::Y);

	PPawn->AddMovementInput(FwdDir,   AxisV.Y);
	PPawn->AddMovementInput(RightDir, AxisV.X);
#else
	FVector2f AxisV = FVector2f(ActionValue.Get<FVector2D>());

	FQuat4f // FQuat isomorphic to FRotor (Hypothetical Def)
	ControlRotor = FQuat4f(GetControlRotation().Quaternion());
	// ControlRotor.Normalize();  // The Quaternion should always be a versor with UE...

	FVector3f HorizontalForward = ControlRotor.RotateVector(FVector3f::ForwardVector);
	// HorizontalForward.Normalize();

	// TODO(Ed): Profile which is faster just to know... (atan2 vs FindBetweenVectors)
	// HorizontalForward.Z = 0;
	// FQuat4f
	// YawRotor = FQuat4f::FindBetweenVectors(FVector3f::ForwardVector, HorizontalForward);
	// YawRotor.Normalize(); // The Quaternion should always be a versor with UE...

	// Need only one axis of rotation so this might be a possible optimization
	float   YawAngle = FMath::Atan2(HorizontalForward.Y, HorizontalForward.X);
	FQuat4f YawRotor = FQuat4f(FVector3f::UpVector, YawAngle);

	// Rotate the combined input by the yaw rotor to get the movement direction
	FVector MoveDir = (FVector) YawRotor.RotateVector( FVector3f(AxisV.Y, AxisV.X, 0.f));
	pawn->AddMovementInput( MoveDir );
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
