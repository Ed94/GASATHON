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
	if ( ! OnGameplayEffectAppliedDelegateToSelf.IsBoundToObject(this))
		OnGameplayEffectAppliedDelegateToSelf.AddUObject(this, & ThisClass::EffectApplied);
}

void UGasaAbilitySystemComp::EffectApplied(UAbilitySystemComponent* AbilitySystem, FGameplayEffectSpec const& Spec,
	FActiveGameplayEffectHandle ActiveEffect)
{
	Log("EFFECT APPLIED?");
	FGameplayTagContainer Tags;
	Spec.GetAllAssetTags(Tags);
	Event_OnEffectAppliedAssetTags.Broadcast(Tags);
}

void UGasaAbilitySystemComp::InitAbilityActorInfo(AActor* InOwnerActor, AActor* InAvatarActor)
{
	Super::InitAbilityActorInfo(InOwnerActor, InAvatarActor);
}
