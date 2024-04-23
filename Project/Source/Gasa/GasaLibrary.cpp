#include "GasaLibrary.h"

#include "GasaDevOptions.h"
#include "Game/GasaLevelScriptActor.h"
#include "Engine/LevelScriptActor.h"
#include "Game/GasaGameInstance.h"
#include "Game/GasaGameMode.h"
#include "Game/GasaGameState.h"
#include "Game/GasaPlayerController.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Misc/ConfigCacheIni.h"

#pragma region Game
UGasaDevOptions* UGasaLib::GetGasaDevOptions(UObject* Context) {
	return Gasa::GetMutDevOptions();
}

UGasaGameInstance* UGasaLib::GetGasaGameInstance(UObject* Context) {
	return Gasa::GetGameInstance(Context);
}

AGasaGameMode* UGasaLib::GetGasaGameMode(UObject* Context) {
	return Gasa::GetGameMode(Context);
}

AGasaGameState* UGasaLib::GetGasaGameState(UObject* Context) {
	return Gasa::GetGameState(Context);
}

AGasaLevelScriptActor* UGasaLib::GetGasaLevelActor(UObject* Context) {
	return Gasa::GetLevelActor(Context);
}

AGasaPlayerController* UGasaLib::GetPrimaryGasaPlayerController(UObject* Context) {
	return Gasa::GetPrimaryPlayerController(Context);
}
#pragma endregion Game

#pragma region Logging
DEFINE_LOG_CATEGORY_STATIC(LogGasaBP, Log, All);

void UGasaLib::Log(UObject* Context, FString Message, EGasaVerbosity Verbosity, bool bPrintToScreen)
{
	#if !UE_BUILD_SHIPPING && !NO_LOGGING
	{
		ELogVerbosity::Type EngineVerbosity = (ELogVerbosity::Type) Verbosity;
	
		static UE::Logging::Private::FStaticBasicLogDynamicData LOG_Dynamic;
		static UE::Logging::Private::FStaticBasicLogRecord
		LOG_Static(TEXT("%s -- %s"), __builtin_FILE(), __builtin_LINE(), EngineVerbosity, LOG_Dynamic);

		if ((EngineVerbosity & ELogVerbosity::VerbosityMask) <= ELogVerbosity::COMPILED_IN_MINIMUM_VERBOSITY)
		{
			if ((EngineVerbosity & ELogVerbosity::VerbosityMask) <= LogGasaBP.GetVerbosity())
			{
				if ( ! LogGasaBP.IsSuppressed(EngineVerbosity))
				{
					BasicLog( LogGasaBP, &LOG_Static, *Message, *Context->GetName() );
				}
			}
		}
	}
	#endif
	if (bPrintToScreen)
	{
		if (GAreScreenMessagesEnabled)
		{
			if (GConfig && printToScreenDuration < 0)
			{
				GConfig->GetFloat(TEXT("Kismet"), TEXT("PrintStringDuration"), printToScreenDuration, GEngineIni);
			}
			GEngine->AddOnScreenDebugMessage((uint64)-1, printToScreenDuration, logRegularColor.ToFColor(true), Message);
		}
		else
		{
			UE_LOG(LogBlueprint, VeryVerbose, TEXT("Screen messages disabled (!GAreScreenMessagesEnabled).  Cannot print to screen."));
		}
	}
};

// Protected

const FLinearColor UGasaLib::logRegularColor       = FLinearColor(0.0, 0.66, 1.0);
float              UGasaLib::printToScreenDuration = 10.0f;
#pragma endregion Logging

#pragma region Timing
// Protected

float UGasaLib::timingRate_Std = Gasa::_60Hz;
#pragma endregion Timing
