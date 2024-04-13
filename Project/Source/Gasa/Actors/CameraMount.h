#pragma once

#include "GasaCommon.h"
#include "CameraMount.generated.h"

UCLASS(Blueprintable)
class GASA_API ACameraMount : public AActor
{
	GENERATED_BODY()
public:
#pragma region Camera
	UPROPERTY(EditAnywhere, Category="Camera")
	TObjectPtr<UCameraComponent> Camera;
	
	UPROPERTY(EditAnywhere, Category="Camera")
	TObjectPtr<USpringArmComponent> CamSpringArm;
#pragma endregion Camera

	ACameraMount();

#pragma region Actor
	void PostInitializeComponents() override;
#pragma endregion Actor
};

