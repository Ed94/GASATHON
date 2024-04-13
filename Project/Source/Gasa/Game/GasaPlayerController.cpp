#include "GasaPlayerController.h"

#include "AbilitySystemComponent.h"
#include "Engine/LocalPlayer.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GasaPlayerState.h"
#include "Actors/CameraMount.h"
#include "Camera/CameraComponent.h"
#include "Characters/GasaCharacter.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/KismetSystemLibrary.h"

AGasaPlayerController::AGasaPlayerController()
{
	PrimaryActorTick.bCanEverTick = true;
	bAutoManageActiveCameraTarget = false;

	// Replication
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

void AGasaPlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	Cam->AttachToActor(InPawn, FAttachmentTransformRules::KeepRelativeTransform);

	AGasaPlayerState* PS      = GetPlayerState();
	AGasaCharacter* character = Cast<AGasaCharacter>(InPawn);
	// Net Owner setup ability system
	if (0)
	{
		character->AbilitySystem = PS->AbilitySystem;
		character->Attributes    = PS->Attributes;
		character->AbilitySystem->InitAbilityActorInfo(PS, character);
	}
}

void AGasaPlayerController::OnUnPossess()
{
	Super::OnUnPossess();
}

#pragma region PlayerController
void AGasaPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	// Cursor Trace
	for (int32 do_once = 0; do_once != 1; ++ do_once)
	{
		FHitResult CursorHit;
		GetHitResultUnderCursor(ECC_Pawn, false, CursorHit);
		if (! CursorHit.bBlockingHit)
			break;

		HoverPrev = HoverCurr;
		HoverCurr = Cast<AGasaCharacter>(CursorHit.GetActor());
		if (HoverPrev == nullptr)
		{
			// We didn't have a prev to de-highlight so we just need to highlight newly detected character.
			if (HoverCurr)
				HoverCurr->Highlight();

			// No matter what we need to not go to the next case as there is no previous.
			break;
		}
		//else Previous is valid...

		// We are no longer hovering the previous with no new character, we just need to de-highlight previous.		
		if ( HoverCurr == nullptr )
			HoverPrev->Dehighlight();

		// We had a prev and curr change between frames. They both don't match; we need to switch highlighting.
		else if ( HoverPrev != HoverCurr )
		{
			HoverPrev->Dehighlight();
			HoverCurr->Highlight();
		}
	}
}

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

void AGasaPlayerController::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	Cam = GetWorld()->SpawnActor<ACameraMount>(CamClass, FActorSpawnParameters() );
	SetViewTarget(Cam);
}

void AGasaPlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

#if 0
	switch (HighlightState)
	{
		case EHighlight::Disabled:
		break;
		case EHighlight::Enabled:
		{
			UCapsuleComponent* Capsule = GetCapsuleComponent();
				
			UKismetSystemLibrary::DrawDebugCapsule(this
				, Capsule->GetComponentLocation()
				, Capsule->GetScaledCapsuleHalfHeight()
				, Capsule->GetScaledCapsuleRadius()
				, Capsule->GetComponentRotation()
				, HighlightColor
				, 0.f
				, 1.f
			);
		}
		break;
	}
#endif
}
#pragma endregion Actor
