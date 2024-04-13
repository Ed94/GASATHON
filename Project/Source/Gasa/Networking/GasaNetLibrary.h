#pragma once


namespace Gasa
{
	constexpr float NetCullDist_Default   = 225000000.0f;
	constexpr float NetCullDist_Immediate = 250.0f   * 250.0f;
	constexpr float NetCullDist_VerClose  = 1000.0f  * 1000.0f;
	constexpr float NetCullDist_Close     = 3500.0f  * 3500.0f;
	constexpr float NetCullDist_Medium    = 5000.0f  * 5000.0f;
	constexpr float NetCullDist_Distant   = 7000.0f  * 7000.0f;
	constexpr float NetCullDist_Far       = 8500.0f  * 8500.0f;
	constexpr float NetCullDist_VeryFar   = 10000.0f * 10000.0f;
	constexpr float NetCullDist_VisualMax = 15000.0f * 15000.0f;	
}
