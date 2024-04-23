#pragma once

#include "AbilitySystemInterface.h"
#include "GameFramework/Character.h"

#include "GasaCommon.h"
#include "Game/GasaGameState.h"
#include "Networking/GasaNetLibrary.h"

#include "GasaCharacter.generated.h"

UENUM(BlueprintType)
enum class EHighlight : uint8
{
	Disabled,
	Enabled,
};

UCLASS(Abstract)
class GASA_API AGasaCharacter : public ACharacter
	, public IAbilitySystemInterface
{
	GENERATED_BODY()
public:
	
	AGasaCharacter();

#pragma region Ability System
	UPROPERTY(EditAnywhere, Category="Ability System")
	bool bAutoAbilitySystem = true;
	
	UPROPERTY(EditAnywhere, Category="Ability System")
	TObjectPtr<UAbilitySystemComponent> AbilitySystem;

	UPROPERTY(EditAnywhere, Category="Ability System")
	TObjectPtr<UAttributeSet> Attributes;
#pragma endregion Ability System
	
#pragma region Combat
	UPROPERTY(EditAnywhere, Category="Combat")
	TObjectPtr<USkeletalMeshComponent> Weapon;
#pragma endregion Combat

#pragma region GameFramework
	UPROPERTY(BlueprintAssignable)
	FOnPawnSig Event_OnPawnReady;
	
	UFUNCTION()
	void Controller_OnPawnPossessed();

	UFUNCTION(BlueprintImplementableEvent)
	void BP_Controller_OnPawnPossessed();

	UFUNCTION(Server, Reliable)
	void ServerRPC_R_NotifyClientPawnReady();
#pragma endregion GameFramework

#pragma region Highlighting
	static constexpr float HighlightStencilDepth = 256.0;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Highlighting")
	EHighlight HighlightState;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Highlighting")
	FLinearColor HighlightColor;

	UFUNCTION(BlueprintCallable, Category="Highlighting")
	void SetHighlight( EHighlight Desired );

	UFUNCTION(BlueprintCallable, Category="Highlighting")
	FORCEINLINE void Highlight() { SetHighlight(EHighlight::Enabled); };
	
	UFUNCTION(BlueprintCallable, Category="Highlighting")
	FORCEINLINE void Dehighlight() { SetHighlight(EHighlight::Disabled); };
#pragma endregion Highlighting

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
	
#pragma region IAbilitySystem
	FORCEINLINE UAttributeSet*           GetAttributes()                            { return Attributes; }
	FORCEINLINE UAbilitySystemComponent* GetAbilitySystemComponent() const override { return AbilitySystem; }
#pragma endregion IAbilitySystem

#pragma region Pawn
	void OnRep_PlayerState() override;
	void PossessedBy(AController* NewController) override;
	void SetPlayerDefaults() override;
	void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
#pragma endregion Pawn
	
#pragma region Actor
	void BeginPlay() override;
	void Tick(float DeltaSeconds) override;
#pragma endregion Actor
};

namespace Gasa
{
	// UGasaAbilitySystemComp* GetAbilitySystem(AGasaCharacter* Object)
	// {
	// 	
	// }
}

