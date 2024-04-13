
#pragma once

#include "CoreMinimal.h"
// #define private protected

#define global        
#define internal      static
#define local_persist static

#pragma region Engine Forwards
struct FInputActionValue;

class UCameraComponent;
class UInputAction;
class UInputMappingContext;
class USpringArmComponent;
#pragma endregion Engine Forwards

#pragma region Engine Plugin Forwards
class UCogWindowManager;
#pragma endregion Engine Plugin Forwards

// Gasa

#pragma region Forwards
class ACameraMount;
class AGasaCharacter;
class AGasaLevelScriptActor;

class UGasaDevOptions;
#pragma endregion Forwards
