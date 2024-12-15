#include "TextValueRow.h"

#include "Components/TextBlock.h"
#include "UI/GasaSizeBox.h"


void UAttributeMenu_TextValueRow::SetAttributeName(FText Name)
{
	TB_AttributeName->SetText(Name);
}

void UAttributeMenu_TextValueRow::SetBoxSize(float Width, float Height)
{
	SB_Root->SetWidthOverride(Width);
	SB_Root->SetHeightOverride(Height);
}

void UAttributeMenu_TextValueRow::NativePreConstruct()
{
	Super::NativePreConstruct();
}
