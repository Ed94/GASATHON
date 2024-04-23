#pragma once
#include "GameFramework/GameState.h"

#include "GasaCommon.h"
#include "Engine/Engine.h"
#include "Networking/GasaNetLibrary.h"

#include "GasaGameState.generated.h"

UCLASS( Blueprintable )
class GASA_API AGasaGameState : public AGameState
{
	GENERATED_BODY()
public:
#pragma region Cog
	// To make sure it doesn't get garbage collected.
	UPROPERTY()
	TObjectPtr<UObject> CogWindowManagerRef;

#if ENABLE_COG
	TObjectPtr<UCogWindowManager> CogWindowManager;
#endif
// ENABLE_COG
#pragma endregion Cog

	AGasaGameState();

#pragma region GameFramework
	UPROPERTY(BlueprintAssignable)
	FOnPawnReadySig Event_OnPlayerPawnReady;
	
	UFUNCTION()
	void OnGameFrameworkInitialized();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, meta=(DisplayName = "Game Framework Initialized"))
	void BP_OnGameFrameworkInitialized();

	UFUNCTION()
	void NotifyPlayerPawnReady(APawn* Pawn)
	{
		if (Event_OnPlayerPawnReady.IsBound())
			Event_OnPlayerPawnReady.Broadcast(Pawn);
	}
#pragma endregion GameFramework

#pragma region Networking
	UPROPERTY(Replicated, BlueprintReadOnly)
	AGasaPlayerState* ListenServerHost;

	UPROPERTY(ReplicatedUsing = "Client_OnRep_OnlinePlayers", BlueprintReadOnly)
	TArray<AGasaPlayerState*> OnlinePlayers;

	UFUNCTION()
	void Client_OnRep_OnlinePlayers();
#pragma endregion Networking

#pragma region Seamless Travel
	UPROPERTY(BlueprintAssignable)
	FOnTravelSig Event_OnSeamlessTravelStart;

	UPROPERTY(BlueprintAssignable, meta=(DisplayName="Event: On Seamless Travel End"))
	FOnTravelSig BP_Event_OnSeamlessTravelEnd;
	
	FOnTravelDelegate Event_OnSeamlessTravelEnd;

	UFUNCTION(NetMulticast, Reliable)
	void Multicast_R_NotifySeamlessTravelEnd();
#pragma endregion Seamless Travel
	
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
	
#pragma region GameState
	void HandleBeginPlay() override;
#pragma endregion GameState

#pragma region GameStateBase
	void SeamlessTravelTransitionCheckpoint(bool bToTransitionMap) override;
#pragma endregion GameStateBase

#pragma region Actor
	void BeginPlay() override;
	void PostInitializeComponents() override;
	void Tick( float DeltaSeconds ) override;
#pragma endregion Actor

#pragma region UObject
	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
#pragma endregion UObject
};

namespace Gasa
{
	inline AGasaGameState* GetGameState( UObject* Context )
	{
		UWorld* World = GEngine->GetWorldFromContextObject( Context, EGetWorldErrorMode::LogAndReturnNull );
		if ( World == nullptr )
		{
			Log( "World is null... are you running in a proper context?", ELogV::Error );
			return nullptr;
		}
		return Cast<AGasaGameState>( World->GetGameState() );
	}
}
