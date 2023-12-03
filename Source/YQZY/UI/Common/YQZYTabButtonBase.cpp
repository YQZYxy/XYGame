// Copyright Epic Games, Inc. All Rights Reserved.

#include "YQZYTabButtonBase.h"

#include "CommonLazyImage.h"
#include "UI/Common/YQZYTabListWidgetBase.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(YQZYTabButtonBase)

class UObject;
struct FSlateBrush;

void UYQZYTabButtonBase::SetIconFromLazyObject(TSoftObjectPtr<UObject> LazyObject)
{
	if (LazyImage_Icon)
	{
		LazyImage_Icon->SetBrushFromLazyDisplayAsset(LazyObject);
	}
}

void UYQZYTabButtonBase::SetIconBrush(const FSlateBrush& Brush)
{
	if (LazyImage_Icon)
	{
		LazyImage_Icon->SetBrush(Brush);
	}
}

void UYQZYTabButtonBase::SetTabLabelInfo_Implementation(const FYQZYTabDescriptor& TabLabelInfo)
{
	SetButtonText(TabLabelInfo.TabText);
	SetIconBrush(TabLabelInfo.IconBrush);
}

