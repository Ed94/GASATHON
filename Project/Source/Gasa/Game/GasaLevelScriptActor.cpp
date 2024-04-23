#include "GasaLevelScriptActor.h"

#include "GasaDevOptions.h"
#include "GasaGameInstance.h"
#include "Engine/PostProcessVolume.h"
#include "Kismet/GameplayStatics.h"
#include "Materials/MaterialInstance.h"
#include "Materials/MaterialInstanceDynamic.h"
using namespace Gasa;

#pragma region Game Framework
AGasaLevelScriptActor::AGasaLevelScriptActor()
{
	// Replication
	
	bReplicates            = true;
	bNetLoadOnClient       = true;
	NetDormancy            = DORM_Awake;
	NetCullDistanceSquared = NetCullDist_Default;
	NetUpdateFrequency     = 10.0f;
	MinNetUpdateFrequency  = 1.0f;
	NetPriority            = 1.0f;
}

void AGasaLevelScriptActor::OnGameFrameworkInitialized()
{
	NetLog("Received game framework initialization.");
	BP_OnGameFrameworkInitialized();
}
#pragma endregion Game Framework

#pragma region Actor
void AGasaLevelScriptActor::BeginPlay()
{
	Super::BeginPlay();
	NetLog("BeginPlay");

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
	
	UGasaGameInstance* GI = GetGameInstance<UGasaGameInstance>();
	if(GI)
		GI->Event_OnGameFrameworkInitialized.AddUniqueDynamic(this, & ThisClass::OnGameFrameworkInitialized);

	if (!bOverrideGameplayFrameworkReady)
		GI->NotifyGameFrameworkClassReady(EGameFrameworkClassFlag::Levels);
}
#pragma endregion Actor
