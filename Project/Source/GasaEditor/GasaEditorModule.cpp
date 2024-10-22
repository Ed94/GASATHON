#include "GasaEditorModule.h"


#include "Framework/Commands/Commands.h"
#include "Framework/MultiBox/MultiBoxBuilder.h"
#include "Framework/Commands/UICommandList.h"
#include "EditorStyleSet.h"
#include "LevelEditor.h"

#include "EditorDetails/GlobeProgressBarDetails.h"
#include "GasaGen/GasaGen.h"
#include "UI/GlobeProgressBar.h"


IMPLEMENT_PRIMARY_GAME_MODULE(FGasaEditorModule, GasaEditor, GasaEditor);

#define LOCTEXT_NAMESPACE "GasaEditor"

class FGasaEditorCommands : public TCommands<FGasaEditorCommands>
{
public:
	FGasaEditorCommands()
        : TCommands<FGasaEditorCommands>(
            TEXT("GasaEditorCommands"),
            NSLOCTEXT("Contexts", "GasaEditorCommands", "GASATHON Editor Commands"),
            NAME_None,
			FAppStyle::GetAppStyleSetName())
    {}

    virtual void RegisterCommands() override
    {
        UI_COMMAND(GasaModule_Codegen_Command, "Run GasaGen Codegen", "Execute gasa codegen pass", EUserInterfaceActionType::Button, FInputChord());
    }

    TSharedPtr<FUICommandInfo> GasaModule_Codegen_Command;
};

void FGasaEditorModule::StartupModule()
{
	// Codegen commands
	{
		FGasaEditorCommands::Register();
	
		TSharedPtr<FUICommandList> PluginCommands = MakeShareable(new FUICommandList);
		PluginCommands->MapAction( FGasaEditorCommands::Get().GasaModule_Codegen_Command,
				FExecuteAction::CreateStatic(& Execute_GasaModule_Codegen),
				FCanExecuteAction()
		);

		FLevelEditorModule&   LEM          = FModuleManager::LoadModuleChecked<FLevelEditorModule>("LevelEditor");
		TSharedPtr<FExtender> MenuExtender = MakeShareable(new FExtender);
		MenuExtender->AddMenuExtension(
			"Tools",
			EExtensionHook::First,
			PluginCommands,
			FMenuExtensionDelegate::CreateLambda([](FMenuBuilder& Builder) {
				Builder.AddMenuEntry(FGasaEditorCommands::Get().GasaModule_Codegen_Command);
				Builder.AddSeparator(); // Add a separator after your command
			})
		);
		LEM.GetMenuExtensibilityManager()->AddExtender(MenuExtender);
	}

	FPropertyEditorModule& PropertyEditor = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");

	PropertyEditor.RegisterCustomClassLayout( UGlobeProgressBar::StaticClass()->GetFName()
		, FOnGetDetailCustomizationInstance::CreateStatic(& FGlobeProgressBarDetails::MakeInstance)
	);
}

void FGasaEditorModule::ShutdownModule()
{
	if (FModuleManager::Get().IsModuleLoaded("PropertyEditor"))
	{
		FPropertyEditorModule& PropertyEditor = FModuleManager::GetModuleChecked<FPropertyEditorModule>("PropertyEditor");
		PropertyEditor.UnregisterCustomClassLayout(UGlobeProgressBar::StaticClass()->GetFName());
	}
}
	
#undef LOCTEXT_NAMESPACE
	
