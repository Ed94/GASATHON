#pragma once
#include "UI/GasaUserWidget.h"

#include "TextValueRow.generated.h"

UCLASS(Blueprintable)
class GASA_API UAttributeMenu_TextValueRow : public UGasaUserWidget
{
	GENERATED_BODY()
	
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Frame", meta=(BindWidget))
	UGasaSizeBox* SB_Root;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Frame", meta=(BindWidget))
	UTextBlock* TB_AttributeName;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Frame", meta=(BindWidget))
	UAttributeMenu_FramedValue* Value;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Frame", meta=(BindWidget))
	UNamedSlot* NSlot;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Frame")
	FText AttributeName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Frame")
	float BoxHeight;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Frame")
	float BoxWidth;

	UFUNCTION(BlueprintCallable)
	void SetAttributeName(FText Name);

	UFUNCTION(BlueprintCallable)
	void SetBoxSize(float Width, float Height);

#pragma region UserWidget
	void NativePreConstruct() override;
#pragma endregion UserWidget
};