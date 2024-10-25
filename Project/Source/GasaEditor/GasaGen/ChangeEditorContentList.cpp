#include "ChangeEditorContentList.h"

#include "GasaGen_Common.h"
#include "GasaEditorCommon.h"

constexpr StrC SAssetView_Construct_Replacement = txt(R"(
void SAssetView::Construct( const FArguments& InArgs )
{
	ViewCorrelationGuid = FGuid::NewGuid();	

	InitialNumAmortizedTasks = 0;
	TotalAmortizeTime = 0;
	AmortizeStartTime = 0;
	MaxSecondsPerFrame = 0.015f;

	bFillEmptySpaceInTileView = InArgs._FillEmptySpaceInTileView;
	FillScale = 1.0f;

	bShowRedirectors = InArgs._ShowRedirectors;
	bLastShowRedirectors = bShowRedirectors.Get(false);

	ThumbnailHintFadeInSequence.JumpToStart();
	ThumbnailHintFadeInSequence.AddCurve(0, 0.5f, ECurveEaseFunction::Linear);

	UContentBrowserDataSubsystem* ContentBrowserData = IContentBrowserDataModule::Get().GetSubsystem();
	ContentBrowserData->OnItemDataUpdated().AddSP(this, &SAssetView::HandleItemDataUpdated);
	ContentBrowserData->OnItemDataRefreshed().AddSP(this, &SAssetView::RequestSlowFullListRefresh);
	ContentBrowserData->OnItemDataDiscoveryComplete().AddSP(this, &SAssetView::HandleItemDataDiscoveryComplete);
	FilterCacheID.Initialaze(ContentBrowserData);

	FCollectionManagerModule& CollectionManagerModule = FCollectionManagerModule::GetModule();
	CollectionManagerModule.Get().OnAssetsAddedToCollection().AddSP( this, &SAssetView::OnAssetsAddedToCollection );
	CollectionManagerModule.Get().OnAssetsRemovedFromCollection().AddSP( this, &SAssetView::OnAssetsRemovedFromCollection );
	CollectionManagerModule.Get().OnCollectionRenamed().AddSP( this, &SAssetView::OnCollectionRenamed );
	CollectionManagerModule.Get().OnCollectionUpdated().AddSP( this, &SAssetView::OnCollectionUpdated );

	// Listen for when view settings are changed
	UContentBrowserSettings::OnSettingChanged().AddSP(this, &SAssetView::HandleSettingChanged);

	ThumbnailSize = InArgs._InitialThumbnailSize;

	// Get desktop metrics
	FDisplayMetrics DisplayMetrics;
	FSlateApplication::Get().GetCachedDisplayMetrics( DisplayMetrics );

	const FIntPoint DisplaySize(
		DisplayMetrics.PrimaryDisplayWorkAreaRect.Right - DisplayMetrics.PrimaryDisplayWorkAreaRect.Left,
		DisplayMetrics.PrimaryDisplayWorkAreaRect.Bottom - DisplayMetrics.PrimaryDisplayWorkAreaRect.Top );

	ThumbnailScaleRangeScalar = (float)DisplaySize.Y / 2160.f;

	// Use the shared ThumbnailPool for the rendering of thumbnails
	AssetThumbnailPool = UThumbnailManager::Get().GetSharedThumbnailPool();
	NumOffscreenThumbnails = 128;
	ListViewThumbnailResolution = 128;
	ListViewThumbnailSize = 32;
	ListViewThumbnailPadding = 2;
	TileViewThumbnailResolution = 256;

	// Max Size for the thumbnail
#if UE_CONTENTBROWSER_NEW_STYLE
	constexpr int32 MaxTileViewThumbnailSize = 160;
#else
	constexpr int32 MaxTileViewThumbnailSize = 150;
#endif

	TileViewThumbnailSize = MaxTileViewThumbnailSize;

	TileViewThumbnailPadding = 9;

	TileViewNameHeight = 50;

	UpdateThumbnailSizeValue();
	MinThumbnailScale = 0.1f * ThumbnailScaleRangeScalar;
	MaxThumbnailScale = 1.9f * ThumbnailScaleRangeScalar;

	bCanShowClasses = InArgs._CanShowClasses;

	bCanShowFolders = InArgs._CanShowFolders;
	
	bCanShowReadOnlyFolders = InArgs._CanShowReadOnlyFolders;

	bFilterRecursivelyWithBackendFilter = InArgs._FilterRecursivelyWithBackendFilter;
		
	bCanShowRealTimeThumbnails = InArgs._CanShowRealTimeThumbnails;

	bCanShowDevelopersFolder = InArgs._CanShowDevelopersFolder;

	bCanShowFavorites = InArgs._CanShowFavorites;
	bCanDockCollections = InArgs._CanDockCollections;

	SelectionMode = InArgs._SelectionMode;

	bShowPathInColumnView = InArgs._ShowPathInColumnView;
	bShowTypeInColumnView = InArgs._ShowTypeInColumnView;
	bSortByPathInColumnView = bShowPathInColumnView && InArgs._SortByPathInColumnView;
	bShowTypeInTileView = InArgs._ShowTypeInTileView;
	bForceShowEngineContent = InArgs._ForceShowEngineContent;
	bForceShowPluginContent = InArgs._ForceShowPluginContent;
	bForceHideScrollbar = InArgs._ForceHideScrollbar;
	bShowDisallowedAssetClassAsUnsupportedItems = InArgs._ShowDisallowedAssetClassAsUnsupportedItems;

	bPendingUpdateThumbnails = false;
	bShouldNotifyNextAssetSync = true;
	CurrentThumbnailSize = TileViewThumbnailSize;

	SourcesData = InArgs._InitialSourcesData;
	BackendFilter = InArgs._InitialBackendFilter;

	FrontendFilters = InArgs._FrontendFilters;
	if (FrontendFilters.IsValid())
	{
		FrontendFilters->OnChanged().AddSP(this, &SAssetView::OnFrontendFiltersChanged);
	}
	TextFilter = InArgs._TextFilter;
	if (TextFilter.IsValid())
	{
		TextFilter->OnChanged().AddSP(this, &SAssetView::OnFrontendFiltersChanged);
	}

	OnShouldFilterAsset = InArgs._OnShouldFilterAsset;
	OnShouldFilterItem = InArgs._OnShouldFilterItem;

	OnNewItemRequested = InArgs._OnNewItemRequested;
	OnItemSelectionChanged = InArgs._OnItemSelectionChanged;
	OnItemsActivated = InArgs._OnItemsActivated;
	OnGetItemContextMenu = InArgs._OnGetItemContextMenu;
	OnItemRenameCommitted = InArgs._OnItemRenameCommitted;
	OnAssetTagWantsToBeDisplayed = InArgs._OnAssetTagWantsToBeDisplayed;
	OnIsAssetValidForCustomToolTip = InArgs._OnIsAssetValidForCustomToolTip;
	OnGetCustomAssetToolTip = InArgs._OnGetCustomAssetToolTip;
	OnVisualizeAssetToolTip = InArgs._OnVisualizeAssetToolTip;
	OnAssetToolTipClosing = InArgs._OnAssetToolTipClosing;
	OnGetCustomSourceAssets = InArgs._OnGetCustomSourceAssets;
	HighlightedText = InArgs._HighlightedText;
	ThumbnailLabel = InArgs._ThumbnailLabel;
	AllowThumbnailHintLabel = InArgs._AllowThumbnailHintLabel;
	InitialCategoryFilter = InArgs._InitialCategoryFilter;
	AssetShowWarningText = InArgs._AssetShowWarningText;
	bAllowDragging = InArgs._AllowDragging;
	bAllowFocusOnSync = InArgs._AllowFocusOnSync;
	HiddenColumnNames = DefaultHiddenColumnNames = InArgs._HiddenColumnNames;
	CustomColumns = InArgs._CustomColumns;
	OnSearchOptionsChanged = InArgs._OnSearchOptionsChanged;
	bShowPathViewFilters = InArgs._bShowPathViewFilters;
	OnExtendAssetViewOptionsMenuContext = InArgs._OnExtendAssetViewOptionsMenuContext;
	AssetViewOptionsProfile = InArgs._AssetViewOptionsProfile;
	
	if ( InArgs._InitialViewType >= 0 && InArgs._InitialViewType < EAssetViewType::MAX )
	{
		CurrentViewType = InArgs._InitialViewType;
	}
	else
	{
		CurrentViewType = EAssetViewType::Tile;
	}

	bPendingSortFilteredItems = false;
	bQuickFrontendListRefreshRequested = false;
	bSlowFullListRefreshRequested = false;
	LastSortTime = 0;
	SortDelaySeconds = 8;

	bBulkSelecting = false;
	bAllowThumbnailEditMode = InArgs._AllowThumbnailEditMode;
	bThumbnailEditMode = false;
	bUserSearching = false;
	bPendingFocusOnSync = false;
	bWereItemsRecursivelyFiltered = false;

	OwningContentBrowser = InArgs._OwningContentBrowser;

	FAssetToolsModule& AssetToolsModule = FModuleManager::LoadModuleChecked<FAssetToolsModule>("AssetTools");
	AssetClassPermissionList = AssetToolsModule.Get().GetAssetClassPathPermissionList(EAssetClassAction::ViewAsset);
	FolderPermissionList = AssetToolsModule.Get().GetFolderPermissionList();
	WritableFolderPermissionList = AssetToolsModule.Get().GetWritableFolderPermissionList();

	if(InArgs._AllowCustomView)
	{
		FContentBrowserModule& ContentBrowserModule = FModuleManager::GetModuleChecked<FContentBrowserModule>(TEXT("ContentBrowser"));

		if(ContentBrowserModule.GetContentBrowserViewExtender().IsBound())
		{
			ViewExtender = ContentBrowserModule.GetContentBrowserViewExtender().Execute();

			// Bind the delegates the custom view is responsible for firing
			if(ViewExtender)
			{
				ViewExtender->OnSelectionChanged().BindSP(this, &SAssetView::AssetSelectionChanged);
				ViewExtender->OnContextMenuOpened().BindSP(this, &SAssetView::OnGetContextMenuContent);
				ViewExtender->OnItemScrolledIntoView().BindSP(this, &SAssetView::ItemScrolledIntoView);
				ViewExtender->OnItemDoubleClicked().BindSP(this, &SAssetView::OnListMouseButtonDoubleClick);
			}
		}
	}
	
	FEditorWidgetsModule& EditorWidgetsModule = FModuleManager::LoadModuleChecked<FEditorWidgetsModule>("EditorWidgets");
	TSharedRef<SWidget> AssetDiscoveryIndicator = EditorWidgetsModule.CreateAssetDiscoveryIndicator(EAssetDiscoveryIndicatorScaleMode::Scale_Vertical);

	TSharedRef<SVerticalBox> VerticalBox = SNew(SVerticalBox);

	BindCommands();

	ChildSlot
	.Padding(0.0f)
	[
		SNew(SBorder)
		.Padding(0.f)
		.BorderImage(FAppStyle::Get().GetBrush("Brushes.Panel"))
		[
			VerticalBox
		]
	];

	// Assets area
	VerticalBox->AddSlot()
	.FillHeight(1.f)
	[
		SNew( SVerticalBox ) 

		+ SVerticalBox::Slot()
		.AutoHeight()
		[
			SNew( SBox )
			.Visibility_Lambda([this] { return InitialNumAmortizedTasks > 0 ? EVisibility::SelfHitTestInvisible : EVisibility::Collapsed; })
			.HeightOverride( 2.f )
			[
				SNew( SProgressBar )
				.Percent( this, &SAssetView::GetIsWorkingProgressBarState )
				.BorderPadding( FVector2D(0,0) )
			]
		]
		
		+ SVerticalBox::Slot()
		.FillHeight(1.f)
		[
			SNew(SOverlay)

			+ SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			[
				SAssignNew(ViewContainer, SBox)
				.Padding(6.0f)

			]

			+ SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Center)
			.Padding(FMargin(0, 14, 0, 0))
			[
				// A warning to display when there are no assets to show
				SNew( STextBlock )
				.Justification( ETextJustify::Center )
				.Text( this, &SAssetView::GetAssetShowWarningText )
				.Visibility( this, &SAssetView::IsAssetShowWarningTextVisible )
				.AutoWrapText( true )
			]

			+ SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Bottom)
			.Padding(FMargin(24, 0, 24, 0))
			[
				// Asset discovery indicator
				AssetDiscoveryIndicator
			]

			+ SOverlay::Slot()
			.HAlign(HAlign_Right)
			.VAlign(VAlign_Bottom)
			.Padding(FMargin(8, 0))
			[
				SNew(SBorder)
				.BorderImage(FAppStyle::GetBrush("ErrorReporting.EmptyBox"))
				.BorderBackgroundColor(this, &SAssetView::GetQuickJumpColor)
				.Visibility(this, &SAssetView::IsQuickJumpVisible)
				[
					SNew(STextBlock)
					.Text(this, &SAssetView::GetQuickJumpTerm)
				]
			]
		]
	];

	// Thumbnail edit mode banner
	VerticalBox->AddSlot()
	.AutoHeight()
	.Padding(0.f, 4.f)
	[
		SNew(SBorder)
		.Visibility( this, &SAssetView::GetEditModeLabelVisibility )
		.BorderImage(FAppStyle::Get().GetBrush("Brushes.Panel"))
		.Content()
		[
			SNew(SHorizontalBox)
			+SHorizontalBox::Slot()
			.VAlign(VAlign_Center)
			.Padding(4.f, 0.f, 0.f, 0.f)
			.FillWidth(1.f)
			[
				SNew(STextBlock)
				.Text(LOCTEXT("ThumbnailEditModeLabel", "Editing Thumbnails. Drag a thumbnail to rotate it if there is a 3D environment."))
				.ColorAndOpacity(FAppStyle::Get().GetSlateColor("Colors.Primary"))
			]

			+SHorizontalBox::Slot()
			.AutoWidth()
			.VAlign(VAlign_Center)
			[
				SNew(SPrimaryButton)
				.Text(LOCTEXT("EndThumbnailEditModeButton", "Done Editing"))
				.OnClicked(this, &SAssetView::EndThumbnailEditModeClicked)
			]
		]
	];

	if (InArgs._ShowBottomToolbar)
	{
		// Bottom panel
		VerticalBox->AddSlot()
		.AutoHeight()
		[
			SNew(SHorizontalBox)

			// Asset count
			+SHorizontalBox::Slot()
			.FillWidth(1.f)
			.VAlign(VAlign_Center)
			.Padding(8, 5)
			[
				SNew(STextBlock)
				.Text(this, &SAssetView::GetAssetCountText)
			]

			// View mode combo button
			+SHorizontalBox::Slot()
			.AutoWidth()
			[
				SNew(SComboButton)
				.Visibility(InArgs._ShowViewOptions ? EVisibility::Visible : EVisibility::Collapsed)
				.ContentPadding(0.f)
				.ButtonStyle( FAppStyle::Get(), "ToggleButton" ) // Use the tool bar item style for this button
				.OnGetMenuContent( this, &SAssetView::GetViewButtonContent )
				.ButtonContent()
				[
					SNew(SHorizontalBox)
 
					+SHorizontalBox::Slot()
					.AutoWidth()
					.VAlign(VAlign_Center)
					[
						SNew(SImage)
						.Image( FAppStyle::GetBrush("GenericViewButton") )
					]
 
					+SHorizontalBox::Slot()
					.AutoWidth()
					.Padding(2.f, 0.f, 0.f, 0.f)
					.VAlign(VAlign_Center)
					[
						SNew(STextBlock)
						.Text( LOCTEXT("ViewButton", "View Options") )
					]
				]
			]
		];
	}

	CreateCurrentView();

	if( InArgs._InitialAssetSelection.IsValid() )
	{
		// sync to the initial item without notifying of selection
		bShouldNotifyNextAssetSync = false;
		SyncToLegacy( MakeArrayView(&InArgs._InitialAssetSelection, 1), TArrayView<const FString>() );
	}

	// If currently looking at column, and you could choose to sort by path in column first and then name
	// Generalizing this is a bit difficult because the column ID is not accessible or is not known
	// Currently I assume this won't work, if this view mode is not column. Otherwise, I don't think sorting by path
	// is a good idea. 
	if (CurrentViewType == EAssetViewType::Column && bSortByPathInColumnView)
	{
		SortManager.SetSortColumnId(EColumnSortPriority::Primary, SortManager.PathColumnId);
		SortManager.SetSortColumnId(EColumnSortPriority::Secondary, SortManager.NameColumnId);
		SortManager.SetSortMode(EColumnSortPriority::Primary, EColumnSortMode::Ascending);
		SortManager.SetSortMode(EColumnSortPriority::Secondary, EColumnSortMode::Ascending);
		SortList();
	}
})");

