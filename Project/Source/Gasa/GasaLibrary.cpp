#include "GasaLibrary.h"

#include "GasaDevOptions.h"
#include "GasaLevelScriptActor.h"
#include "Engine/LevelScriptActor.h"

UGasaDevOptions* UGasaLib::GetDevOptions(UObject* Context) {
	return Gasa::GetMutDevOptions();
}
