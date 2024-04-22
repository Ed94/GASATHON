#include "HostWidgetController.h"
#include "AbilitySystem/GasaAttributeSet.h"
void UHostWidgetController::BroadcastInitialValues()
{
	Super::BroadcastInitialValues();
	UGasaAttributeSet* GasaAttribs = Cast<UGasaAttributeSet>( Data.Attributes );
	if ( GasaAttribs )
	{
		Event_OnHealthChanged.Broadcast( GasaAttribs->GetHealth() );
		Event_OnMaxHealthChanged.Broadcast( GasaAttribs->GetMaxHealth() );
		Event_OnManaChanged.Broadcast( GasaAttribs->GetMana() );
		Event_OnMaxManaChanged.Broadcast( GasaAttribs->GetMaxMana() );
	}
}
