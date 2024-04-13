// This was generated by GasaGen/GasaGen.cpp

#include "AttributeSet.h"

#include "GasaAttributeSet.generated.h"

UCLASS() class GASA_API UGasaAttributeSet : public UAttributeSet
{
	GENERATED_BODY()
public:
	UPROPERTY( ReplicatedUsing = Client_OnRep_Health, EditAnywhere, BlueprintReadWrite, Category = "Attributes" )
	FGameplayAttributeData Health;

	UPROPERTY( ReplicatedUsing = Client_OnRep_Health, EditAnywhere, BlueprintReadWrite, Category = "Attributes" )
	FGameplayAttributeData MaxHealth;

	UPROPERTY( ReplicatedUsing = Client_OnRep_Health, EditAnywhere, BlueprintReadWrite, Category = "Attributes" )
	FGameplayAttributeData Mana;

	UPROPERTY( ReplicatedUsing = Client_OnRep_Health, EditAnywhere, BlueprintReadWrite, Category = "Attributes" )
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

#pragma region UObject

	void GetLifetimeReplicatedProps( TArray< FLifetimeProperty >& OutLifetimeProps ) const override;
#pragma endregion UObject
};
