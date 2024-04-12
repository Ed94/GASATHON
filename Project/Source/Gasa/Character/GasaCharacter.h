#pragma once

#include "GameFramework/Character.h"

#include "GasaCharacter.generated.h"

UCLASS(Abstract)
class GASA_API AGasaCharacter : public ACharacter
{
	GENERATED_BODY()
public:
	AGasaCharacter();

#pragma region Combat
	UPROPERTY(EditAnywhere, Category="Combat")
	TObjectPtr<USkeletalMeshComponent> Weapon;
#pragma endregion Combat
	
#pragma region Actor
	void BeginPlay() override;
#pragma endregion Actor
};
