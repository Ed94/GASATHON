#pragma once

#include "GasaCommon.h"

#include "GasaLibrary.Generated.h"


// UINTERFACE()
// class 

UCLASS(BlueprintType)
class GASA_API UGasaLib : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:

#pragma region Game
	UFUNCTION(BlueprintCallable, Category="Gasa|Game", BlueprintPure, meta=(WorldContext="Context"))
	static UGasaDevOptions* GetGasaDevOptions(UObject* Context);

	UFUNCTION(BlueprintCallable, Category="Gasa|Game", BlueprintPure, meta=(WorldContext="Context"))
	static UGasaGameInstance* GetGasaGameInstance(UObject* Context);
	
	UFUNCTION(BlueprintCallable, Category="Gasa|Game", BlueprintPure, meta=(WorldContext="Context"))
	static AGasaGameMode* GetGasaGameMode(UObject* Context);
	
	UFUNCTION(BlueprintCallable, Category="Gasa|Game", BlueprintPure, meta=(WorldContext="Context"))
	static AGasaGameState* GetGasaGameState(UObject* Context);
	
	UFUNCTION(BlueprintCallable, Category="Gasa|Game", BlueprintPure, meta=(WorldContext="Context"))
	static AGasaLevelScriptActor* GetGasaLevelActor(UObject* Context);

	UFUNCTION(BlueprintCallable, Category="Gasa|Game", BlueprintPure, meta=(WorldContext="Context"))
	static AGasaPlayerController* GetPrimaryGasaPlayerController(UObject* Context);
#pragma endregion Game

#pragma region Logging
	UFUNCTION(BlueprintCallable, Category="Gasa|Logging", meta=(WorldContext="Context", DisplayName="Log Gasa", AdvancedDisplay="bPrintToScreen", DevelopmentOnly))
	static void Log( UObject* Context, FString Message, EGasaVerbosity Verbosity = EGasaVerbosity::Log, bool bPrintOnScreen = false);

	static const FLinearColor logRegularColor;
	static float              printToScreenDuration;
#pragma endregion Logging

#pragma region Timing
public:

	static constexpr float _24Hz  = .042f;
	static constexpr float _30Hz  = .033f;
	static constexpr float _42Hz  = .024f;
	static constexpr float _45Hz  = .022f;
	static constexpr float _50Hz  = .020f;
	static constexpr float _60Hz  = .016f;
	static constexpr float _72Hz  = .014f;
	static constexpr float _80Hz  = .013f;
	static constexpr float _90Hz  = .011f;
	static constexpr float _100Hz = .010f;
	static constexpr float _120Hz = .083f;
	static constexpr float _240Hz = .004f;
	static constexpr float _480Hz = .002f;

	// Constant Rates

	UFUNCTION(BlueprintPure, Category = "Timing", Meta = (DisplayName = "24 Hz", CallableWithoutWorldContext))
	static FORCEINLINE float BP_Clock_24Hz () { return _24Hz;  }
	UFUNCTION(BlueprintPure, Category = "Timing", Meta = (DisplayName = "30 Hz", CallableWithoutWorldContext))
	static FORCEINLINE float BP_Clock_30Hz () { return _30Hz;  }
	UFUNCTION(BlueprintPure, Category = "Timing", Meta = (DisplayName = "42 Hz", CallableWithoutWorldContext))
	static FORCEINLINE float BP_Clock_42Hz () { return _42Hz;  }
	UFUNCTION(BlueprintPure, Category = "Timing", Meta = (DisplayName = "50 Hz", CallableWithoutWorldContext))
	static FORCEINLINE float BP_Clock_50Hz () { return _50Hz;  }
	UFUNCTION(BlueprintPure, Category = "Timing", Meta = (DisplayName = "60 Hz", CallableWithoutWorldContext))
	static FORCEINLINE float BP_Clock_60Hz () { return _60Hz;  }
	UFUNCTION(BlueprintPure, Category = "Timing", Meta = (DisplayName = "72 Hz", CallableWithoutWorldContext))
	static FORCEINLINE float BP_Clock_72Hz () { return _72Hz;  }
	UFUNCTION(BlueprintPure, Category = "Timing", Meta = (DisplayName = "80 Hz", CallableWithoutWorldContext))
	static FORCEINLINE float BP_Clock_80Hz () { return _80Hz;  }
	UFUNCTION(BlueprintPure, Category = "Timing", Meta = (DisplayName = "90 Hz", CallableWithoutWorldContext))
	static FORCEINLINE float BP_Clock_90Hz () { return _90Hz;  }
	UFUNCTION(BlueprintPure, Category = "Timing", Meta = (DisplayName = "100 Hz", CallableWithoutWorldContext))
	static FORCEINLINE float BP_Clock_100Hz() { return _100Hz; }
	UFUNCTION(BlueprintPure, Category = "Timing", Meta = (DisplayName = "120 Hz", CallableWithoutWorldContext))
	static FORCEINLINE float BP_Clock_120Hz() { return _120Hz; }
	UFUNCTION(BlueprintPure, Category = "Timing", Meta = (DisplayName = "240 Hz", CallableWithoutWorldContext))
	static FORCEINLINE float BP_Clock_240Hz() { return _240Hz; }
	UFUNCTION(BlueprintPure, Category = "Timing", Meta = (DisplayName = "480 Hz", CallableWithoutWorldContext))
	static FORCEINLINE float BPClock_480Hz() { return _480Hz; }

	// Standard Timing

	UFUNCTION(BlueprintPure, Category = "Timing", Meta = (DisplayName = "Time Rate", CallableWithoutWorldContext))
	static FORCEINLINE float GetStd_Timerate        () { return timingRate_Std;        }
	UFUNCTION(BlueprintPure, Category = "Timing", Meta = (DisplayName = "Quarter Time Rate", CallableWithoutWorldContext))
	static FORCEINLINE float GetStd_Timerate_Quarter() { return timingRate_Std / 4.0f; }
	UFUNCTION(BlueprintPure, Category = "Timing", Meta = (DisplayName = "Half Time Rate", CallableWithoutWorldContext))
	static FORCEINLINE float GetStd_Timerate_Half   () { return timingRate_Std / 2.0f; }
	UFUNCTION(BlueprintPure, Category = "Timing", Meta = (DisplayName = "2X Time Rate", CallableWithoutWorldContext))
	static FORCEINLINE float GetStd_Timerate_2X     () { return timingRate_Std * 2.0f; }
	UFUNCTION(BlueprintPure, Category = "Timing", Meta = (DisplayName = "4X Time Rate", CallableWithoutWorldContext))
	static FORCEINLINE float GetStd_Timerate_4X     () { return timingRate_Std * 2.0f; }

	UFUNCTION(BlueprintCallable, Category = "Timing", Meta = (DisplayName = "Set Time Rate"))
	static void SetStd_Timerate(float _rateDesired)
	{
		// Not the best check.. if inconsistency arises, use the a rigorous one.
		if (_rateDesired >= _24Hz)
		{
			timingRate_Std = _rateDesired;
		}
	}

protected:
	static float timingRate_Std;
#pragma endregion Timing
};
