#pragma once

#include "GasaEngineMinimal.h"

#include "GasaCommon.generated.h"

#define global        
#define internal      static
#define local_persist static

#define ccast( Type, Value ) ( *const_cast<(Type)*>( &( Value ) ) )
#define pcast( Type, Value ) ( *reinterpret_cast<(Type)*>( &( Value ) ) )
#define rcast( Type, Value ) reinterpret_cast<Type>( Value )
#define scast( Type, Value ) static_cast<Type>( Value )

#define bit(position) (1 << position)

#pragma region Math
#define m_pow2( value ) (value * value)
#pragma endregion Math

#pragma region Engine Forwards
struct FInputActionValue;
struct FGameplayEffectContextHandle;
struct FGameplayEffectModCallbackData;
struct FOnAttributeChangeData;
struct FReplicationFlags;

class AActor;
class APawn;
class APostProcessVolume;

class FOutBunch;

class IAbilitySystemInterface;

class UAbilitySystemComponent;
class UAbilitySystemInterface;
class UActorChannel;
class UAttributeSet;
class UCameraComponent;
class UGameplayEffect;
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
struct FWidgetControllerData;

class ACameraMount;
class AGasaCharacter;
class AGasaGameInstance;
class AGasaGameState;
class AGasaLevelScriptActor;
class AGasaPlayerController;
class AGasaPlayerState;
class APlayerCharacter;

class UGasaAbilitySystemComp;
class UGasaAttributeSet;
class UGasaDevOptions;
class UGasaImage;
class UGasaObject;
class UGasaOverlay;
class UGasaProgressBar;
class UGasaSizeBox;
class UHostWidgetController;
class UHUDHostWidget;
class UWidgetController;
#pragma endregion Forwards

#pragma region Bitfields
namespace Gasa
{
	inline
	bool Bitfield_IsSet(int32 Bitfield, int32 Bitmask) {
		bool Result = Bitmask == (Bitfield & Bitmask);
		return Result;
	}
	inline
	bool Bitfield_IsSetExactly(int32 Bitfield, int32 Bitmask)
	{
		bool Result = Bitfield == (Bitfield & Bitmask);
		return Result;
	}

	inline void Bitfield_Set   ( int32& Bitfield, int32 BitsToAdd )    { Bitfield |= BitsToAdd; }
	inline void Bitfield_Remove( int32& Bitfield, int32 BitsToRemove ) { Bitfield &= (! BitsToRemove); }
	inline void Bitfield_Toggle( int32& Bitfield, int32 Bitmask )      { Bitfield ^= Bitmask; }

	template<typename EnumType>
	inline
	bool Bitfield_IsSet(int32 Bitfield, EnumType Mask)
	{
		bool Result = int32(Mask) == (Bitfield & int32(Mask));
		return Result;
	}
	template<typename EnumType> inline void Bitfield_Set   ( int32& Bitfield, EnumType BitToAdd )    { Bitfield |= int32(BitToAdd); }
	template<typename EnumType> inline void Bitfield_Remove( int32& Bitfield, EnumType BitToRemove ) { Bitfield &= (! int32(BitToRemove)); }
	template<typename EnumType> inline void Bitfield_Toggle( int32& Bitfield, EnumType BitToToggle ) { Bitfield ^= int32(BitToToggle); }
}
#pragma endregion Bitfields

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

	// Works for Unreal 5.4, Win64 MSVC (untested in other scenarios, for now)
	inline
	void Log( FString Message
		, EGasaVerbosity    Verbosity = EGasaVerbosity::Log
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

#pragma region Delegates
DECLARE_MULTICAST_DELEGATE(FOnTravelDelegate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnTravelSig);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPawnSig);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPlayerCharacterReadySig, APlayerCharacter*, Character);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPawnReadySig, APawn*, Pawn);
#pragma endregion Delegates

