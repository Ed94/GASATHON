#pragma once
#include "IDetailCustomization.h"


class FGlobeProgressBarDetails : public IDetailCustomization
{
public:
	static TSharedRef<IDetailCustomization> MakeInstance() { return MakeShareable(new FGlobeProgressBarDetails); }

	void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;

	static bool CheckAsset(FAssetData const& Asset);
	TSharedPtr<FAssetThumbnail> Thumbnail;
};
