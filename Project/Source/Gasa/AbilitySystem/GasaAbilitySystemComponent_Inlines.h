#pragma once
#include "GasaAbilitySystemComponent.h"
#include "AbilitySystemInterface.h"

namespace Gasa
{
	inline
	UGasaAbilitySystemComp* GetAbilitySystem(UObject* Object)
	{
		if (Object->Implements<UAbilitySystemInterface>())
		{
			return Cast<UGasaAbilitySystemComp>( Cast<IAbilitySystemInterface>(Object)->GetAbilitySystemComponent() );
		}
		return nullptr;
	}
}
