#include "FramedValue.h"

#include "UI/GasaImage.h"
#include "Components/TextBlock.h"
#include "UI/GasaSizeBox.h"

void UAttributeMenu_FramedValue::SetBackgroundBrush(FSlateBrush Brush)
{
	BG->SetBrush(Brush);
}

void UAttributeMenu_FramedValue::SetBorderBrush(FSlateBrush Brush)
{
	Border->SetBrush(Brush);
}

void UAttributeMenu_FramedValue::SetBoxSize(float Width, float Height)
{
	SB_Root->SetWidthOverride(Width);
	SB_Root->SetHeightOverride(Height);
}

void UAttributeMenu_FramedValue::SetText(FText Content)
{
	Value->SetText(Content);
}
