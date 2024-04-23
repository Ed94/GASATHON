﻿#pragma once

#include "Networking/GasaNetLibrary.h"
#include "GasaDevOptionsCache.h"
#include "Engine/Engine.h"

#include "Engine/GameInstance.h"
#include "GasaGameInstance.generated.h"

UENUM(BlueprintType)
enum class EGameFrameworkClassFlag : uint8
{
	None             = 0 UMETA(Hidden),
	GameMode         = 1 << 0,
	GameState        = 1 << 1,
	PlayerController = 1 << 2,
	PlayerState      = 1 << 3,
	Levels           = 1 << 4
};

UENUM(BlueprintType)
enum class EGameFrameworkState : uint8
{
	Initialized,
	Uninitialized
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnGameFrameworkInitializedSig);

UCLASS(Blueprintable)
class GASA_API UGasaGameInstance : public UGameInstance
{
	GENERATED_BODY()
public:

	UPROPERTY(VisibleAnywhere, Category="Dev Cache")
	FGasaDevOptionsCache DevOptionsCache;

#pragma region GameFramework
	UPROPERTY(BlueprintAssignable, Category = "GameFramework")
	FOnGameFrameworkInitializedSig Event_OnGameFrameworkInitialized;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameFramework")
	EGameFrameworkState GameFrameworkState;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameFramework", meta=(Bitmask, BitmaskEnum = EGameFrameworkClassFlag))
	int32 GameFrameworkClassesState;

	UFUNCTION(BlueprintCallable, Category="GameFramework")
	void ClearGameplayFrameworkState() 	{
		Gasa::Log("Clearing game framework state", EGasaVerbosity::Log, LogGasaNet ); // TODO(Ed): Make a default NetLog
		GameFrameworkClassesState = scast(int32, EGameFrameworkClassFlag::None);
		GameFrameworkState        = EGameFrameworkState::Uninitialized;
	}

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "GameFramework")
	FORCEINLINE bool IsGameFrameworkInitialized() { return GameFrameworkState == EGameFrameworkState::Initialized; }
	
	UFUNCTION(BlueprintCallable, Category="GameFramework")
	void NotifyGameFrameworkClassReady(EGameFrameworkClassFlag ClassReady);

	UFUNCTION(BlueprintCallable, Category = "GameFramework", meta=(BlueprintProtected))
	void ProcessGameFrameworkState();
#pragma endregion GameFramework

#pragma region NetSlime
	// NetSlime interface is generated by GasaGen/GasaGen_NetSlime.cpp
	FORCEINLINE ENetworkMode GetNetworkMode() const { return Gasa::GetNetworkMode( this ); }
	FORCEINLINE bool IsClient()               const { return Gasa::IsClient( this ); }
	FORCEINLINE bool IsListenServer()         const { return Gasa::IsListenServer( this ); }
	FORCEINLINE bool IsNetOwner()             const { return Gasa::IsNetOwner( this ); }
	FORCEINLINE bool IsServer()               const { return Gasa::IsServer( this ); }
	FORCEINLINE bool IsSimulatedProxy()       const { return Gasa::IsSimulatedProxy( this ); }
	FORCEINLINE void NetLog(
		FString           Message,
		EGasaVerbosity    Verbosity = EGasaVerbosity::Log,
		FLogCategoryBase& Category  = LogGasaNet,
		bool              DumpStack = false,
		int32             Line      = __builtin_LINE(),
		ANSICHAR const*   File      = __builtin_FILE(),
		ANSICHAR const*   Func      = __builtin_FUNCTION()
	)
	{
		Gasa::NetLog( this, Message, Verbosity, Category, DumpStack, Line, File, Func );
	}
#pragma endregion NetSlime

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
