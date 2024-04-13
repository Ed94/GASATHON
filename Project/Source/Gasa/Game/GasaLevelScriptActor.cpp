#include "GasaLevelScriptActor.h"

#include "GasaDevOptions.h"
#include "Kismet/GameplayStatics.h"

void AGasaLevelScriptActor::BeginPlay()
{
	Super::BeginPlay();

	using namespace Gasa;

	TArray<AActor*> TaggedActors;
	UGameplayStatics::GetAllActorsWithTag(GetWorld(), GetDevOptions()->Tag_GlobalPPV, TaggedActors);
	for (AActor* Actor : TaggedActors)
	{
		GlobalPPV = Cast<APostProcessVolume>(Actor);

		APostProcessVolume* PPV     = GetLevelActor(this)->GlobalPPV;
		UMaterialInstance*  Blendable = Cast<UMaterialInstance>(PPV->Settings.WeightedBlendables.Array[0].Object);
		UMaterialInstanceDynamic* MID = UMaterialInstanceDynamic::Create(Blendable, this);
		PPV->Settings.WeightedBlendables.Array[0].Object = MID;
		break;
	}
}
