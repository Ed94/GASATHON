// Used in the GasaGen.cpp translation unit
#include "ChangeBPActionMenu.h"
#include "GasaGen_Common.h"

constexpr StrC SBlueprintActionMenu_Construct_Replacement = txt(R"(
void SBlueprintActionMenu::Construct( const FArguments& InArgs, TSharedPtr<FBlueprintEditor> InEditor )
{
	bActionExecuted = false;

	this->GraphObj = InArgs._GraphObj;
	this->DraggedFromPins = InArgs._DraggedFromPins;
	this->NewNodePosition = InArgs._NewNodePosition;
	this->OnClosedCallback = InArgs._OnClosedCallback;
	this->bAutoExpandActionMenu = InArgs._AutoExpandActionMenu;
	this->EditorPtr = InEditor;
	this->OnCloseReasonCallback = InArgs._OnCloseReason;

	// Generate the context display; showing the user what they're picking something for
	//@TODO: Should probably be somewhere more schema-sensitive than the graph panel!
	FSlateColor TypeColor;
	FString TypeOfDisplay;
	const FSlateBrush* ContextIcon = nullptr;

	if (DraggedFromPins.Num() == 1)
	{
		UEdGraphPin* OnePin = DraggedFromPins[0];

		const UEdGraphSchema* Schema = OnePin->GetSchema();
		const UEdGraphSchema_K2* K2Schema = GetDefault<UEdGraphSchema_K2>();

		if (!Schema->IsA(UEdGraphSchema_K2::StaticClass()) || !K2Schema->IsExecPin(*OnePin))
		{
			// Get the type color and icon
			TypeColor = Schema->GetPinTypeColor(OnePin->PinType);
			ContextIcon = FAppStyle::GetBrush( OnePin->PinType.IsArray() ? TEXT("Graph.ArrayPin.Connected") : TEXT("Graph.Pin.Connected") );
		}
	}

	FBlueprintActionContext MenuContext;
	ConstructActionContext(MenuContext);

	TSharedPtr<SWidget> AddImportTargetContent = SNullWidget::NullWidget;
	if (GetDefault<UBlueprintEditorSettings>()->bEnableNamespaceImportingFeatures)
	{
		SAssignNew(AddImportTargetContent, SBox)
			.ToolTipText(LOCTEXT("ImportActionLabelTooltip", "Choose a namespace to import and load additional actions."))
		[
			SNew(SHorizontalBox)
			+SHorizontalBox::Slot()
				.AutoWidth()
				.VAlign(VAlign_Center)
			[
				SNew(STextBlock)
				.Text(LOCTEXT("ImportActionButtonLabel", "Import Actions From:"))
			]
			+SHorizontalBox::Slot()
				.AutoWidth()
				.Padding(4.f, 0.f)
			[
				SNew(SBlueprintNamespaceEntry)
					.AllowTextEntry(false)
					.OnNamespaceSelected(this, &SBlueprintActionMenu::OnNamespaceSelectedForImport)
					.OnGetNamespacesToExclude(this, &SBlueprintActionMenu::OnGetNamespacesToExcludeFromImportMenu)
					.ExcludedNamespaceTooltipText(LOCTEXT("CannotSelectNamespaceForImport", "This namespace has already been imported by this Blueprint."))
			]
		];
	}

	TSharedPtr<SComboButton> TargetContextSubMenuButton;
	// @TODO: would be nice if we could use a checkbox style for this, and have a different state for open/closed
	SAssignNew(TargetContextSubMenuButton, SComboButton)
		.MenuPlacement(MenuPlacement_MenuRight)
		.HasDownArrow(false)
		.ButtonStyle(FAppStyle::Get(), "BlueprintEditor.ContextMenu.TargetsButton")
		.ContentPadding(FMargin(5))
		.MenuContent()
		[
			SAssignNew(ContextTargetSubMenu, SBlueprintContextTargetMenu, MenuContext)
				.OnTargetMaskChanged(this, &SBlueprintActionMenu::OnContextTargetsChanged)
				.CustomTargetContent()
				[
					AddImportTargetContent.ToSharedRef()
				]
		];

	// Build the widget layout
	TSharedRef<SBox> ContentBox = SNew(SBox);
	{
		TSharedRef<SVerticalBox> VBox = SNew(SVerticalBox);
		{
			SVerticalBox::FSlot::FSlotArguments
			SearchIndicator = SVerticalBox::Slot();
			{
				TSharedRef<SHorizontalBox> HBox = SNew(SHorizontalBox);
				{
					SHorizontalBox::FSlot::FSlotArguments 
					TypePill = SHorizontalBox::Slot();
					{
						TSharedRef<SImage> PillImage = SNew(SImage);
						{
							SImage::FArguments Args;
							Args.Visibility(this, & SBlueprintActionMenu::GetTypeImageVisibility);
							PillImage->SetColorAndOpacity(TypeColor);
							PillImage->SetImage(ContextIcon);
							PillImage->Construct(Args);
						}
						SHorizontalBox::FSlot* Slot; TypePill.Expose(Slot);
						TypePill.AutoWidth();
						TypePill.VAlign(VAlign_Center);
						TypePill.Padding( FMargin(0.f, 0.f, (ContextIcon != nullptr) ? 5.f : 0.f, 0.f));
						TypePill.AttachWidget(PillImage);
					}

					SHorizontalBox::FSlot::FSlotArguments
					SearchContextDescription = SHorizontalBox::Slot();	
					{
						TSharedRef<STextBlock> TextBlock = SNew(STextBlock);
						{
							STextBlock::FArguments Args;
							Args.Text(this, & SBlueprintActionMenu::GetSearchContextDesc);
							Args.Font(FAppStyle::GetFontStyle(FName("BlueprintEditor.ActionMenu.ContextDescriptionFont")));
							Args.ToolTip(IDocumentation::Get()->CreateToolTip(
								LOCTEXT("BlueprintActionMenuContextTextTooltip", "Describes the current context of the action list"),
								NULL,
								TEXT("Shared/Editors/BlueprintEditor"),
								TEXT("BlueprintActionMenuContextText")));
							Args.AutoWrapText(true);
							TextBlock->Construct(Args);
						}
						SearchContextDescription.FillWidth(1.f);
						SearchContextDescription.VAlign(VAlign_Center);
						SearchContextDescription.AttachWidget(TextBlock);
					}

					SHorizontalBox::FSlot::FSlotArguments
					ContextToggle = SHorizontalBox::Slot();
					{
						TSharedRef<SCheckBox> CheckBox = SNew(SCheckBox);
						{
							SCheckBox::FArguments Args;
							Args.OnCheckStateChanged(this, & SBlueprintActionMenu::OnContextToggleChanged);
							Args.IsChecked(this, & SBlueprintActionMenu::ContextToggleIsChecked);
							Args.ToolTip(IDocumentation::Get()->CreateToolTip(
								LOCTEXT("BlueprintActionMenuContextToggleTooltip"
									, "Should the list be filtered to only actions that make sense in the current context?"),
								NULL,
								TEXT("Shared/Editors/BlueprintEditor"),
								TEXT("BlueprintActionMenuContextToggle")));
							Args.Content().SlotContent.Widget = SNew(STextBlock)
								.Text(LOCTEXT("BlueprintActionMenuContextToggle", "Context Sensitive"));
							CheckBox->Construct(Args);
						}
						ContextToggle.HAlign(HAlign_Right);
						ContextToggle.VAlign(VAlign_Center);
						ContextToggle.AutoWidth();
						ContextToggle.AttachWidget( CheckBox );
					}

					SHorizontalBox::FSlot::FSlotArguments
					ContextButton = SHorizontalBox::Slot();
					{
						ContextButton.HAlign(HAlign_Right);
						ContextButton.VAlign(VAlign_Center);
						ContextButton.AutoWidth();
						ContextButton.Padding( FMargin( 3.f, 0.f, 0.f, 0.f ));
						ContextButton.AttachWidget( TargetContextSubMenuButton.ToSharedRef() );
					}

					SHorizontalBox::FArguments Args = SHorizontalBox::FArguments();
					Args.operator+( TypePill );
					Args.operator+( SearchContextDescription );
					Args.operator+( ContextToggle );
					Args.operator+( ContextButton );
					HBox->Construct(Args);
				}

				SearchIndicator.AutoHeight();
				SearchIndicator.Padding( FMargin(2, 2, 2, 5));
				SearchIndicator.AttachWidget(HBox);
			}

			SVerticalBox::FSlot::FSlotArguments
			ActionList = SVerticalBox::Slot();
			{
				SAssignNew( GraphActionMenu, SGraphActionMenu);

				SGraphActionMenu::FArguments Args;
				Args.OnActionSelected(this, &SBlueprintActionMenu::OnActionSelected);
				Args.OnCreateWidgetForAction(SGraphActionMenu::FOnCreateWidgetForAction::CreateSP(this, &SBlueprintActionMenu::OnCreateWidgetForAction));
				Args.OnGetActionList(this, &SBlueprintActionMenu::OnGetActionList);
				Args.OnCreateCustomRowExpander_Static(&CreateCustomBlueprintActionExpander);
				Args.DraggedFromPins(DraggedFromPins);
				Args.GraphObj(GraphObj);
				GraphActionMenu->Construct(Args);

				ActionList.AttachWidget( GraphActionMenu.ToSharedRef() );
			}

			SVerticalBox::FSlot::FSlotArguments
			ProgressBar = SVerticalBox::Slot();
			{
				TSharedRef<SBox> Box = SNew(SBox);
				{
					TSharedRef<SProgressBar> Bar = SNew(SProgressBar);
					{
						Bar->SetBorderPadding(FVector2D( 0, 0 ));
						Bar->SetPercent( TAttribute<TOptional<float>>::CreateLambda([this]()
						{
							return ContextMenuBuilder.IsValid() ? ContextMenuBuilder->GetPendingActionsProgress() : 0.0f;
						}));
					}
					Box->SetContent( Bar );
					Box->SetHeightOverride(2);
					Box->SetVisibility(TAttribute<EVisibility>().CreateLambda([this]()
					{
						return ContextMenuBuilder.IsValid() && ContextMenuBuilder->GetNumPendingActions() > 0 ? EVisibility::SelfHitTestInvisible : EVisibility::Collapsed;
					}));
				}
				ProgressBar.AutoHeight();
				ProgressBar.AttachWidget(Box);
			}

			SVerticalBox::FArguments Args;
			Args.operator+( SearchIndicator );
			Args.operator+( ActionList );
			Args.operator+( ProgressBar );
			VBox->Construct( Args );
		}

		ContentBox->SetMaxDesiredWidth(500.f);
		ContentBox->SetMaxDesiredHeight(650.f);
		ContentBox->SetContent( VBox );

		SBorder::FArguments Args;
		Args.BorderImage(FAppStyle::GetBrush("Menu.Background"));
		Args.Padding(5.0f);
		Args.operator[](ContentBox);
		SBorder::Construct(Args);
	}
})");

