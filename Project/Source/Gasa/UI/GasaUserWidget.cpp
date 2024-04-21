#include "GasaUserWidget.h"

#include "Blueprint/WidgetBlueprintGeneratedClass.h"
#include "Blueprint/WidgetTree.h"
#include "Components/HorizontalBoxSlot.h"
#include "Components/Overlay.h"
#include "Components/OverlaySlot.h"
#include "Components/ScaleBoxSlot.h"
#include "Components/ScrollBoxSlot.h"
#include "Components/SizeBoxSlot.h"
#include "Components/VerticalBoxSlot.h"

#if WITH_EDITOR
#include "WidgetBlueprint.h"
#include "Kismet2/BlueprintEditorUtils.h"
#endif

#if 0
UWidget* UMyModalDialog::DeepDuplicateWidget(UWidget *pUWidget)
{
	UWidget *pNewWidget = DuplicateObject<UWidget>(pUWidget, this);
	UPanelWidget *pNewUPanelWidget = Cast<UPanelWidget>(pNewWidget);
	if (pNewUPanelWidget)
	{
		const TArray<UPanelSlot*>& slots = pNewUPanelWidget->GetSlots();
		for (int32 iSlotNum = 0; iSlotNum < slots.Num(); ++iSlotNum)
		{
			slots[iSlotNum]->Content = nullptr;
		}
		pNewUPanelWidget->ClearChildren();
		UPanelWidget *pUPanelWidget = Cast<UPanelWidget>(pUWidget);
		for (int ii = 0; ii < pUPanelWidget->GetChildrenCount(); ++ii)
		{
			UWidget *pChildUWidget = pUPanelWidget->GetChildAt(ii);
			UWidget *pNewChildWidget = DeepDuplicateWidget(pChildUWidget);
			UPanelSlot *pUPanelSlot = pNewUPanelWidget->AddChild(pNewChildWidget);
			UHorizontalBoxSlot *pNewUHorizontalBoxSlot = Cast<UHorizontalBoxSlot>(pUPanelSlot);
			if (pNewUHorizontalBoxSlot)
			{
				UHorizontalBoxSlot *pUHorizontalBoxSlot = Cast<UHorizontalBoxSlot>(pChildUWidget->Slot);
				pNewUHorizontalBoxSlot->SetHorizontalAlignment(pUHorizontalBoxSlot->HorizontalAlignment);
				pNewUHorizontalBoxSlot->SetVerticalAlignment(pUHorizontalBoxSlot->VerticalAlignment);
			}
			USizeBoxSlot *pNewUSizeBoxSlot = Cast<USizeBoxSlot>(pUPanelSlot);
			if (pNewUSizeBoxSlot)
			{
				USizeBoxSlot *pUSizeBoxSlot = Cast<USizeBoxSlot>(pChildUWidget->Slot);
				pNewUSizeBoxSlot->SetHorizontalAlignment(pUSizeBoxSlot->HorizontalAlignment);
				pNewUSizeBoxSlot->SetVerticalAlignment(pUSizeBoxSlot->VerticalAlignment);
			}
		}
	}

	return pNewWidget;
}
#endif

void UGasaUserWidget::OnLooseParentCompiled(UBlueprint* BP)
{
	GenerateParentHierarchyFromLooseParent();
}

