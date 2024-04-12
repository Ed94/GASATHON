#pragma once

#include "GasaCommon.h"

#include "GasaPlayerController.generated.h"

UCLASS(Blueprintable)
class GASA_API AGasaPlayerController : public APlayerController
{
	GENERATED_BODY()
public:

	TObjectPtr<UInputMappingContext> IMC;
	
	AGasaPlayerController();

	void BeginPlay() override;
};
