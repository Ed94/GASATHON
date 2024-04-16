#pragma once

#include "GasaCommon.h"
#include "GasaUserWidget.h"

#include "GlobeProgressBar.generated.h"

UCLASS()
class GASA_API UGlobeProgressBar : public UGasaUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget), Category="Globe")
	UGasaSizeBox* SizeBox_Root;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget), Category="Globe")
	UGasaOverlay* Overlay_Root;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget), Category="Globe")
	UGasaImage* Glass;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget), Category="Globe")
	UGasaImage* BG;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget), Category="Globe")
	UGasaProgressBar* Bar;
	
	// UGlobeProgressBar(FObjectInitializer const& ObjectInitializer);

	UFUNCTION(BlueprintCallable, Category="Globe")
	void SetBackgroundStyle(FSlateBrush brush);

	UFUNCTION(BlueprintCallable, Category="Globe")
	void SetBarPadding( FMargin margin );
	
	UFUNCTION(BlueprintCallable, Category="Globe")
	void SetBarStyle(FProgressBarStyle style);

	UFUNCTION(BlueprintCallable, Category="Globe")
	void SetGlassPadding( FMargin margin );
	
	UFUNCTION(BlueprintCallable, Category="Globe")
	void SetGlassStyle(FSlateBrush brush);
	
	UFUNCTION(BlueprintCallable, Category="Globe")
	void SetSize(float width, float height);

#if 0
	UFUNCTION(BlueprintCallable, Category="Globe")
	void UpdateSize();
	
	UFUNCTION(BlueprintCallable, Category="Globe")
	void UpdateBackground();
#endif

#pragma region UserWidget
	void NativePreConstruct() override;
#pragma endregion UserWidget
};
