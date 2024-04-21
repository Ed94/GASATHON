
#pragma once

#include "CoreMinimal.h"
// #define private protected

#define global        
#define internal      static
#define local_persist static

#pragma region Math
#define m_pow2( value ) (value * value)
#pragma endregion Math

#pragma region Engine Forwards
struct FInputActionValue;

class IAbilitySystemInterface;

class UAbilitySystemComponent;
class UAbilitySystemInterface;
class UAttributeSet;
class UCameraComponent;
class UInputAction;
class UInputMappingContext;
class USphereComponent;
class USpringArmComponent;
#pragma endregion Engine Forwards

#pragma region Engine Plugin Forwards
class UCogWindowManager;
#pragma endregion Engine Plugin Forwards

// Gasa

#pragma region Forwards
class ACameraMount;
class AGasaCharacter;
class AGasaGameInstance;
class AGasaGameState;
class AGasaLevelScriptActor;
class AGasaPlayerController;
class AGasaPlayerState;

class UGasaAbilitySystemComp;
class UGasaAttributeSet;
class UGasaDevOptions;
class UGasaImage;
class UGasaOverlay;
class UGasaProgressBar;
class UGasaSizeBox;
class UHostWidgetController;
class UHUDHostWidget;
class UWidgetController;

struct FWidgetControllerData;
#pragma endregion Forwards

#pragma region Logging
// Straight from the Engine
UENUM(BlueprintType)
enum class EGasaVerbosity : uint8
{
	/** Not used */
	NoLogging		= 0,

	/** Always prints a fatal error to console (and log file) and crashes (even if logging is disabled) */
	// Fatal,
	// Just use GASA_Fatal...

	/** 
	 * Prints an error to console (and log file). 
	 * Commandlets and the editor collect and report errors. Error messages result in commandlet failure.
	 */
	Error = ELogVerbosity::Error,

	/** 
	 * Prints a warning to console (and log file).
	 * Commandlets and the editor collect and report warnings. Warnings can be treated as an error.
	 */
	Warning,

	/** Prints a message to console (and log file) */
	Display,

	/** Prints a message to a log file (does not print to console) */
	Log,

	/** 
	 * Prints a verbose message to a log file (if Verbose logging is enabled for the given category, 
	 * usually used for detailed logging) 
	 */
	Verbose,

	/** 
	 * Prints a verbose message to a log file (if VeryVerbose logging is enabled, 
	 * usually used for detailed logging that would otherwise spam output) 
	 */
	VeryVerbose,
};

DECLARE_LOG_CATEGORY_EXTERN(LogGasa, Log, All);

namespace Gasa
{
	using ELogV = EGasaVerbosity;

	//◞ ‸ ◟//
	// Works for Unreal 5.4, Win64 MSVC (untested in other scenarios, for now)
	inline
	void Log( FString Message, EGasaVerbosity Verbosity = EGasaVerbosity::Log
		, FLogCategoryBase& Category  = LogGasa
		, bool              DumpStack = false
		, int32             Line      = __builtin_LINE()
		, const ANSICHAR*   File      = __builtin_FILE()
		, const ANSICHAR*   Func      = __builtin_FUNCTION() )
	{
	#if !UE_BUILD_SHIPPING && !NO_LOGGING
		ELogVerbosity::Type EngineVerbosity = (ELogVerbosity::Type) Verbosity;

		static UE::Logging::Private::FStaticBasicLogDynamicData LOG_Dynamic;
		static UE::Logging::Private::FStaticBasicLogRecord
		LOG_Static(TEXT("%s -- %hs %hs(%d)"), File, Line, EngineVerbosity, LOG_Dynamic);

		if ((EngineVerbosity & ELogVerbosity::VerbosityMask) <= ELogVerbosity::COMPILED_IN_MINIMUM_VERBOSITY)
		{
			if ((EngineVerbosity & ELogVerbosity::VerbosityMask) <= Category.GetVerbosity())
			{
				if ( ! Category.IsSuppressed(EngineVerbosity))
				{
					if (DumpStack)
						FDebug::DumpStackTraceToLog(EngineVerbosity);
					BasicLog(Category, &LOG_Static, *Message, File, Func, Line);
				}
			}
		}
	#endif
	}
}

#define GASA_Fatal(Message)       UE_LOG( LogGasa, Fatal,       TEXT("%s -- %hs %hs(%d)"), *Message, __builtin_FILE(), __func__, __builtin_LINE()  );
#define GASA_Error(Message)       UE_LOG( LogGasa, Error,       TEXT("%s -- %hs %hs(%d)"), *Message, __builtin_File(), __func__, __builtin_LINE()  );
#define GASA_Warning(Message)     UE_LOG( LogGasa, Warning,     TEXT("%s -- %hs %hs(%d)"), *Message, __builtin_File(), __func__, __builtin_LINE()  );
#define GASA_Display(Message)     UE_LOG( LogGasa, Display,     TEXT("%s -- %hs %hs(%d)"), *Message, __builtin_File(), __func__, __builtin_LINE()  );
#define GASA_Log(Message)         UE_LOG( LogGasa, Log,         TEXT("%s -- %hs %hs(%d)"), *Message, __builtin_File(), __func__, __builtin_LINE()  );
#define GASA_Verbose(Message)     UE_LOG( LogGasa, Verbose,     TEXT("%s -- %hs %hs(%d)"), *Message, __builtin_File(), __func__, __builtin_LINE()  );
#define GASA_VeryVerbose(Message) UE_LOG( LogGasa, VeryVerbose, TEXT("%s -- %hs %hs(%d)"), *Message, __builtin_File(), __func__, __builtin_LINE()  );
#pragma endregion Logging

#pragma region Timing
namespace Gasa
{
	constexpr float _24Hz  = .042f;
	constexpr float _30Hz  = .033f;
	constexpr float _42Hz  = .024f;
	constexpr float _45Hz  = .022f;
	constexpr float _50Hz  = .020f;
	constexpr float _60Hz  = .016f;
	constexpr float _72Hz  = .014f;
	constexpr float _80Hz  = .013f;
	constexpr float _90Hz  = .011f;
	constexpr float _100Hz = .010f;
	constexpr float _120Hz = .008f;
	constexpr float _240Hz = .004f;
	constexpr float _480Hz = .002f;
}
#pragma endregion Timing
