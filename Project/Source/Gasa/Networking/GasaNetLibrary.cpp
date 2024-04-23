#include "GasaNetLibrary.h"
#include "GasaNetLibrary_Inlines.h"

DEFINE_LOG_CATEGORY(LogGasaNet);

void NetLog( UObject const* Context, FString Message, EGasaVerbosity Verbosity = EGasaVerbosity::Log
		, FLogCategoryBase& Category  = LogGasaNet
		, bool              DumpStack = false
		, int32             Line      = __builtin_LINE()
		, const ANSICHAR*   File      = __builtin_FILE()
		, const ANSICHAR*   Func      = __builtin_FUNCTION() )
{
#if !UE_BUILD_SHIPPING && !NO_LOGGING
	ELogVerbosity::Type EngineVerbosity = (ELogVerbosity::Type) Verbosity;
	if ((EngineVerbosity & ELogVerbosity::VerbosityMask) > ELogVerbosity::COMPILED_IN_MINIMUM_VERBOSITY)
		return;
	if ((EngineVerbosity & ELogVerbosity::VerbosityMask) > Category.GetVerbosity())
		return;
	if ( Category.IsSuppressed(EngineVerbosity))
		return;

	AActor const* Actor = nullptr;
	FString       ActorLevel;
	{
		if (Context != nullptr)
		{
			if (Context->GetClass()->IsChildOf(AActor::StaticClass()))
				Actor = Cast<AActor>(Context);
			else if (Context->GetClass()->IsChildOf(UActorComponent::StaticClass()))
				Actor = Cast<UActorComponent>(Context)->GetOwner();
			// Its assumed that all GasaObjects have an outer actor
			else if (Context->IsA(UGasaObject::StaticClass()))
				Actor = Cast<AActor>(Context->GetOuter());
		}
		if (Actor)
		{
			if (Actor->HasLocalNetOwner())
				ActorLevel = TEXT("Net Owner");
			
			else if (Actor->HasAuthority())
				ActorLevel = TEXT("Server Authorized");
				
			else
				ActorLevel = TEXT("No Authority");
		}
		else
			ActorLevel = TEXT("Local");
	}

	FString NetMode = FString::Printf(TEXT("%-16s"), * GetNetworkModeStr(Context));
	ActorLevel      = FString::Printf(TEXT("%-18s"), * ActorLevel);
	FString Name    = FString::Printf(TEXT("%-40s"), * Context->GetName());
	FString FullMsg = NetMode + " " + ActorLevel + " " + Name + " : " + Message;
	
	static UE::Logging::Private::FStaticBasicLogDynamicData LOG_Dynamic;
	static UE::Logging::Private::FStaticBasicLogRecord
	LOG_Static(TEXT("%s -- %hs %hs(%d)"), File, Line, EngineVerbosity, LOG_Dynamic);

	SET_WARN_COLOR(COLOR_PURPLE)
	
	if (DumpStack)
		FDebug::DumpStackTraceToLog(EngineVerbosity);
	BasicLog(Category, &LOG_Static, * FullMsg, File, Func, Line);
	
	CLEAR_WARN_COLOR()
#endif
}