#pragma once
#include "Blueprint/UserWidget.h"

#include "GasaUserWidget.generated.h"

UCLASS(Blueprintable)
class GASA_API UGasaUserWidget : public UUserWidget
{
	GENERATED_BODY()
public:

	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UObject> WidgetController;

	UGasaUserWidget(FObjectInitializer const& ObjectInitializer);

	UFUNCTION(BlueprintCallable)
	void SetWidgetController(UObject* Controller)
	{
		WidgetController = Controller;
		OnWidgetControllerSet();
	}
	
	UFUNCTION(BlueprintImplementableEvent)
	void OnWidgetControllerSet();
};
