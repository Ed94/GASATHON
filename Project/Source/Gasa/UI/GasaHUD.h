#pragma once

#include "GasaCommon.h"
#include "GameFramework/HUD.h"

#include "GasaHUD.generated.h"


UCLASS()
class GASA_API AGasaHUD : public AHUD
{
	GENERATED_BODY()
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TObjectPtr<UUI_HostWidget> HostWidget;

#pragma region HUD	
	void ShowHUD() override;
#pragma endregion HUD	

#pragma region Actor
	void BeginPlay() override;

#pragma endregion Actor
};
