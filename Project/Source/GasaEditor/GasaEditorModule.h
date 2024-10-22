#pragma once

#include "Modules/ModuleInterface.h"

class GASAEDITOR_API FGasaEditorModule : public IModuleInterface
{
public:
	static bool IsAvailable() {
		return FModuleManager::Get().IsModuleLoaded("GasaEditor");
	}
	
	static FGasaEditorModule& Get() 	{
		return FModuleManager::LoadModuleChecked<FGasaEditorModule>("GasaEditor");
	}

protected:
	void StartupModule() override;
	void ShutdownModule() override;
};
