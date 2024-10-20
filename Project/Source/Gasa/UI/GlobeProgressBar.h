#pragma once

#include "GasaCommon.h"
#include "GasaUserWidget.h"

#include "GlobeProgressBar.generated.h"

UCLASS()
class GASA_API UGlobeProgressBar : public UGasaUserWidget
{
	GENERATED_BODY()
	
public:

	// Just learning: https://benui.ca/unreal/build-widgets-in-editor/?utm_medium=social&utm_source=Discord
	UFUNCTION(CallInEditor, Category="Generate Designer Widget Template")
	void GenerateDesignerWidgetTemplate();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Globe")
	float GhostTargetPercent;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Globe")
	float GhostPercentInterpolationSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Globe")
	float GhostPercentChangeDelay;
	
	FTimerHandle GhostPercentChangeTimer;
	
	UFUNCTION()
	void GhostPercentUpdateViaTimer();
	
#pragma region Bindings
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidgetOptional), Category="Globe")
	UGasaSizeBox* Root_SB;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidgetOptional), Category="Globe")
	UGasaOverlay* Overlay;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidgetOptional), Category="Globe")
	UGasaImage* Bezel;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidgetOptional), Category="Globe")
	UGasaProgressBar* GhostBar;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidgetOptional), Category="Globe")
	UGasaProgressBar* Bar;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidgetOptional), Category="Globe")
	UGasaImage* Glass;

	UFUNCTION(BlueprintCallable, Category="Globe")
	void SetBezelStyle(FSlateBrush brush);

	UFUNCTION(BlueprintCallable, Category="Globe")
	void SetBarPadding( FMargin margin );
	
	UFUNCTION(BlueprintCallable, Category="Globe")
	void SetBarStyle(FProgressBarStyle style);

	UFUNCTION(BlueprintCallable, Category="Globe")
	void SetGhostBarStyle(FProgressBarStyle style);
	
	UFUNCTION(BlueprintCallable, Category="Globe")
	void SetGlassPadding( FMargin margin );
	
	UFUNCTION(BlueprintCallable, Category="Globe")
	void SetGlassStyle(FSlateBrush brush);

	UFUNCTION(BlueprintCallable, Category="Globe")
	void SetPercentage(float CurrentValue, float MaxValue);
	
	UFUNCTION(BlueprintCallable, Category="Globe")
	void SetSize(float width, float height);
#pragma endregion Bindings
	
	// UGlobeProgressBar(FObjectInitializer const& ObjectInitializer);

#pragma region Widget
	void SynchronizeProperties() override;
#pragma endregion Widget

	void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;

#pragma region UserWidget
	void NativePreConstruct() override;

	void NativeTick(const FGeometry& MyGeometry, float InDeltaTime);
#pragma endregion UserWidget

#pragma region Object
	void Serialize(FArchive& Ar) override;
	void Serialize(FStructuredArchive::FRecord Record) override;
#pragma endregion Object
};
