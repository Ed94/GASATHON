#include "GasaPlayerController.h"
#include "GasaPlayerState.h"

inline
AGasaPlayerState* AGasaPlayerController::GetPlayerState()
{
	return Cast<AGasaPlayerState>( PlayerState );
}
