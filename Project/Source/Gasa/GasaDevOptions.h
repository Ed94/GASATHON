#pragma once

#include "Engine/DeveloperSettings.h"

#include "GasaDevOptions.generated.h"

UCLASS(Config=Game, DefaultConfig, meta=(DisplayName="Gasa"))
class GASA_API UGasaDevOptions : public UDeveloperSettings
{
	GENERATED_BODY()
public:
	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category="Tags")
	FName Tag_GlobalPPV;
};

namespace Gasa
{
	extern FName Tag_GlobalPPV;

	FORCEINLINE
	UGasaDevOptions const* GetDevOptions() {
		return GetDefault<UGasaDevOptions>();	
	}

	FORCEINLINE
	UGasaDevOptions* GetMutDevOptions() {
		return GetMutableDefault<UGasaDevOptions>();	
	}
}
