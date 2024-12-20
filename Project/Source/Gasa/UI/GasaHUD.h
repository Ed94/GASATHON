﻿#pragma once

#include "GasaCommon.h"
#include "GameFramework/HUD.h"

#include "GasaHUD.generated.h"


UCLASS()
class GASA_API AGasaHUD : public AHUD
{
	GENERATED_BODY()
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TObjectPtr<UHUDHostWidget> HostWidget;

	// This should only be accessed AFTER InitOverlay is called. Otherwise, it will be null
	// See references to InitOverlay or docs for lifetime.
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TObjectPtr<UHostWidgetController> HostWidgetController;
	
	void InitHostWidget(FWidgetControllerData const* WidgetControllerData);
	
#pragma region HUD
	void DrawHUD() override;
	void ShowHUD() override;
#pragma endregion HUD	

#pragma region Actor
	void BeginPlay() override;

	void Tick(float DeltaSeconds) override;
#pragma endregion Actor
};
