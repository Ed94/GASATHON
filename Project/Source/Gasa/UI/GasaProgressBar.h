#pragma once

#include "Components/ProgressBar.h"

#include "GasaProgressBar.generated.h"

UCLASS()
class GASA_API UGasaProgressBar : public UProgressBar
{
	GENERATED_BODY()
public:

#pragma region Object
	void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;

	void Serialize(FArchive& Ar) override;
	void Serialize(FStructuredArchive::FRecord Record) override;
#pragma endregion Object
};
