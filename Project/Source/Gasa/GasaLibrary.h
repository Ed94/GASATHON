#pragma once

#include "GasaCommon.h"

#include "GasaLibrary.Generated.h"


// UINTERFACE()
// class 

UCLASS(BlueprintType)
class GASA_API UGasaLib : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:

#pragma region Game
	
	UFUNCTION(BlueprintCallable, Category="Gasa|Game", BlueprintPure, meta=(WorldContext="Context"))
	static UGasaDevOptions* GetDevOptions(UObject* Context);
#pragma endregion Game
};