constexpr StrC SAssetView_GetThumbnailScale_Replacement = txt(R"(
float SAssetView::GetThumbnailScale() const
{
	float BaseScale;
	switch (ThumbnailSize)
	{
	case EThumbnailSize::Tiny:
		BaseScale = 0.1f;
		break;
	case EThumbnailSize::Small:
		BaseScale = 0.25f;
		break;
	case EThumbnailSize::Medium:
		BaseScale = 0.40f;
		break;
	case EThumbnailSize::Large:
		BaseScale = 0.60f;
		break;
	case EThumbnailSize::XLarge:
		BaseScale = 0.8f;
		break;
	case EThumbnailSize::Huge:
		BaseScale = 1.0f;
		break;
	default:
		BaseScale = 0.5f;
		break;
	}

	return BaseScale * GetTickSpaceGeometry().Scale;
})");

constexpr StrC SPropertyMenuAssetPicker_Construct_Replacement = txt(R"(
void SPropertyMenuAssetPicker::Construct( const FArguments& InArgs )
{
	CurrentObject = InArgs._InitialObject;
	PropertyHandle = InArgs._PropertyHandle;
	const TArray<FAssetData>& OwnerAssetArray = InArgs._OwnerAssetArray;
	bAllowClear = InArgs._AllowClear;
	bAllowCopyPaste = InArgs._AllowCopyPaste;
	AllowedClasses = InArgs._AllowedClasses;
	DisallowedClasses = InArgs._DisallowedClasses;
	NewAssetFactories = InArgs._NewAssetFactories;
	OnShouldFilterAsset = InArgs._OnShouldFilterAsset;
	OnSet = InArgs._OnSet;
	OnClose = InArgs._OnClose;

	const bool bForceShowEngineContent = PropertyHandle ? PropertyHandle->HasMetaData(TEXT("ForceShowEngineContent")) : false;
	const bool bForceShowPluginContent = PropertyHandle ? PropertyHandle->HasMetaData(TEXT("ForceShowPluginContent")) : false;

	const bool bInShouldCloseWindowAfterMenuSelection = true;
	const bool bCloseSelfOnly = true;
	const bool bSearchable = false;
	
	FMenuBuilder MenuBuilder(bInShouldCloseWindowAfterMenuSelection, nullptr, nullptr, bCloseSelfOnly, &FCoreStyle::Get(), bSearchable);

	if (NewAssetFactories.Num() > 0)
	{
		MenuBuilder.BeginSection(NAME_None, LOCTEXT("CreateNewAsset", "Create New Asset"));
		{
			for (UFactory* Factory : NewAssetFactories)
			{
				TWeakObjectPtr<UFactory> FactoryPtr(Factory);

				MenuBuilder.AddMenuEntry(
					Factory->GetDisplayName(),
					Factory->GetToolTip(),
					FSlateIconFinder::FindIconForClass(Factory->GetSupportedClass()),
					FUIAction(FExecuteAction::CreateSP(this, &SPropertyMenuAssetPicker::OnCreateNewAssetSelected, FactoryPtr))
					);
			}
		}
		MenuBuilder.EndSection();
	}

	if (CurrentObject.IsValid() || bAllowCopyPaste || bAllowClear)
	{
		MenuBuilder.BeginSection(NAME_None, LOCTEXT("CurrentAssetOperationsHeader", "Current Asset"));
		{
			if (CurrentObject.IsValid())
			{
				MenuBuilder.AddMenuEntry(
					LOCTEXT("EditAsset", "Edit"),
					LOCTEXT("EditAsset_Tooltip", "Edit this asset"),
					FSlateIcon(FAppStyle::GetAppStyleSetName(),"Icons.Edit"),
					FUIAction(FExecuteAction::CreateSP(this, &SPropertyMenuAssetPicker::OnEdit)));
			}

			if (bAllowCopyPaste)
			{
				MenuBuilder.AddMenuEntry(
					LOCTEXT("CopyAsset", "Copy"),
					LOCTEXT("CopyAsset_Tooltip", "Copies the asset to the clipboard"),
					FSlateIcon(FAppStyle::GetAppStyleSetName(),"GenericCommands.Copy"),
					FUIAction(FExecuteAction::CreateSP(this, &SPropertyMenuAssetPicker::OnCopy))
				);

				MenuBuilder.AddMenuEntry(
					LOCTEXT("PasteAsset", "Paste"),
					LOCTEXT("PasteAsset_Tooltip", "Pastes an asset from the clipboard to this field"),
					FSlateIcon(FAppStyle::GetAppStyleSetName(),"GenericCommands.Paste"),
					FUIAction(
						FExecuteAction::CreateSP(this, &SPropertyMenuAssetPicker::OnPaste),
						FCanExecuteAction::CreateSP(this, &SPropertyMenuAssetPicker::CanPaste))
				);
			}

			if (bAllowClear)
			{
				MenuBuilder.AddMenuEntry(
					LOCTEXT("ClearAsset", "Clear"),
					LOCTEXT("ClearAsset_ToolTip", "Clears the asset set on this field"),
					FSlateIcon(FAppStyle::GetAppStyleSetName(),"GenericCommands.Delete"),
					FUIAction(FExecuteAction::CreateSP(this, &SPropertyMenuAssetPicker::OnClear))
				);
			}
		}
		MenuBuilder.EndSection();
	}

	MenuBuilder.BeginSection(NAME_None, LOCTEXT("BrowseHeader", "Browse"));
	{
		FContentBrowserModule& ContentBrowserModule = FModuleManager::Get().LoadModuleChecked<FContentBrowserModule>(TEXT("ContentBrowser"));

		FAssetPickerConfig AssetPickerConfig;
		// Add filter classes - if we have a single filter class of "Object" then don't set a filter since it would always match everything (but slower!)
		if (AllowedClasses.Num() == 1 && AllowedClasses[0] == UObject::StaticClass())
		{
			AssetPickerConfig.Filter.ClassPaths.Reset();
		}
		else
		{
			for(int32 i = 0; i < AllowedClasses.Num(); ++i)
			{
				AssetPickerConfig.Filter.ClassPaths.Add( AllowedClasses[i]->GetClassPathName() );
			}
		}

		for (int32 i = 0; i < DisallowedClasses.Num(); ++i)
		{
			AssetPickerConfig.Filter.RecursiveClassPathsExclusionSet.Add(DisallowedClasses[i]->GetClassPathName());
		}

		// Allow child classes
		AssetPickerConfig.Filter.bRecursiveClasses = true;
		// Set a delegate for setting the asset from the picker
		AssetPickerConfig.OnAssetSelected = FOnAssetSelected::CreateSP(this, &SPropertyMenuAssetPicker::OnAssetSelected);
		// Set a delegate for setting the asset from the picker via the keyboard
		AssetPickerConfig.OnAssetEnterPressed = FOnAssetEnterPressed::CreateSP(this, &SPropertyMenuAssetPicker::OnAssetEnterPressed);
		// Use the list view by default
		AssetPickerConfig.InitialAssetViewType = EAssetViewType::List;
		// The initial selection should be the current value
		AssetPickerConfig.InitialAssetSelection = CurrentObject;
		// We'll do clearing ourselves
		AssetPickerConfig.bAllowNullSelection = false;
		// Focus search box
		AssetPickerConfig.bFocusSearchBoxWhenOpened = true;
		// Apply custom filter
		AssetPickerConfig.OnShouldFilterAsset = OnShouldFilterAsset;
		// Don't allow dragging
		AssetPickerConfig.bAllowDragging = false;

		// Note(Ed): Personal changes
		AssetPickerConfig.ThumbnailScale = 0.25;
		AssetPickerConfig.InitialThumbnailSize = EThumbnailSize::Small;

		// Save the settings into a special section for asset pickers for properties
		AssetPickerConfig.SaveSettingsName = TEXT("AssetPropertyPicker");
		// Populate the referencing assets via property handle
		AssetPickerConfig.PropertyHandle = PropertyHandle;
		// Populate the additional referencing assets with the Owner asset data
		AssetPickerConfig.AdditionalReferencingAssets = OwnerAssetArray;
		// Force show engine content if meta data says so
		AssetPickerConfig.bForceShowEngineContent = bForceShowEngineContent;
		// Force show plugin content if meta data says so
		AssetPickerConfig.bForceShowPluginContent = bForceShowPluginContent;

		AssetPickerWidget = ContentBrowserModule.Get().CreateAssetPicker(AssetPickerConfig);

		TSharedRef<SWidget> MenuContent =
			SNew(SBox)
			.WidthOverride(static_cast<float>(PropertyEditorAssetConstants::ContentBrowserWindowSize.X))
			.HeightOverride(static_cast<float>(PropertyEditorAssetConstants::ContentBrowserWindowSize.Y))
			[
				AssetPickerWidget.ToSharedRef()
			];

		MenuBuilder.AddWidget(MenuContent, FText::GetEmpty(), true);
	}
	MenuBuilder.EndSection();

	ChildSlot
	[
		MenuBuilder.MakeWidget()
	];
})");

