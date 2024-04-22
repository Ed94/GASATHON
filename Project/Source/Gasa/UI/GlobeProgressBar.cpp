#include "GlobeProgressBar.h"

#include "GasaImage.h"
#include "GasaOverlay.h"
#include "GasaProgressBar.h"
#include "GasaSizeBox.h"

#include "Components/OverlaySlot.h"
#include "Blueprint/WidgetBlueprintGeneratedClass.h"
#include "Blueprint/WidgetTree.h"
#include "Extensions/WidgetBlueprintGeneratedClassExtension.h"

#if WITH_EDITOR
#include "WidgetBlueprint.h"
#include "Kismet2/BlueprintEditorUtils.h"
#endif

using namespace Gasa;

// UGlobeProgressBar::UGlobeProgressBar(FObjectInitializer const& ObjectInitializer)
// {
// }

void UGlobeProgressBar::GenerateDesignerWidgetTemplate()
{
#if WITH_EDITOR
	UWidgetBlueprintGeneratedClass* WBG_Class = Cast<UWidgetBlueprintGeneratedClass>(GetClass());

	UPackage*         Package = WBG_Class->GetPackage();
	UWidgetBlueprint* AssetBP = Cast<UWidgetBlueprint>(Package->FindAssetInPackage());
	UWidgetTree*      WT      = AssetBP->WidgetTree;

	UWidget* AssetRoot = AssetBP->WidgetTree->RootWidget;

	UGasaSizeBox*     Asset_SB      = WT->FindWidget<UGasaSizeBox>("Root");
	UGasaOverlay*     Asset_Overlay = WT->FindWidget<UGasaOverlay>("Overlay");
	UGasaImage*       Asset_Bezel   = WT->FindWidget<UGasaImage>("Bezel");
	UGasaImage*       Asset_Glass   = WT->FindWidget<UGasaImage>("Glass");
	UGasaProgressBar* Asset_Bar     = WT->FindWidget<UGasaProgressBar>("Bar");
	if (Root_SB == nullptr)
		Asset_SB = WT->ConstructWidget<UGasaSizeBox>(UGasaSizeBox::StaticClass(), FName("Root_SB"));
	if (Overlay == nullptr)
		Asset_Overlay = WT->ConstructWidget<UGasaOverlay>(UGasaOverlay::StaticClass(), FName("Overlay"));
	if (Bezel == nullptr)
		Asset_Bezel = WT->ConstructWidget<UGasaImage>(UGasaImage::StaticClass(), FName("Bezel"));
	if (Glass == nullptr)
		Asset_Glass = WT->ConstructWidget<UGasaImage>(UGasaImage::StaticClass(), FName("Glass"));
	if (Bar == nullptr)
		Asset_Bar = WT->ConstructWidget<UGasaProgressBar>(UGasaProgressBar::StaticClass(), FName("Bar"));
	
	WT->RootWidget = Asset_SB;
	Asset_SB->ClearChildren();
	Asset_Overlay->ClearChildren();
	Asset_SB->AddChild(Asset_Overlay);
	Asset_Overlay->AddChild(Asset_Bezel);
	Asset_Overlay->AddChild(Asset_Glass);
	Asset_Overlay->AddChild(Asset_Bar);
	
	AssetBP->Modify();
	FBlueprintEditorUtils::MarkBlueprintAsStructurallyModified(AssetBP);
#endif
}

#pragma region Bindings
void UGlobeProgressBar::SetBezelStyle(FSlateBrush brush)
{
	Bezel->SetBrush( brush );
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

void UGlobeProgressBar::SetPercentage(float CurrentValue, float MaxValue)
{
	Bar->SetPercent( MaxValue > 0.f ? CurrentValue / MaxValue : 0.f );
}

void UGlobeProgressBar::SetSize(float width, float height)
{
	Root_SB->SetWidthOverride(  width );
	Root_SB->SetHeightOverride( height );
}
#pragma endregion Bindings

#pragma region Widget
void UGlobeProgressBar::SynchronizeProperties()
{
	Super::SynchronizeProperties();
}

void UGlobeProgressBar::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);
}
#pragma endregion Widget

#pragma region UserWidget
void UGlobeProgressBar::NativePreConstruct()
{
	// Super::NativePreConstruct(); - Inlined
	LLM_SCOPE_BYTAG(UI_UMG);
	const bool bIsDesignTime = IsDesignTime();

	UWidgetBlueprintGeneratedClass* WBG_Class = Cast<UWidgetBlueprintGeneratedClass>(GetClass());
	if (WBG_Class)
	{
		WBG_Class->ForEachExtension([this, bIsDesignTime](UWidgetBlueprintGeneratedClassExtension* Extension)
			{
				Extension->PreConstruct(this, bIsDesignTime);
			});
	}

	DesiredFocusWidget.Resolve(WidgetTree);

	// Blueprint Callback
	PreConstruct(bIsDesignTime);	
}

void UGlobeProgressBar::Serialize(FArchive& Ar)
{
	Super::Serialize(Ar);
}

void UGlobeProgressBar::Serialize(FStructuredArchive::FRecord Record)
{
	Super::Serialize(Record);
}
#pragma endregion UserWidget