// This was just an experiment to see how possible it would be to generate a WidgetTree from a parent reference without using the usual blueprint inheritance.
void UGasaUserWidget::GenerateParentHierarchyFromLooseParent()
{
#if WITH_EDITOR
	UWidgetBlueprintGeneratedClass* WBG_ParentClass = Cast<UWidgetBlueprintGeneratedClass>(LooseParent);
	UWidgetBlueprintGeneratedClass* WBG_Class      = Cast<UWidgetBlueprintGeneratedClass>(GetClass());
	if (WBG_ParentClass == nullptr)
		return;
	if (WBG_Class == nullptr)
		return;

	UPackage*         Package = WBG_Class->GetPackage();
	UWidgetBlueprint* BP      = Cast<UWidgetBlueprint>(Package->FindAssetInPackage());
	UWidgetTree*      WT      = BP->WidgetTree;

	UPackage*         UserParentPackage = WBG_ParentClass->GetPackage();
	UWidgetBlueprint* UserParentBP      = Cast<UWidgetBlueprint>(UserParentPackage->FindAssetInPackage());
	UWidgetTree*      UserParentWT      = UserParentBP->WidgetTree;	

	TArray<UWidget*> UserParentWidgets;
	UserParentWT->GetAllWidgets(UserParentWidgets);
	for (UWidget* UserParentWidget : UserParentWidgets)
	{
		UWidget* OldWidget = nullptr;
		UWidget* Widget    = WT->FindWidget(UserParentWidget->GetFName());
		TArray<UWidget*> Children;
		UPanelWidget*    Parent = nullptr;
		
		if (Widget == nullptr)
		{
			if (UserParentWidget->GetClass()->IsChildOf(UUserWidget::StaticClass()))
				Widget = CreateWidget<UUserWidget>(WT, UserParentWidget->GetClass(), UserParentWidget->GetFName());
			else
				Widget = NewObject<UWidget>(WT, UserParentWidget->GetClass(), UserParentWidget->GetFName(), RF_Transactional, UserParentWidget);
			
			if (WT->RootWidget == nullptr)
			{
				WT->RootWidget = Widget;
			}
			else
			{
				Parent = WT->FindWidget<UPanelWidget>(UserParentWidget->GetParent()->GetFName());
			}
		}
		else
		{
			// The widget existed previously (most likely already ran this before or manually created)
			// Try to preserve widget heiarchy attached to this if possible
			Parent = Widget->GetParent();
			
			UPanelWidget* Panel = Cast<UPanelWidget>(Widget);
			if (Panel)
			{
				Children = Panel->GetAllChildren();
			}

			OldWidget = Widget;
			Widget = DuplicateObject<UWidget>(UserParentWidget, WT, UserParentWidget->GetFName());
		}

		UPanelWidget* NewPanel = Cast<UPanelWidget>(Widget);
		if (NewPanel)
		{
			const TArray<UPanelSlot*>& Slots = NewPanel->GetSlots();
			for (int32 Id = 0; Id < Slots.Num(); ++Id)
			{
				Slots[Id]->Content = nullptr;
			}
			NewPanel->ClearChildren();
		}

		if (Parent)
		{
			UPanelSlot* PSlot = Parent->AddChild(Widget);
			UScaleBoxSlot*      SlotScale   = Cast<UScaleBoxSlot>(PSlot);
			UScrollBoxSlot*     SlotScroll  = Cast<UScrollBoxSlot>(PSlot);
			UOverlaySlot*       SlotOverlay = Cast<UOverlaySlot>(PSlot);
			UHorizontalBoxSlot* SlotHB      = Cast<UHorizontalBoxSlot>(PSlot);
			USizeBoxSlot*       SlotSB      = Cast<USizeBoxSlot>(PSlot);
			UVerticalBoxSlot*   SlobVB      = Cast<UVerticalBoxSlot>(PSlot);

			if (SlotOverlay)
			{
				UOverlay* UPW_ParentOverlay = Cast<UOverlay>(UserParentWidget->GetParent());
				UOverlaySlot* ParentSlot = Cast<UOverlaySlot>(UPW_ParentOverlay->GetSlots()[Parent->GetSlots().Num() - 1]);
				SlotOverlay->SetPadding( ParentSlot->GetPadding());
				SlotOverlay->SetHorizontalAlignment( ParentSlot->GetHorizontalAlignment());
				SlotOverlay->SetVerticalAlignment( ParentSlot->GetVerticalAlignment());
			}
		}

		//This may not need to happen since the children check to see if they need to be added back.
		for (UWidget* Child : Children)
		{
			if (UserParentWT->FindWidget(Child->GetFName()))
				continue;
			UPanelSlot* PSlot = Cast<UPanelWidget>(Widget)->AddChild(Child);
			UScaleBoxSlot*      SlotScale   = Cast<UScaleBoxSlot>(PSlot);
			UScrollBoxSlot*     SlotScroll  = Cast<UScrollBoxSlot>(PSlot);
			UOverlaySlot*       SlotOverlay = Cast<UOverlaySlot>(PSlot);
			UHorizontalBoxSlot* SlotHB      = Cast<UHorizontalBoxSlot>(PSlot);
			USizeBoxSlot*       SlotSB      = Cast<USizeBoxSlot>(PSlot);
			UVerticalBoxSlot*   SlobVB      = Cast<UVerticalBoxSlot>(PSlot);

			// I'm not entirely sure if this is possible this way...
			if (SlotOverlay)
			{
				UOverlay* ParentOverlay = Cast<UOverlay>(OldWidget->GetParent());
				UOverlaySlot* ParentSlot = Cast<UOverlaySlot>(ParentOverlay->GetSlots()[Parent->GetSlots().Num() - 1]);
				SlotOverlay->SetPadding( ParentSlot->GetPadding());
				SlotOverlay->SetHorizontalAlignment( ParentSlot->GetHorizontalAlignment());
				SlotOverlay->SetVerticalAlignment( ParentSlot->GetVerticalAlignment());
			}
		}

		if (OldWidget)
			OldWidget->RemoveFromParent();
	}

	BP->Modify();
	FBlueprintEditorUtils::MarkBlueprintAsStructurallyModified(BP);
#endif
}

