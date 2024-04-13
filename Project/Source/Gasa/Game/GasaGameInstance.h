#pragma once

#include "GasaCommon.h"
#include "GasaDevOptionsCache.h"

#include "GasaGameInstance.generated.h"

UCLASS(Blueprintable)
class GASA_API UGasaGameInstance : public UGameInstance
{
	GENERATED_BODY()
public:

	UPROPERTY(VisibleAnywhere, Category="Dev Cache")
	FGasaDevOptionsCache DevOptionsCache;

#pragma region GameInstance
	void Init() override;
#pragma endregion GameInstance
};

namespace Gasa
{
	inline
	UGasaGameInstance* GetGameInstance(UObject* Context)
	{
		UWorld* World = GEngine->GetWorldFromContextObject(Context, EGetWorldErrorMode::LogAndReturnNull);
		if (World == nullptr)
		{
			Log("World is null... are you running in a proper context?", ELogV::Error);
			return nullptr;
		}
		return Cast<UGasaGameInstance>(World->GetGameInstance());
	}
}
