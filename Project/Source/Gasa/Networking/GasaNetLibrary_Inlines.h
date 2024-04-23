#include "GasaNetLibrary.h"
#include "GasaObject.h"
#include "Engine/NetDriver.h"
#include "Game/GasaGameMode.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"

namespace Gasa
{
	// TODO(Ed): Profile these...

	inline
	void DrawNetCullingSphere(const UObject* Context, float Duration, float Thickness)
	{
		const AActor* actor = nullptr;
	
		if (Context->IsA(UGasaObject::StaticClass()))
			actor = Cast<AActor>(Context->GetOuter());
		
		else if (Context->IsA(AActor::StaticClass()))
			actor = Cast<AActor>(Context);	

		if (actor)
			UKismetSystemLibrary::DrawDebugSphere(actor
				, actor->GetActorLocation()
				, UKismetMathLibrary::Sqrt(actor->NetCullDistanceSquared) * 2
				, 12
				, FLinearColor(FColor::Emerald)
				, Duration
				, Thickness);
	}

	inline
	ENetworkMode GetNetworkMode(UObject const* Context)
	{
		if (Context == nullptr)
		{
			Log("Context is null...", ELogV::Error);
			return scast(ENetworkMode, ENetMode::NM_MAX);
		}
		UWorld* World = Context->GetWorld();
		if (World == nullptr) {
			Log("World is null... are you running in a proper context?", ELogV::Error);
			return scast(ENetworkMode, ENetMode::NM_MAX);
		}

		if (IsValid(World) == false)
			return ENetworkMode::Standalone;
		
		ENetworkMode NetMode = scast(ENetworkMode, World->GetNetMode());
		return NetMode;
	}

	inline
	FString GetNetworkModeStr(UObject const* Context)
	{
		FString Str;
		if (Context == nullptr)
			return Str;
		switch (GetNetworkMode(Context))
		{
			case ENetworkMode::Standalone:
				Str = TEXT("Standalone");
			break;
			case ENetworkMode::ListenServer:
				Str = TEXT("ListenServer");
			break;
			case ENetworkMode::DedicatedServer:
				Str = TEXT("DedicatedServer");
			break;
			case ENetworkMode::Client:
				Str = TEXT("Client");
			break;
		}
		return Str;
	}

	inline
	bool IsClient(UObject const* Context)
	{
		if (Context == nullptr || Context->GetWorld() == nullptr)
			return false;
		
		UNetDriver* NetDriver = Context->GetWorld()->NetDriver;
		bool Result = NetDriver && ! NetDriver->IsServer();
		return Result;
	}

	inline
	bool IsListenServer(UObject const* Context)
	{
		if (Context == nullptr || Context->GetWorld() == nullptr)
			return false;

		UNetDriver* NetDriver = Context->GetWorld()->NetDriver;
		bool Result = NetDriver && NetDriver->GetNetMode() == ENetMode::NM_ListenServer;
		return Result;	
	}

	inline
	bool IsNetOwner(UObject const* Context)
	{
		if (Context == nullptr || Context->GetWorld() == nullptr)
			return false;

		AActor const* Actor = nullptr;
		
		if (Context->IsA(AActor::StaticClass()))
			Actor = Cast<AActor>(Context);
		else if (Context->GetClass()->IsChildOf(UActorComponent::StaticClass()))
			Actor = Cast<UActorComponent>(Context)->GetOwner();
		// Its assumed that all GasaObjects have an outer actor
		else if (Context->IsA(UGasaObject::StaticClass()))
			Actor = Cast<AActor>(Context->GetOuter());
		else
		{
			UObject const* Outermost = Context->GetOutermostObject();
			if (Outermost->IsA(AActor::StaticClass()))
				Actor = Cast<AActor>(Outermost);
		}

		if (Actor == nullptr)
		{
			Log("Could not get actor reference", ELogV::Warning, LogGasaNet);
			return false;
		}
		bool Result = Actor->HasLocalNetOwner();
		return Result;
	}

	inline
	bool IsNetOwner(UGasaObject const* Context)
	{
		if (Context == nullptr || Context->GetWorld() == nullptr)
			return false;

		AActor const* Actor = Cast<AActor>(Context->GetOuter());
		if (Actor == nullptr)
		{
			Log("Could not get actor reference", ELogV::Warning, LogGasaNet);
			return false;
		}
		bool Result = Actor->HasLocalNetOwner();
		return Result;	
	}

