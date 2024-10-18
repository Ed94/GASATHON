#pragma once

#include "GasaCommon.h"
#include "TaggedMessageRow.h"
#include "WidgetController.h"
#include "HostWidgetController.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FAttributeChangedSig, float, NewValue );

UCLASS( Blueprintable, BlueprintType )
class GASA_API UHostWidgetController : public UWidgetController
{
	GENERATED_BODY()
public:
#pragma region Attribute Events
	// Attribute Events are generated by GasaGen/GasaGen_HostWidgetController.cpp

	UPROPERTY( BlueprintAssignable, Category = "Attributes" )
	FAttributeChangedSig Event_OnHealthChanged;

	UPROPERTY( BlueprintAssignable, Category = "Attributes" )
	FAttributeChangedSig Event_OnMaxHealthChanged;

	UPROPERTY( BlueprintAssignable, Category = "Attributes" )
	FAttributeChangedSig Event_OnManaChanged;

	UPROPERTY( BlueprintAssignable, Category = "Attributes" )
	FAttributeChangedSig Event_OnMaxManaChanged;

	void HealthChanged( FOnAttributeChangeData const& Data );
	void MaxHealthChanged( FOnAttributeChangeData const& Data );
	void ManaChanged( FOnAttributeChangeData const& Data );
	void MaxManaChanged( FOnAttributeChangeData const& Data );
#pragma endregion Attribute Events

	UPROPERTY( BlueprintAssignable, Category = "Messages" )
	FTaggedMessageRowSig OnTaggedAssetMessage;

	void OnEffectAppliedAssetTags( FGameplayTagContainer const& AssetTags );

#pragma region WidgetController
	void BroadcastInitialValues() override;
	void BindCallbacksToDependencies() override;
#pragma endregion WidgetController
};
