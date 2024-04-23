#include "GasaGameInstance.h"

#include "Engine/NetDriver.h"
#include "Engine/World.h"
using namespace Gasa;

#pragma region GameFramework
// TODO(Ed): Make a NetLog

void UGasaGameInstance::NotifyGameFrameworkClassReady(EGameFrameworkClassFlag ClassReady)
{
	switch (ClassReady)
	{
		case EGameFrameworkClassFlag::GameMode:
			GameFrameworkClassesState |= (uint32)EGameFrameworkClassFlag::GameMode;
			NetLog("Gameplay Framework class ready: Game State", ELogV::Log, LogGasaNet );
		break;
		case EGameFrameworkClassFlag::GameState:
			GameFrameworkClassesState |= (uint32)EGameFrameworkClassFlag::GameState;
			NetLog("Gameplay Framework class ready: Game State", ELogV::Log, LogGasaNet );
		break;
		case EGameFrameworkClassFlag::PlayerController:
			GameFrameworkClassesState |= (uint32)EGameFrameworkClassFlag::PlayerController;
			NetLog("Gameplay Framework class ready: Player Controller", ELogV::Log, LogGasaNet);
		break;
		case EGameFrameworkClassFlag::PlayerState:
			GameFrameworkClassesState |= (uint32)EGameFrameworkClassFlag::PlayerState;
			NetLog("Gameplay Framework class ready: Player State", ELogV::Log, LogGasaNet);
		break;
		case EGameFrameworkClassFlag::Levels:
			GameFrameworkClassesState |= (uint32)EGameFrameworkClassFlag::Levels;
			NetLog("Gameplay Framework class ready: Levels", ELogV::Log, LogGasaNet);
		break;
	}
	ProcessGameFrameworkState();
}

void UGasaGameInstance::ProcessGameFrameworkState()
{
	switch (GameFrameworkState)
	{
		case EGameFrameworkState::Uninitialized:
		{
			uint32 InitializedFlags =
				(uint32)EGameFrameworkClassFlag::GameState        |
				(uint32)EGameFrameworkClassFlag::PlayerController |
				(uint32)EGameFrameworkClassFlag::PlayerState      |
				(uint32)EGameFrameworkClassFlag::Levels
			;

			if (GetWorld()->NetDriver == nullptr || GetWorld()->NetDriver->IsServer())
			{
				InitializedFlags |= (uint32)EGameFrameworkClassFlag::GameMode;
			}

			FString MsgGM = "GameMode        : " + FString::FromInt( Bitfield_IsSet( GameFrameworkClassesState, scast(uint32, EGameFrameworkClassFlag::GameMode )) );
			FString MsgGS = "GameState       : " + FString::FromInt( Bitfield_IsSet( GameFrameworkClassesState, scast(uint32, EGameFrameworkClassFlag::GameState )) );
			FString MsgPC = "PlayerController: " + FString::FromInt( Bitfield_IsSet( GameFrameworkClassesState, scast(uint32, EGameFrameworkClassFlag::PlayerController ) ));
			FString MsgPS = "PlayerState     : " + FString::FromInt( Bitfield_IsSet( GameFrameworkClassesState, scast(uint32, EGameFrameworkClassFlag::PlayerState ) ));
			FString MsgL  = "Levels          : " + FString::FromInt( Bitfield_IsSet( GameFrameworkClassesState, scast(uint32, EGameFrameworkClassFlag::Levels ) ));

			NetLog(MsgGM, ELogV::Log, LogGasaNet);
			NetLog(MsgGS, ELogV::Log, LogGasaNet);
			NetLog(MsgPC, ELogV::Log, LogGasaNet);
			NetLog(MsgPS, ELogV::Log, LogGasaNet);
			NetLog(MsgL,  ELogV::Log, LogGasaNet);
			
			if (GameFrameworkClassesState == InitializedFlags)
			{
				GameFrameworkState = EGameFrameworkState::Initialized;
				NetLog("Gameplay Framework initialized");
				
				Event_OnGameFrameworkInitialized.Broadcast();
			}
			break;
		}
	}
}
#pragma endregion GameFramework

#pragma region GameInstance
void UGasaGameInstance::Init()
{
	Super::Init();

	DevOptionsCache.CachedDevOptions();

	using namespace Gasa;
	NetLog(FString::Printf(TEXT("UObject Size:  %d RT: %d"), sizeof(UObject), UObject::StaticClass()->PropertiesSize ));
}
#pragma region GameInstance
