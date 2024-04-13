#include "GasaDevOptions.h"

#include "GasaDevOptionsCache.h"

namespace Gasa
{
	global FName Tag_GlobalPPV;
}

void FGasaDevOptionsCache::CachedDevOptions()
{
	using namespace Gasa;

	UGasaDevOptions const* DevOs = GetDevOptions();
	Tag_GlobalPPV = DevOs->Tag_GlobalPPV;
}

 