UGasaUserWidget::UGasaUserWidget(FObjectInitializer const& ObjectInitializer)
	: UUserWidget(ObjectInitializer)
{	
}

bool UGasaUserWidget::Initialize()
{
	// If it's not initialized initialize it, as long as it's not the CDO, we never initialize the CDO.
	if (!bInitialized && !HasAnyFlags(RF_ClassDefaultObject))
	{
		// If this is a sub-widget of another UserWidget, default designer flags and player context to match those of the owning widget
		if (UUserWidget* OwningUserWidget = GetTypedOuter<UUserWidget>())
		{
#if WITH_EDITOR
			SetDesignerFlags(OwningUserWidget->GetDesignerFlags());
#endif
			SetPlayerContext(OwningUserWidget->GetPlayerContext());
		}

		UWidgetBlueprintGeneratedClass* BGClass = Cast<UWidgetBlueprintGeneratedClass>(GetClass());
		// Only do this if this widget is of a blueprint class
		if (BGClass)
		{
			BGClass->InitializeWidget(this);
		}
		else
		{
			InitializeNativeClassData();
		}

		if ( WidgetTree == nullptr )
		{
			WidgetTree = NewObject<UWidgetTree>(this, TEXT("WidgetTree"), RF_Transient);
		}
		else
		{
			WidgetTree->SetFlags(RF_Transient);

			InitializeNamedSlots();
		}

		// For backward compatibility, run the initialize event on widget that doesn't have a player context only when the class authorized it.
		bool bClassWantsToRunInitialized = BGClass && BGClass->bCanCallInitializedWithoutPlayerContext;
		if (!IsDesignTime() && (PlayerContext.IsValid() || bClassWantsToRunInitialized))
		{
			NativeOnInitialized();
		}

#if WITH_EDITOR
		if (LooseParent && bUpdateOnParentCompile)
		{
			UWidgetBlueprintGeneratedClass* WBG_ParentClass = Cast<UWidgetBlueprintGeneratedClass>(LooseParent);
			UPackage*         UserParentPackage = WBG_ParentClass->GetPackage();
			UWidgetBlueprint* UserParentBP      = Cast<UWidgetBlueprint>(UserParentPackage->FindAssetInPackage());
			UWidgetTree*      UserParentWT      = UserParentBP->WidgetTree;

			if ( ! UserParentBP->OnCompiled().IsBoundToObject(this))
			{
				UserParentBP->OnCompiled().AddUObject(this, & ThisClass::OnLooseParentCompiled);
			}
		}
#endif

		bInitialized = true;
		return true;
	}

	return false;
}

void UGasaUserWidget::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	FName PropertyName = (PropertyChangedEvent.Property != NULL) ? PropertyChangedEvent.Property->GetFName() : NAME_None;
	if (PropertyName == GET_MEMBER_NAME_CHECKED(UGasaUserWidget, LooseParent)
	|| PropertyName == GET_MEMBER_NAME_CHECKED(UGasaUserWidget, bUpdateOnParentCompile) )
	{
#if WITH_EDITOR
		if (LooseParent && bUpdateOnParentCompile)
		{
			UWidgetBlueprintGeneratedClass* WBG_ParentClass = Cast<UWidgetBlueprintGeneratedClass>(LooseParent);
			if (WBG_ParentClass == nullptr)
				return;
			UPackage*         UserParentPackage = WBG_ParentClass->GetPackage();
			UWidgetBlueprint* UserParentBP      = Cast<UWidgetBlueprint>(UserParentPackage->FindAssetInPackage());
			UWidgetTree*      UserParentWT      = UserParentBP->WidgetTree;

			if ( ! UserParentBP->OnCompiled().IsBoundToObject(this))
			{
				UserParentBP->OnCompiled().AddUObject(this, & ThisClass::OnLooseParentCompiled);
			}
		}
#endif	
	}
}

void UGasaUserWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

}

void UGasaUserWidget::NativePreConstruct()
{
	Super::NativePreConstruct();

#if 0
	if (LooseParent)
	{
		UWidgetBlueprintGeneratedClass* WBG_ParentClass = Cast<UWidgetBlueprintGeneratedClass>(LooseParent);
		UPackage*         UserParentPackage = WBG_ParentClass->GetPackage();
		UWidgetBlueprint* UserParentBP      = Cast<UWidgetBlueprint>(UserParentPackage->FindAssetInPackage());
		UWidgetTree*      UserParentWT      = UserParentBP->WidgetTree;

		UserParentBP->OnCompiled().AddLambda( [this](UBlueprint* BP) {
			if (this)
			{
				this->GenerateParentHierarchyFromLooseParent();
			}
		});
	}
#endif
}
