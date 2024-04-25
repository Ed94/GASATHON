#include "EffectProperties.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystemGlobals.h"
#include "GameplayEffect.h"
#include "GameplayEffectExtension.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/PlayerController.h"

void FEffectProperties::Populate(FGameplayEffectModCallbackData const& Data)
{
	Context             = Data.EffectSpec.GetContext();
	SourceAbilitySystem = Context.GetOriginalInstigatorAbilitySystemComponent();

	if (IsValid(SourceAbilitySystem)
		&& SourceAbilitySystem->AbilityActorInfo.IsValid()
		&& SourceAbilitySystem->AbilityActorInfo->AvatarActor.IsValid())
	{
		FGameplayAbilityActorInfo* AbilityInfo = SourceAbilitySystem->AbilityActorInfo.Get();
		SourceAvatar     = AbilityInfo->AvatarActor.Get();
		SourceController = AbilityInfo->PlayerController.Get();

		if (SourceController == nullptr && SourceAvatar)
		{
			APawn* Pawn = Cast<APawn>(SourceAvatar);
			if (Pawn)
				SourceController = Pawn->GetController();
		}
	}

	if (Data.Target.AbilityActorInfo.IsValid() && Data.Target.AbilityActorInfo->AvatarActor.IsValid())
	{
		FGameplayAbilityActorInfo* AbilityInfo = Data.Target.AbilityActorInfo.Get();
		TargetAvatar        = AbilityInfo->AvatarActor.Get();
		TargetController    = AbilityInfo->PlayerController.Get();
		TargetAbilitySystem = UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(TargetAvatar);
	}
}
