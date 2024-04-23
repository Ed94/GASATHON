#pragma once

#include "Modules/ModuleInterface.h"
#include "Modules/ModuleManager.h"

class GASA_API FGasaModule : public IModuleInterface
{
public:
	static bool IsAvailable() {
		return FModuleManager::Get().IsModuleLoaded("Gasa");
	}
	
	static FGasaModule& Get() 	{
		return FModuleManager::LoadModuleChecked<FGasaModule>("Gasa");
	}
	
protected:
	void StartupModule() override;
	void ShutdownModule() override;
};
