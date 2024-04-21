#include "GasaEditorModule.h"

#include "EditorDetails/GlobeProgressBarDetails.h"
#include "UI/GlobeProgressBar.h"

IMPLEMENT_PRIMARY_GAME_MODULE(FGasaEditorModule, GasaEditor, GasaEditor);

void FGasaEditorModule::StartupModule()
{
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
	