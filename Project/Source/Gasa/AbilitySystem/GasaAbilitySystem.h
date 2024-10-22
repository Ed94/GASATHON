#pragma once

#include "GasaCommon.h"
#include "Engine/DataTable.h"

#include "GasaAbilitySystem.generated.h"


USTRUCT(BlueprintType)
struct GASA_API FAttributeSetField : public FTableRowBase
{
	GENERATED_BODY()
	
	FAttributeSetField() 
		: Name("Provide_Name")
		, Category("Optional Category")
		, Description("Provide Description")
		, BaseValue(0)
		, bUseMinAttribute(false)
		, bUseMaxAttribute(false)
		, MinAttribute("Attribute behaving has minimum value")
		, MinValue(0)
		, MaxAttribute("Attribute behaving has maximum value")
		, MaxValue(0)
	{}
	virtual ~FAttributeSetField()
	{}
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Gameplay Attribute")
	FName Name;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Gameplay Attribute")
	FName Category;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Gameplay Attribute")
	FString Description;
	
//	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Gameplay Attribute")
//	FGameplayTag Tag;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Gameplay Attribute")
	float BaseValue;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Gameplay Attribute")
	bool bUseMinAttribute;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Gameplay Attribute")
	bool bUseMaxAttribute;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Gameplay Attribute", meta =( EditCondition="bUseMinAttribute", EditConditionHides))
	FString MinAttribute;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Gameplay Attribute", meta =( EditCondition="bUseMinAttribute==false", EditConditionHides))
	float MinValue;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Gameplay Attribute", meta =( EditCondition="bUseMaxAttribute", EditConditionHides))
	FString MaxAttribute;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Gameplay Attribute", meta =( EditCondition="bUseMaxAttribute==false", EditConditionHides))
	float MaxValue;
};
