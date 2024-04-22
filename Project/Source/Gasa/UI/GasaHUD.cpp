#include "GasaHUD.h"
#include "GasaHUD_Inlines.h"

#include "GasaDevOptions.h"
#include "HUDHostWidget.h"
#include "Blueprint/UserWidget.h"
using namespace Gasa;

void AGasaHUD::InitHostWidget(FWidgetControllerData const* WidgetControllerData)
{
	HostWidget = CreateWidget<UHUDHostWidget>( GetWorld() 
		, GetDevOptions()->Template_HUD_HostUI.LoadSynchronous() );

	HostWidgetController = NewObject<UHostWidgetController>(this, GetDevOptions()->Template_HostWidgetController.Get());
	HostWidgetController->Data = (* WidgetControllerData);
	HostWidget->SetWidgetController(HostWidgetController);
	HostWidgetController->BindCallbacksToDependencies();
	
	HostWidgetController->BroadcastInitialValues();
	HostWidget->AddToViewport();
}

#pragma region HUD
void AGasaHUD::ShowHUD()
{
	Super::ShowHUD();
}
#pragma endregion HUD

#pragma region Actor
void AGasaHUD::BeginPlay()
{
	Super::BeginPlay();
}
#pragma endregion Actor
