#pragma once

#include "Engine/DeveloperSettings.h"

#include "GasaCommon.h"

#include "GasaDevOptions.generated.h"

UCLASS(Config=Game, DefaultConfig, meta=(DisplayName="Gasa"))
class GASA_API UGasaDevOptions : public UDeveloperSettings
{
	GENERATED_BODY()
public:

	// NOTE(Ed): Any Soft-References must have their includes defined in GasaDevOptions.cpp
	// They are used by GasaGen for the GasaDevOptionsCache

	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category="UI")
	TSoftClassPtr<ACameraMount> Template_PlayerCamera;

	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category="UI")
	TSoftClassPtr<UUI_HostWidget> Template_HUD_HostUI;

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