	inline
	bool IsNetOwner(AActor const* Actor)
	{
		if (Actor == nullptr || Actor->GetWorld() == nullptr)
			return false;
		bool Result = Actor->HasLocalNetOwner();
		return Result;		
	}

	inline
	bool IsServer(UObject const* Context)
	{
		if (Context == nullptr || Context->GetWorld() == nullptr)
			return false;

		UNetDriver* NetDriver = Context->GetWorld()->NetDriver;
		bool Result = NetDriver && NetDriver->IsServer();
		return Result;
	}

	inline
	bool IsSimulatedProxy(UObject const* Context)
	{
		if (Context == nullptr || Context->GetWorld() == nullptr)
			return false;

		AActor const* Actor = nullptr;
		
		if (Context->IsA(AActor::StaticClass()))
			Actor = Cast<AActor>(Context);
		else if (Context->GetClass()->IsChildOf(UActorComponent::StaticClass()))
			Actor = Cast<UActorComponent>(Context)->GetOwner();
		// Its assumed that all GasaObjects have an outer actor
		else if (Context->IsA(UGasaObject::StaticClass()))
			Actor = Cast<AActor>(Context->GetOuter());
		else
		{
			UObject const* Outermost = Context->GetOutermostObject();
			if (Outermost->IsA(AActor::StaticClass()))
				Actor = Cast<AActor>(Outermost);
		}

		if (Actor == nullptr)
		{
			Log("Could not get actor reference", ELogV::Warning, LogGasaNet);
			return false;
		}
		bool Result = Actor->GetLocalRole() == ENetRole::ROLE_SimulatedProxy;
		return Result;	
	}

	inline
	bool IsSimulatedProxy(UGasaObject const* Context)
	{
		if (Context == nullptr || Context->GetWorld() == nullptr)
			return false;

		AActor const* Actor = Cast<AActor>(Context->GetOuter());
		if (Actor == nullptr)
		{
			Log("Could not get actor reference", ELogV::Warning, LogGasaNet);
			return false;
		}
		bool Result = Actor->GetLocalRole() == ENetRole::ROLE_SimulatedProxy;
		return Result;	
	}
	
	inline
	bool IsSimulatedProxy(AActor const* Actor)
	{
		if (Actor == nullptr || Actor->GetWorld() == nullptr)
			return false;
		bool Result = Actor->GetLocalRole() == ENetRole::ROLE_SimulatedProxy;
		return Result;	
	}

	inline
	bool ServerAuthorized(UObject const* Context)
	{
		if (Context == nullptr || Context->GetWorld() == nullptr)
			return false;

		AActor const* Actor = nullptr;

		if (Context->IsA(AActor::StaticClass()))
			Actor = Cast<AActor>(Context);
		else if (Context->GetClass()->IsChildOf(UActorComponent::StaticClass()))
			Actor = Cast<UActorComponent>(Context)->GetOwner();
		// Its assumed that all GasaObjects have an outer actor
		else if (Context->IsA(UGasaObject::StaticClass()))
			Actor = Cast<AActor>(Context->GetOuter());
		else
		{
			UObject const* Outermost = Context->GetOutermostObject();
			if (Outermost->IsA(AActor::StaticClass()))
				Actor = Cast<AActor>(Outermost);
		}

		if (Actor == nullptr)
		{
			Log("Could not get actor reference", ELogV::Warning, LogGasaNet);
			return false;
		}
		bool Result = Actor->HasAuthority();
		return Result;
	}
	
	inline
	bool ServerAuthorized(UGasaObject const* Context)
	{
		if (Context == nullptr || Context->GetWorld() == nullptr)
			return false;

		AActor const* Actor = Cast<AActor>(Context->GetOuter());
		if (Actor == nullptr)
		{
			Log("Could not get actor reference", ELogV::Warning, LogGasaNet);
			return false;
		}
		bool Result = Actor->HasAuthority();
		return Result;
	}

	inline
	bool ServerAuthorized(AActor const* Actor)
	{
		if (Actor == nullptr || Actor->GetWorld() == nullptr)
			return false;
		bool Result = Actor->HasAuthority();
		return Result;
	}
}
