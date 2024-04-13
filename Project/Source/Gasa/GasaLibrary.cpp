#include "GasaLibrary.h"

#include "GasaDevOptions.h"
#include "Game/GasaLevelScriptActor.h"
#include "Engine/LevelScriptActor.h"
#include "Game/GasaGameInstance.h"
#include "Game/GasaGameMode.h"
#include "Game/GasaGameState.h"
#include "Game/GasaPlayerController.h"
#include "Kismet/KismetSystemLibrary.h"

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
void UGasaLib::Log(UObject* Context, FString Message, EGasaVerbosity Verbosity, bool bPrintToScreen)
{
	Gasa::Log(Message, Verbosity, LogGasa, false, 0, "", TCHAR_TO_ANSI( *Context->GetName() ));
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

float UGasaLib::timingRate_Std = UGasaLib::_60Hz;
#pragma endregion Timing
