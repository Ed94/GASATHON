#pragma once

#include "GasaCommon.h"

template<typename KeyType, typename ValueType>
inline
void RemoveKeys(TMap<KeyType, ValueType> Map, TArray<KeyType> Keys)
{
	for (KeyType& Key : Keys )
	{
		Map.Remove(Key);
	}
}
	