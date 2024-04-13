#pragma once

#include "AbilitySystemComponent.h"
#include "AbilitySystemInterface.h"

#include "GasaCommon.h"

#include "GasaAbilitySystemComponent.generated.h"


UCLASS()
class GASA_API UGasaAbilitySystemComp : public UAbilitySystemComponent
{
	GENERATED_BODY()
public:
};

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
