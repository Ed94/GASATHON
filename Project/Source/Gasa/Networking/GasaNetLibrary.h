// NetSlime: Ol'Reliable
#pragma once

#include "GasaCommon.h"

#define DOREPLIFETIME_DEFAULT_GAS(Class, ReplicatedVar) \
	DOREPLIFETIME_CONDITION_NOTIFY(Class, ReplicatedVar, COND_None, REPNOTIFY_Always)

DECLARE_LOG_CATEGORY_EXTERN(LogGasaNet, Log, All);

UENUM(BlueprintType)
enum class ENetworkMode : uint8
{
	Standalone,
	DedicatedServer,
	ListenServer,
	Client,
	MAX,
};

namespace Gasa
{
	constexpr float NetCullDist_Default   = 225000000.0f;
	constexpr float NetCullDist_Immediate = 250.0f   * 250.0f;
	constexpr float NetCullDist_VerClose  = 1000.0f  * 1000.0f;
	constexpr float NetCullDist_Close     = 3500.0f  * 3500.0f;
	constexpr float NetCullDist_Medium    = 5000.0f  * 5000.0f;
	constexpr float NetCullDist_Distant   = 7000.0f  * 7000.0f;
	constexpr float NetCullDist_Far       = 8500.0f  * 8500.0f;
	constexpr float NetCullDist_VeryFar   = 10000.0f * 10000.0f;
	constexpr float NetCullDist_VisualMax = 15000.0f * 15000.0f;

	void DrawNetCullingSphere(UObject const* Context, float Duration, float Thickness);

	ENetworkMode GetNetworkMode(UObject const* Context);
	FString GetNetworkModeStr(UObject const* Context);

	bool IsClient(UObject const* Context);
	bool IsListenServer(UObject const* Context);

	bool IsNetOwner(UObject const* Context);
	bool IsNetOwner(UGasaObject const* Context);
	bool IsNetOwner(AActor const* Context);

	bool IsServer(UObject const* Context);
	
	bool IsSimulatedProxy(UObject const* Context);
	bool IsSimulatedProxy(UGasaObject const* Context);
	bool IsSimulatedProxy(AActor const* Context);
	
	void NetLog( UObject const* Context, FString Message, EGasaVerbosity Verbosity = EGasaVerbosity::Log
		, FLogCategoryBase& Category  = LogGasaNet
		, bool              DumpStack = false
		, int32             Line      = __builtin_LINE()
		, const ANSICHAR*   File      = __builtin_FILE()
		, const ANSICHAR*   Func      = __builtin_FUNCTION() );
	
	bool ServerAuthorized(UObject const* Context);
	bool ServerAuthorized(UGasaObject const* Context);
	bool ServerAuthorized(AActor const* Context);
}