void change_SBlueprintActionMenu_Construct()
{
#define path_SBlueprintActionMenuCpp \
	R"(C:\projects\Unreal\Surgo\UE\Engine\Source\Editor\Kismet\Private\SBlueprintActionMenu.cpp)"

	FileContents content = file_read_contents( GlobalAllocator, true, path_SBlueprintActionMenuCpp );
	CodeBody parsed_SBlueprintActionMenu = parse_global_body( StrC { content.size, (char const*)content.data });

	CodeFn signature_to_change = parse_function( code(
		void SBlueprintActionMenu::Construct( const FArguments& InArgs, TSharedPtr<FBlueprintEditor> InEditor ) {}
	));

	CodeBody changed_SBlueprintActionMenu = def_body(ECode::Global_Body);
	for ( Code code : parsed_SBlueprintActionMenu )
	{
		switch ( code->Type )
		{
			using namespace ECode;
			case Function:
				CodeFn function_def = code.cast<CodeFn>();

				if ( String::are_equal(function_def->Name, signature_to_change->Name)
				&&  function_def->Params.is_equal(signature_to_change->Params))
				{
					code = parse_function( SBlueprintActionMenu_Construct_Replacement );
					log_fmt("Swapped: %S", function_def->Name);
				}
			break;
		}
		changed_SBlueprintActionMenu.append(code);
	}
	log_fmt("\n");

	Builder SBlueprintActionMenu_Changed = Builder::open(path_SBlueprintActionMenuCpp);
	SBlueprintActionMenu_Changed.print( def_comment(txt("This file was regenerated by GasaGen/ChangeBPActionMenu.cpp")));
	SBlueprintActionMenu_Changed.print(changed_SBlueprintActionMenu);
	SBlueprintActionMenu_Changed.write();
	format_file(path_SBlueprintActionMenuCpp, false);
}
