#include "GlobeProgressBar.h"

#include "GasaImage.h"
#include "GasaProgressBar.h"
#include "GasaSizeBox.h"
#include "Components/OverlaySlot.h"

// UGlobeProgressBar::UGlobeProgressBar(FObjectInitializer const& ObjectInitializer)
// {
// }

void UGlobeProgressBar::SetBackgroundStyle(FSlateBrush brush)
{
	BG->SetBrush( brush );
}

void UGlobeProgressBar::SetBarPadding(FMargin margin )
{
	UOverlaySlot* BarSlot = CastChecked<UOverlaySlot>(Bar->Slot);
	BarSlot->SetPadding( margin );
}

void UGlobeProgressBar::SetBarStyle(FProgressBarStyle style)
{
	Bar->SetWidgetStyle( style );
}

void UGlobeProgressBar::SetGlassPadding(FMargin margin)
{
	UOverlaySlot* GlassSlot = CastChecked<UOverlaySlot>(Glass->Slot);
	GlassSlot->SetPadding(margin);
}

void UGlobeProgressBar::SetGlassStyle(FSlateBrush brush)
{
	Glass->SetBrush(brush);
}

void UGlobeProgressBar::SetSize(float width, float height)
{
	SizeBox_Root->SetWidthOverride(  width );
	SizeBox_Root->SetHeightOverride( height );
}

#if 0
void UGlobeProgressBar::UpdateSize()
{
	
}

void UGlobeProgressBar::UpdateBackground()
{
}
#endif

#pragma region UserWidget
void UGlobeProgressBar::NativePreConstruct()
{
	Super::NativePreConstruct();
}
#pragma endregion UserWidget
