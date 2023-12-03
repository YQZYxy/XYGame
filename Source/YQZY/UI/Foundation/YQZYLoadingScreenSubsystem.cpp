// Copyright Epic Games, Inc. All Rights Reserved.

#include "UI/Foundation/YQZYLoadingScreenSubsystem.h"

#include "Blueprint/UserWidget.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(YQZYLoadingScreenSubsystem)

class UUserWidget;

//////////////////////////////////////////////////////////////////////
// UYQZYLoadingScreenSubsystem

UYQZYLoadingScreenSubsystem::UYQZYLoadingScreenSubsystem()
{
}

void UYQZYLoadingScreenSubsystem::SetLoadingScreenContentWidget(TSubclassOf<UUserWidget> NewWidgetClass)
{
	if (LoadingScreenWidgetClass != NewWidgetClass)
	{
		LoadingScreenWidgetClass = NewWidgetClass;

		OnLoadingScreenWidgetChanged.Broadcast(LoadingScreenWidgetClass);
	}
}

TSubclassOf<UUserWidget> UYQZYLoadingScreenSubsystem::GetLoadingScreenContentWidget() const
{
	return LoadingScreenWidgetClass;
}

