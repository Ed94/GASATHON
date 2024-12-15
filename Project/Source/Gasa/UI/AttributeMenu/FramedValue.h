#pragma once
#include "UI/GasaUserWidget.h"

#include "FramedValue.generated.h"

UCLASS(Blueprintable)
class GASA_API UAttributeMenu_FramedValue : public UGasaUserWidget
{
	GENERATED_BODY()

public:
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Frame", meta=(BindWidget))
	UGasaSizeBox* SB_Root;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Frame", meta=(BindWidget))
	UGasaImage* BG;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Frame", meta=(BindWidget))
	UGasaImage* Border;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Frame", meta=(BindWidget))
	UTextBlock* Value;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Frame")
	float BoxHeight;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Frame")
	float BoxWidth;

	UFUNCTION(BlueprintCallable)
	void SetBackgroundBrush(FSlateBrush Brush);

	UFUNCTION(BlueprintCallable)
	void SetBorderBrush(FSlateBrush Brush);

	UFUNCTION(BlueprintCallable)
	void SetBoxSize(float Width, float Height);

	UFUNCTION(BlueprintCallable)
	void SetText(FText Content);
};
