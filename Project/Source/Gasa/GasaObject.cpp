#include "GasaObject.h"

#include "Engine/ActorChannel.h"
#include "Engine/BlueprintGeneratedClass.h"
#include "Engine/NetDriver.h"
#include "GameFramework/Actor.h"
using namespace Gasa;

UGasaObject::UGasaObject()
{
	bReplicates                 = false;
	bDisconnectOnBadReplication = false;
}

void UGasaObject::Destroy()
{
	if ( ! IsValid(this))
	{
		checkf(GetOwningActor()->HasAuthority() == true, TEXT("Destroy:: Object does not have authority to destroy itself!"));
		OnDestroyed();
		Event_OnDestroyed.Broadcast();
		ConditionalBeginDestroy();
	}
}

void UGasaObject::OnDestroyed()
{
}

bool UGasaObject::ReplicateAsSubobject(AActor* ActorResponsible, UActorChannel* Channel, FOutBunch* Bunch, FReplicationFlags* RepFlags)
{
	if (!ActorResponsible)
	{
		NetLog("Actor reponsible is null", ELogV::Error);
		return false;
	}
	if (!bDisconnectOnBadReplication && ActorResponsible != GetOuter())
	{
		NetLog("Attempted to replicate whose outer was not set to the actor whose responsible for replicating it as a subobject", ELogV::Error);
		return false;
	}
	return Channel->ReplicateSubobject(this, *Bunch, *RepFlags);
}

bool UGasaObject::CallRemoteFunction(UFunction* Function, void* Parms, FOutParmRec* OutParms, FFrame* Stack)
{
	check(! HasAnyFlags(RF_ClassDefaultObject));
	AActor*     Owner     = GetOwningActor();
	UNetDriver* NetDriver = Owner->GetNetDriver();
	if (NetDriver)
	{
		NetDriver->ProcessRemoteFunction(Owner, Function, Parms, OutParms, Stack, this);
		return true;
	}
	return false;
}

int32 UGasaObject::GetFunctionCallspace(UFunction* Function, FFrame* Stack)
{
	check(GetOuter() != nullptr);
	return GetOuter()->GetFunctionCallspace(Function, Stack);
}

void UGasaObject::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	// Add any Blueprint properties
	// This is not required if you do not want the class to be "Blueprintable"
	if (const UBlueprintGeneratedClass* BP = Cast<UBlueprintGeneratedClass>(GetClass()))
	{
		BP->GetLifetimeBlueprintReplicationList(OutLifetimeProps);
	}	
}

bool UGasaObject::IsSupportedForNetworking() const
{
	return bReplicates;
}
