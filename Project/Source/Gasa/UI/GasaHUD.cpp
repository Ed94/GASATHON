#include "GasaHUD.h"

#include "GasaDevOptions.h"
#include "UI_HostWidget.h"
#include "Blueprint/UserWidget.h"

using namespace Gasa;


#pragma region HUD
void AGasaHUD::ShowHUD()
{
	Super::ShowHUD();
}
#pragma endregion HUD

#pragma region Actor
UE_DISABLE_OPTIMIZATION
void AGasaHUD::BeginPlay()
{
	Super::BeginPlay();

	HostWidget = CreateWidget<UUI_HostWidget>( GetWorld() 
		, GetDevOptions()->Template_HUD_HostUI.LoadSynchronous() );
	HostWidget->AddToViewport();
	
	bool bHostVis = HostWidget->IsVisible();
	Log(FString::Printf(TEXT("HostVIs: %s"), *FString::FromInt(bHostVis)));
}
UE_ENABLE_OPTIMIZATION
#pragma endregion Actor
