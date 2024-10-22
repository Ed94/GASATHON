#pragma once

#include "UObject/Interface.h"

#include "CombatInterface.generated.h"


UINTERFACE(MinimalAPI)
class UCombat : public UInterface
{
	GENERATED_BODY()
};

class GASA_API ICombat
{
	GENERATED_BODY()

public:
	virtual int32 GetPlayerLevel();
};
