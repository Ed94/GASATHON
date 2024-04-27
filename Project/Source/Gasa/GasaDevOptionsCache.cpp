// Generated by GasaGen/GasaGen_DevOptionsCache.cpp
#include "GasaDevOptionsCache.h"

#include "GasaDevOptions.h"
#include "Actors/CameraMount.h"
#include "UI/HUDHostWidget.h"
#include "UI/HostWidgetController.h"
using namespace Gasa;

void FGasaDevOptionsCache::CachedDevOptions()
{
	UGasaDevOptions* DevOpts = GetMutDevOptions();

	TaggedMessageTable = DevOpts->TaggedMessageTable.LoadSynchronous();
	ensureMsgf( TaggedMessageTable != nullptr, TEXT( "TaggedMessageTable is null, DO NOT RUN PIE or else you may get a crash if not handled in BP or C++" ) );

	Template_PlayerCamera = DevOpts->Template_PlayerCamera.LoadSynchronous();
	ensureMsgf(
	    Template_PlayerCamera != nullptr, TEXT( "Template_PlayerCamera is null, DO NOT RUN PIE or else you may get a crash if not handled in BP or C++" )
	);

	Template_HUD_HostUI = DevOpts->Template_HUD_HostUI.LoadSynchronous();
	ensureMsgf( Template_HUD_HostUI != nullptr, TEXT( "Template_HUD_HostUI is null, DO NOT RUN PIE or else you may get a crash if not handled in BP or C++" ) );

	Template_HostWidgetController = DevOpts->Template_HostWidgetController.LoadSynchronous();
	ensureMsgf(
	    Template_HostWidgetController != nullptr,
	    TEXT( "Template_HostWidgetController is null, DO NOT RUN PIE or else you may get a crash if not handled in BP or C++" )
	);

	Tag_GlobalPPV = DevOpts->Tag_GlobalPPV;
}
