// Generated by GasaGen/GasaGen_DevOptionsCache.cpp
#pragma once

#include "GasaDevOptionsCache.generated.h"

USTRUCT()
struct GASA_API FGasaDevOptionsCache
{
	GENERATED_BODY()

	UPROPERTY()
	UClass* Template_PlayerCamera;
	UPROPERTY()
	UClass* Template_HUD_HostUI;
	UPROPERTY()
	UClass* Template_HostWidgetController;

	void CachedDevOptions();
};
