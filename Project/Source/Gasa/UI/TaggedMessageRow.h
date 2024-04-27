#pragma once

#include "GameplayTagContainer.h"
#include "GasaCommon.h"
#include "Engine/DataTable.h"
#include "Templates/SubclassOf.h"

#include "TaggedMessageRow.generated.h"

USTRUCT(BlueprintType)
struct FTaggedMessageRow : public FTableRowBase
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FGameplayTag Tag;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FText Message;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<UGasaUserWidget> MessageTemplate;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UTexture2D* Image;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FTaggedMessageRowSig, FTaggedMessageRow, Message);
