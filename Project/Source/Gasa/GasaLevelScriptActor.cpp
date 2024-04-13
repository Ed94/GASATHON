#include "GasaLevelScriptActor.h"

#include "GasaDevOptions.h"
#include "GasaGameplayTags.h"
#include "Kismet/GameplayStatics.h"

#include "GasaLibrary.h"

void AGasaLevelScriptActor::BeginPlay()
{
	Super::BeginPlay();

	TArray<AActor*> TaggedActors;
	UGameplayStatics::GetAllActorsWithTag(GetWorld(), Gasa::GetDevOptions()->Tag_GlobalPPV,TaggedActors);
	for (AActor* Actor : TaggedActors)
	{
		GlobalPPV = Cast<APostProcessVolume>(Actor);

		APostProcessVolume* PPV     = Gasa::GetLevelActor(this)->GlobalPPV;
		UMaterialInstance*  Blendable = Cast<UMaterialInstance>(PPV->Settings.WeightedBlendables.Array[0].Object);
		UMaterialInstanceDynamic* MID = UMaterialInstanceDynamic::Create(Blendable, this);
		PPV->Settings.WeightedBlendables.Array[0].Object = MID;
		break;
	}
}
