#pragma once

#include "GasaCommon.h"

template<typename RowType>
inline
RowType* GetDataTableRowByTag(UDataTable* DT, FGameplayTag& Tag)
{
	RowType* Row = DT->FindRow<RowType>(Tag.GetTagName(), TEXT(""));
	return Row;
}

template<typename KeyType, typename ValueType>
inline
void RemoveKeys(TMap<KeyType, ValueType> Map, TArray<KeyType> Keys)
{
	for (KeyType& Key : Keys )
	{
		Map.Remove(Key);
	}
}
	