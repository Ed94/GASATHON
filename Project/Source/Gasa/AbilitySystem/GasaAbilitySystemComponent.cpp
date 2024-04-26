#include "GasaAbilitySystemComponent.h"

#include "Engine/Engine.h"
#include "Engine/GameViewportClient.h"
#include "Game/GasaGameState.h"
#include "Game/GasaPlayerController.h"
#include "GameFramework/HUD.h"
#include "Slate/SceneViewport.h"
#include "UI/GasaHUD.h"
#include "CogDebugDraw.h"


using namespace Gasa;

void UGasaAbilitySystemComp::OnAbilityActorInfoSet()
{
}

void UGasaAbilitySystemComp::EffectApplied(UAbilitySystemComponent* AbilitySystem, FGameplayEffectSpec const& Spec,
	FActiveGameplayEffectHandle ActiveEffect)
{
	FGameplayTagContainer Tags;
	Spec.GetAllAssetTags(Tags);
	for (FGameplayTag const& Tag : Tags)
	{
		// TODO(Ed): Broadcast the tag to the widget controller
		FString Msg = FString::Printf(TEXT("GE Tag: %s"), * Tag.ToString());
		Log(Msg);
	}
}

void UGasaAbilitySystemComp::InitAbilityActorInfo(AActor* InOwnerActor, AActor* InAvatarActor)
{
	Super::InitAbilityActorInfo(InOwnerActor, InAvatarActor);

	OnGameplayEffectAppliedDelegateToSelf.AddUObject(this, & ThisClass::EffectApplied);
}
