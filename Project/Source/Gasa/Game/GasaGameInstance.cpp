#include "GasaGameInstance.h"

void UGasaGameInstance::Init()
{
	Super::Init();

	DevOptionsCache.CachedDevOptions();

	using namespace Gasa;
	Log(FString::Printf(TEXT("UObject Size:  %d RT: %d"), sizeof(UObject), UObject::StaticClass()->PropertiesSize ));
}
