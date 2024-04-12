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
	
	AGasaCharacter();
	
#pragma region Actor
	void BeginPlay() override;
#pragma endregion Actor
};
