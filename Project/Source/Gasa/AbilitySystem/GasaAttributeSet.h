// Generated by GasaGen/GasaGen_UGasaAttributeSet.cpp
#pragma once

#include "AttributeSet.h"
#include "GasaAttributeSet.generated.h"

UCLASS()
class GASA_API UGasaAttributeSet : public UAttributeSet
{
	GENERATED_BODY()
public:
	UPROPERTY( ReplicatedUsing = Client_OnRep_Health, EditAnywhere, BlueprintReadWrite, Category = "Attributes" )
	FGameplayAttributeData Health;

	UPROPERTY( ReplicatedUsing = Client_OnRep_MaxHealth, EditAnywhere, BlueprintReadWrite, Category = "Attributes" )
	FGameplayAttributeData MaxHealth;

	UPROPERTY( ReplicatedUsing = Client_OnRep_Mana, EditAnywhere, BlueprintReadWrite, Category = "Attributes" )
	FGameplayAttributeData Mana;

	UPROPERTY( ReplicatedUsing = Client_OnRep_MaxMana, EditAnywhere, BlueprintReadWrite, Category = "Attributes" )
	FGameplayAttributeData MaxMana;

	UGasaAttributeSet();

	UFUNCTION()
	void Client_OnRep_Health( FGameplayAttributeData& PrevHealth );
	UFUNCTION()
	void Client_OnRep_MaxHealth( FGameplayAttributeData& PrevMaxHealth );
	UFUNCTION()
	void Client_OnRep_Mana( FGameplayAttributeData& PrevMana );
	UFUNCTION()
	void Client_OnRep_MaxMana( FGameplayAttributeData& PrevMaxMana );

#pragma region Getters
	static FGameplayAttribute GetHealthAttribute()
	{
		static FProperty* Prop = FindFieldChecked<FProperty>( UGasaAttributeSet::StaticClass(), GET_MEMBER_NAME_CHECKED( UGasaAttributeSet, Health ) );
		return Prop;
	}
	static FGameplayAttribute GetMaxHealthAttribute()
	{
		static FProperty* Prop = FindFieldChecked<FProperty>( UGasaAttributeSet::StaticClass(), GET_MEMBER_NAME_CHECKED( UGasaAttributeSet, MaxHealth ) );
		return Prop;
	}
	static FGameplayAttribute GetManaAttribute()
	{
		static FProperty* Prop = FindFieldChecked<FProperty>( UGasaAttributeSet::StaticClass(), GET_MEMBER_NAME_CHECKED( UGasaAttributeSet, Mana ) );
		return Prop;
	}
	static FGameplayAttribute GetMaxManaAttribute()
	{
		static FProperty* Prop = FindFieldChecked<FProperty>( UGasaAttributeSet::StaticClass(), GET_MEMBER_NAME_CHECKED( UGasaAttributeSet, MaxMana ) );
		return Prop;
	}

	FORCEINLINE float GetHealth() const { return Health.GetCurrentValue(); }
	FORCEINLINE float GetMaxHealth() const { return MaxHealth.GetCurrentValue(); }
	FORCEINLINE float GetMana() const { return Mana.GetCurrentValue(); }
	FORCEINLINE float GetMaxMana() const { return MaxMana.GetCurrentValue(); }
	#pragma endregion Getters

#pragma region Setters
	    FORCEINLINE void
	                 SetHealth( float NewVal );
	FORCEINLINE void SetMaxHealth( float NewVal );
	FORCEINLINE void SetMana( float NewVal );
	FORCEINLINE void SetMaxMana( float NewVal );

	FORCEINLINE void InitHealth( float NewVal )
	{
		Health.SetBaseValue( NewVal );
		Health.SetCurrentValue( NewVal );
	}
	FORCEINLINE void InitMaxHealth( float NewVal )
	{
		MaxHealth.SetBaseValue( NewVal );
		MaxHealth.SetCurrentValue( NewVal );
	}
	FORCEINLINE void InitMana( float NewVal )
	{
		Mana.SetBaseValue( NewVal );
		Mana.SetCurrentValue( NewVal );
	}
	FORCEINLINE void InitMaxMana( float NewVal )
	{
		MaxMana.SetBaseValue( NewVal );
		MaxMana.SetCurrentValue( NewVal );
	}
	#pragma endregion Setters

#pragma region UObject
	    void
	    GetLifetimeReplicatedProps( TArray<FLifetimeProperty>& OutLifetimeProps ) const override;
#pragma endregion UObject
};