void change_EditorContentList()
{
	// Change property editor constant
	{
	#define path_PropertyEditorAssetConstantsHeader \
		R"(C:\Projects\Unreal\Surgo\UE\Engine\Source\Editor\PropertyEditor\Private\UserInterface\PropertyEditor\PropertyEditorAssetConstants.h)"
		
		FileContents content = file_read_contents( GlobalAllocator, true, path_PropertyEditorAssetConstantsHeader );
		CodeBody parsed_PropertyEditorAssetConstantsHeader = parse_global_body( StrC { content.size, (char const*)content.data });

		CodeBody changed_PropertyEditorAssetConstantsHeader = def_body(ECode::Global_Body);
		for ( Code code : parsed_PropertyEditorAssetConstantsHeader )
		{
			switch ( code->Type )
			{
				using namespace ECode;
				case Namespace:
					CodeNS ns = code.cast<CodeNS>();
					for ( Code ns_code : ns->Body )
					{
						switch ( ns_code->Type )
						{
							case Variable:
								CodeVar var = ns_code.cast<CodeVar>();
								if ( var->Name.starts_with(txt("ContentBrowserWindowSize")) )
								{
									// Swap value with new value
									var->Value->Content = get_cached_string(txt("300.0f, 600.0f"));
									Gasa::LogEditor("Swapped: " + to_fstring(var->Name));
								}
								
							break;
						}
					}
				break;
			}
			changed_PropertyEditorAssetConstantsHeader.append( code );
		}

		Builder SBlueprintActionMenu_Changed = Builder::open(path_PropertyEditorAssetConstantsHeader);
		SBlueprintActionMenu_Changed.print( def_comment(txt("This file was regenerated by GasaGen/ChangeEditorContentList.cpp")));
		SBlueprintActionMenu_Changed.print(changed_PropertyEditorAssetConstantsHeader);
		SBlueprintActionMenu_Changed.write();
		format_file(path_PropertyEditorAssetConstantsHeader, false );
	}

	// Change SAssetView's Construct & GetThumbnailScale
	{
	#define path_SAssetView \
	R"(C:\projects\Unreal\Surgo\UE\Engine\Source\Editor\ContentBrowser\Private\SAssetView.cpp)"

		FileContents content = file_read_contents( GlobalAllocator, true, path_SAssetView );
		CodeBody parsed_SAssetViewCpp = parse_global_body( StrC { content.size, (char const*)content.data });

		CodeFn signature_Construct = parse_function( code(
			void SAssetView::Construct( const FArguments& InArgs ) {}
		));
		CodeFn signature_GetThumbnailScale = parse_function( code(
			float SAssetView::GetThumbnailScale() const {}
		));

		CodeBody changed_SAssetViewCpp = def_body(ECode::Global_Body);
		for ( Code code : parsed_SAssetViewCpp )
		{
			switch ( code->Type )
			{
				using namespace ECode;
				case Function:
				{
					CodeFn function_def = code.cast<CodeFn>();

					if ( String::are_equal(function_def->Name, signature_Construct->Name)
					&&  function_def->Params.is_equal(signature_Construct->Params))
					{
						code = parse_function( SAssetView_Construct_Replacement );
						Gasa::LogEditor("Swapped: " +  to_fstring(function_def->Name));
					}
					else if ( String::are_equal(function_def->Name, signature_GetThumbnailScale->Name)
					&&  function_def->Params.is_equal(signature_GetThumbnailScale->Params))
					{
						code = parse_function( SAssetView_GetThumbnailScale_Replacement );
						Gasa::LogEditor("Swapped: " +  to_fstring(function_def->Name));
					}
				}
				break;
			}
			changed_SAssetViewCpp.append( code );
		}

		Builder SBlueprintActionMenu_Changed = Builder::open(path_SAssetView);
		SBlueprintActionMenu_Changed.print( def_comment(txt("This file was regenerated by GasaGen/ChangeEditorContentList.cpp")));
		SBlueprintActionMenu_Changed.print(changed_SAssetViewCpp);
		SBlueprintActionMenu_Changed.write();
		format_file(path_SAssetView, false );	
	}

	// Change SAssetView's Construct & GetThumbnailScale
	{
	#define path_SPropertyMenuAssetPicker \
	R"(C:\projects\Unreal\Surgo\UE\Engine\Source\Editor\PropertyEditor\Private\UserInterface\PropertyEditor\SPropertyMenuAssetPicker.cpp)"

		FileContents content = file_read_contents( GlobalAllocator, true, path_SPropertyMenuAssetPicker );
		CodeBody parsed = parse_global_body( StrC { content.size, (char const*)content.data });

		CodeFn signature = parse_function( code(
			void SPropertyMenuAssetPicker::Construct( const FArguments& InArgs ) {}
		));

		CodeBody changed = def_body(ECode::Global_Body);
		for ( Code code : parsed )
		{
			switch ( code->Type )
			{
				using namespace ECode;
				case Function:
				{
					CodeFn function_def = code.cast<CodeFn>();

					if ( String::are_equal(function_def->Name, signature->Name)
					&&  function_def->Params.is_equal(signature->Params))
					{
						code = parse_function( SPropertyMenuAssetPicker_Construct_Replacement );
						Gasa::LogEditor("Swapped: " +  to_fstring(function_def->Name));
					}
				}
				break;
			}
			changed.append( code );
		}

		Builder SBlueprintActionMenu_Changed = Builder::open(path_SPropertyMenuAssetPicker);
		SBlueprintActionMenu_Changed.print( def_comment(txt("This file was regenerated by GasaGen/ChangeEditorContentList.cpp")));
		SBlueprintActionMenu_Changed.print(changed);
		SBlueprintActionMenu_Changed.write();
		format_file(path_SPropertyMenuAssetPicker, false );	
	}
}
