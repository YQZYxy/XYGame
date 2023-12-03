// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "YQZYTabListWidgetBase.h"
#include "UI/Foundation/YQZYButtonBase.h"

#include "YQZYTabButtonBase.generated.h"

class UCommonLazyImage;
class UObject;
struct FFrame;
struct FSlateBrush;

UCLASS(Abstract, Blueprintable, meta = (DisableNativeTick))
class YQZY_API UYQZYTabButtonBase : public UYQZYButtonBase, public IYQZYTabButtonInterface
{
	GENERATED_BODY()

public:

	void SetIconFromLazyObject(TSoftObjectPtr<UObject> LazyObject);
	void SetIconBrush(const FSlateBrush& Brush);

protected:

	UFUNCTION()
	virtual void SetTabLabelInfo_Implementation(const FYQZYTabDescriptor& TabLabelInfo) override;

private:

	UPROPERTY(meta = (BindWidgetOptional))
	TObjectPtr<UCommonLazyImage> LazyImage_Icon;
};
