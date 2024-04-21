
#pragma once

#include "CoreMinimal.h"
#include "Gasa/GasaCommon.h"

#pragma region Engine Forwards
#pragma endregion Engine Forwards

#pragma region Engine Plugin Forwards
#pragma endregion Engine Plugin Forwards

// Gasa Editor

#pragma region Forwards
#pragma endregion Forwards

#pragma region Logging
DECLARE_LOG_CATEGORY_EXTERN(LogGasaEditor, Log, All);

namespace Gasa
{
	using ELogV = EGasaVerbosity;

	//◞ ‸ ◟//
	// Works for Unreal 5.4, Win64 MSVC (untested in other scenarios, for now)
	inline
	void LogEditor( FString Message, EGasaVerbosity Verbosity = EGasaVerbosity::Log
		, FLogCategoryBase& Category  = LogGasaEditor
		, bool              DumpStack = false
		, int32             Line      = __builtin_LINE()
		, const ANSICHAR*   File      = __builtin_FILE()
		, const ANSICHAR*   Func      = __builtin_FUNCTION() )
	{
	#if !UE_BUILD_SHIPPING && !NO_LOGGING
		ELogVerbosity::Type EngineVerbosity = (ELogVerbosity::Type) Verbosity;

		static UE::Logging::Private::FStaticBasicLogDynamicData LOG_Dynamic;
		static UE::Logging::Private::FStaticBasicLogRecord
		LOG_Static(TEXT("%80s -- %hs %hs(%d)"), File, Line, EngineVerbosity, LOG_Dynamic);

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

#define GasaEd_Fatal(Message)       UE_LOG( LogGasaEditor, Fatal,       TEXT("%s -- %hs %hs(%d)"), *Message, __builtin_FILE(), __func__, __builtin_LINE()  );
#define GasaEd_Error(Message)       UE_LOG( LogGasaEditor, Error,       TEXT("%s -- %hs %hs(%d)"), *Message, __builtin_File(), __func__, __builtin_LINE()  );
#define GasaEd_Warning(Message)     UE_LOG( LogGasaEditor, Warning,     TEXT("%s -- %hs %hs(%d)"), *Message, __builtin_File(), __func__, __builtin_LINE()  );
#define GasaEd_Display(Message)     UE_LOG( LogGasaEditor, Display,     TEXT("%s -- %hs %hs(%d)"), *Message, __builtin_File(), __func__, __builtin_LINE()  );
#define GasaEd_Log(Message)         UE_LOG( LogGasaEditor, Log,         TEXT("%s -- %hs %hs(%d)"), *Message, __builtin_File(), __func__, __builtin_LINE()  );
#define GasaEd_Verbose(Message)     UE_LOG( LogGasaEditor, Verbose,     TEXT("%s -- %hs %hs(%d)"), *Message, __builtin_File(), __func__, __builtin_LINE()  );
#define GasaEd_VeryVerbose(Message) UE_LOG( LogGasaEditor, VeryVerbose, TEXT("%s -- %hs %hs(%d)"), *Message, __builtin_File(), __func__, __builtin_LINE()  );
#pragma endregion Logging

#pragma region Timing
#pragma endregion Timing
