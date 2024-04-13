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
	FORCEINLINE
	UGasaGameInstance* GetGameInstance(UObject* Context) {
		// TODO(Ed): Do this with proper checks
		return Context->GetWorld()->GetGameInstance<UGasaGameInstance>();
	}
}