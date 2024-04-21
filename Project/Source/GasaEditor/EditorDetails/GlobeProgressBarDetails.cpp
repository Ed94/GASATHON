#include "GlobeProgressBarDetails.h"

#include "BaseWidgetBlueprint.h"
#include "BlueprintEditor.h"
#include "GasaEditorCommon.h"
#include "DetailCategoryBuilder.h"
#include "DetailLayoutBuilder.h"
#include "DetailWidgetRow.h"
#include "PropertyCustomizationHelpers.h"
#include "Blueprint/WidgetBlueprintGeneratedClass.h"
#include "Blueprint/WidgetTree.h"
#include "Components/ProgressBar.h"
#include "Gasa/UI/GlobeProgressBar.h"
#include "Kismet2/BlueprintEditorUtils.h"
#include "UI/GasaProgressBar.h"

UE_DISABLE_OPTIMIZATION
void FGlobeProgressBarDetails::CustomizeDetails(IDetailLayoutBuilder& LayoutBuilder)
{
	IDetailCategoryBuilder& GlobeCategory = LayoutBuilder.EditCategory("Globe");

	UObject* GlobeBar = nullptr;
	UGlobeProgressBar* Globe = nullptr;
	for (TWeakObjectPtr<UObject> Object : LayoutBuilder.GetSelectedObjects())
	{
		if ( ! Object.IsValid())
			return;

		Globe = Cast<UGlobeProgressBar>(Object.Get());
		if (Globe)
			break;
	}

	if (Globe && Globe->Bar)
	{
		auto StyleFillImage = Globe->Bar->GetWidgetStyle().FillImage.GetResourceObject();
		Thumbnail = MakeShareable(new FAssetThumbnail(FAssetData(StyleFillImage), 64, 64, LayoutBuilder.GetThumbnailPool()));
	}
	
	TSharedPtr<IPropertyHandle>
	ProgressBarStyle = LayoutBuilder.GetProperty(GET_MEMBER_NAME_CHECKED(UGlobeProgressBar, Bar), UGlobeProgressBar::StaticClass());
	ProgressBarStyle->GetValue(GlobeBar);
	if (ProgressBarStyle && ! ProgressBarStyle->IsValidHandle())
		return;

	// This can't be done, UE widget parenting forces the parent widget's hierarchy to be immutable at 'design time'.
	// This is because a proper clone of the UWidgetBlueprintGeneratedClass parent's widget tree is not done.
	// Instead... I don't even know what they are even doing with the widget tree because somehow they still have a unique widget tree
	// for at least the child widget.
	// All code paths related to this are not navigable in a reasonable amount of time.
	// So I don't even know why this failure point exist architecturally...
#if 0
	// TSharedPtr<IPropertyHandle> WidgetStyle = ProgressBarStyleHandle->GetChildHandle("WidgetStyle");
	// if ( ! WidgetStyle.IsValid())
	// 	return;
	IDetailPropertyRow& ProgressBarRow = LayoutBuilder.AddPropertyToCategory(ProgressBarStyle);
	
	FDetailWidgetRow& RowWidget = ProgressBarRow.CustomWidget();
	{
		FDetailWidgetDecl& RowNameWidget = RowWidget.NameContent();
		{
			TSharedRef<STextBlock>
			TextBlock = SNew(STextBlock);
			TextBlock->SetText(FText::FromString(TEXT("Bar Fill Material")));
			TextBlock->SetFont(LayoutBuilder.GetDetailFont());
			RowNameWidget.Widget = TextBlock;
		}

		FDetailWidgetDecl& RowValueWidget = RowWidget.ValueContent();
		TSharedRef<SHorizontalBox> HBox = SNew(SHorizontalBox);
		{
			SHorizontalBox::FSlot::FSlotArguments ThumbnailSlot = SHorizontalBox::Slot();
			{
				TSharedRef<SBox> ThumbnailBox = SNew(SBox);
				ThumbnailBox->SetWidthOverride(64);
				ThumbnailBox->SetHeightOverride(64);

				if ( Thumbnail.IsValid() )
					ThumbnailBox->SetContent( Thumbnail->MakeThumbnailWidget());
				else
					ThumbnailBox->SetContent( SNullWidget::NullWidget );

				ThumbnailSlot.AutoWidth();
				ThumbnailSlot.AttachWidget( ThumbnailBox );
			}

			SHorizontalBox::FSlot::FSlotArguments DropDownSlot = SHorizontalBox::Slot();
			{
				TSharedRef<SObjectPropertyEntryBox> EntryBox = SNew(SObjectPropertyEntryBox);
				{
					SObjectPropertyEntryBox::FArguments Args;
					Args.PropertyHandle(ProgressBarStyle);
					Args.AllowClear(false);
					// Args.OnShouldFilterAsset_Lambda( [&](FAssetData const& Asset) -> bool
					// {
					// 	FString const AssetPath = Asset.ObjectPath.ToString();
					// 	// Add conditional filters here
					// 	return true;
					// });
					Args.DisplayThumbnail(false);
					Args.OnObjectChanged_Lambda( [this, Globe, &ProgressBarStyle, &LayoutBuilder](FAssetData const& Asset)
					{
						if ( ! Asset.IsValid() || ! Thumbnail.IsValid() || ! Globe || ! Globe->Bar )
							return;
						
						FProgressBarStyle
						Style = Globe->Bar->GetWidgetStyle();
						Style.FillImage.SetResourceObject(Asset.GetAsset());

						// Get the Blueprint that owns this widget and mark it as modified
						UBaseWidgetBlueprint* GlobeBP = Cast<UBaseWidgetBlueprint>(Globe->WidgetGeneratedBy);
						if (GlobeBP != nullptr)
						{
							GlobeBP->Modify();
							UObject* CDO = GlobeBP->GeneratedClass->GetDefaultObject();
							UGlobeProgressBar* GlobeCDO = Cast<UGlobeProgressBar>(CDO);

							UWidget* PossibleWidget = Cast<UBaseWidgetBlueprint>(GlobeBP)->WidgetTree->FindWidget("Bar");
							if (PossibleWidget)
							{
								UGasaProgressBar* BarWidget = Cast<UGasaProgressBar>(PossibleWidget);
								BarWidget->SetWidgetStyle(Style);
								GlobeBP->MarkPackageDirty();
							}
							else // Its parent is it.
							{
								UWidgetBlueprintGeneratedClass* Parent = Cast<UWidgetBlueprintGeneratedClass>(GlobeBP->ParentClass);
								UPackage* Pkg = Parent->GetOuterUPackage();

								PossibleWidget = Parent->GetWidgetTreeArchetype()->FindWidget("Bar");
								if (PossibleWidget)
								{
									GlobeCDO->Bar = GlobeCDO->WidgetTree->ConstructWidget<UGasaProgressBar>( PossibleWidget->GetClass(), "Bar" );
									Globe->Bar = GlobeCDO->Bar;
									GlobeCDO->Modify();
									GlobeCDO->MarkPackageDirty();
								}
							}
						}

						Globe->SetBarStyle(Style);
						Globe->Bar->Modify();
						Globe->Modify();

						Thumbnail->SetAsset(Asset);
						Thumbnail->RefreshThumbnail();
					});
					// Args.CustomResetToDefault(FResetToDefaultOverride::Hide());
					Args.DisplayBrowse(true);
					EntryBox->Construct(Args);				
				}

				DropDownSlot.AutoWidth();
				DropDownSlot.AttachWidget(EntryBox);
			}
			
			SHorizontalBox::FArguments Args = SHorizontalBox::FArguments();
			Args.operator+(ThumbnailSlot);
			Args.operator+(DropDownSlot);
			HBox->Construct(Args);
			RowValueWidget.Widget = HBox;
		}	
	}
#endif
}

bool FGlobeProgressBarDetails::CheckAsset(FAssetData const& Asset)
{
	return true;
}
UE_ENABLE_OPTIMIZATION
