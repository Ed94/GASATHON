#include "GasaProgressBar.h"

#include "GasaCommon.h"

using namespace Gasa;

#pragma region Object
void UGasaProgressBar::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);
}

void UGasaProgressBar::Serialize(FArchive& Ar)
{
	Super::Serialize(Ar);
}

void UGasaProgressBar::Serialize(FStructuredArchive::FRecord Record)
{
	Super::Serialize(Record);
}
#pragma endregion Object
