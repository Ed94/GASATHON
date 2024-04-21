#pragma once
#include "Blueprint/UserWidget.h"
#include "GasaCommon.h"

#include "GasaUserWidget.generated.h"


UCLASS(Blueprintable)
class GASA_API UGasaUserWidget : public UUserWidget
{
	GENERATED_BODY()
public:

	UFUNCTION()
	void OnLooseParentCompiled(UBlueprint* BP);

	UFUNCTION(CallInEditor, Category="Parent (Expriemental)", meta=(
		ToolTip="Exprimental: This will overrite the current LooseParent widgets or create them in this user widget. Beware it will be destructive changes"))
	void GenerateParentHierarchyFromLooseParent();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Parent (Expriemental)")
	bool bUpdateOnParentCompile = false;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Parent (Expriemental)")
	TSubclassOf<UGasaUserWidget> LooseParent;

	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UWidgetController> WidgetController;

	UGasaUserWidget(FObjectInitializer const& ObjectInitializer);

	template<typename WidgetControllerType>
	FORCEINLINE WidgetControllerType* GetWidgetController() { return Cast<WidgetControllerType>(WidgetController); }

	UFUNCTION(BlueprintCallable)
	void SetWidgetController(UWidgetController* Controller)
	{
		WidgetController = Controller;
		OnWidgetControllerSet();
	}
	
	UFUNCTION(BlueprintImplementableEvent)
	void OnWidgetControllerSet();

#pragma region UserWidget
	bool Initialize() override;

	void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;

	void NativeOnInitialized() override;
	void NativePreConstruct() override;
#pragma endregion UserWidget
};
