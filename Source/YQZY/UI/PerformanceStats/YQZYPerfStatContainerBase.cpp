// Copyright Epic Games, Inc. All Rights Reserved.

#include "YQZYPerfStatContainerBase.h"

#include "Blueprint/WidgetTree.h"
#include "YQZYPerfStatWidgetBase.h"
#include "Settings/YQZYSettingsLocal.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(YQZYPerfStatContainerBase)

//////////////////////////////////////////////////////////////////////
// UYQZYPerfStatsContainerBase

UYQZYPerfStatContainerBase::UYQZYPerfStatContainerBase(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

void UYQZYPerfStatContainerBase::NativeConstruct()
{
	Super::NativeConstruct();
	UpdateVisibilityOfChildren();

	UYQZYSettingsLocal::Get()->OnPerfStatDisplayStateChanged().AddUObject(this, &ThisClass::UpdateVisibilityOfChildren);
}

void UYQZYPerfStatContainerBase::NativeDestruct()
{
	UYQZYSettingsLocal::Get()->OnPerfStatDisplayStateChanged().RemoveAll(this);

	Super::NativeDestruct();
}

void UYQZYPerfStatContainerBase::UpdateVisibilityOfChildren()
{
	UYQZYSettingsLocal* UserSettings = UYQZYSettingsLocal::Get();

	const bool bShowTextWidgets = (StatDisplayModeFilter == EYQZYStatDisplayMode::TextOnly) || (StatDisplayModeFilter == EYQZYStatDisplayMode::TextAndGraph);
	const bool bShowGraphWidgets = (StatDisplayModeFilter == EYQZYStatDisplayMode::GraphOnly) || (StatDisplayModeFilter == EYQZYStatDisplayMode::TextAndGraph);
	
	check(WidgetTree);
	WidgetTree->ForEachWidget([&](UWidget* Widget)
	{
		if (UYQZYPerfStatWidgetBase* TypedWidget = Cast<UYQZYPerfStatWidgetBase>(Widget))
		{
			const EYQZYStatDisplayMode SettingMode = UserSettings->GetPerfStatDisplayState(TypedWidget->GetStatToDisplay());

			bool bShowWidget = false;
			switch (SettingMode)
			{
			case EYQZYStatDisplayMode::Hidden:
				bShowWidget = false;
				break;
			case EYQZYStatDisplayMode::TextOnly:
				bShowWidget = bShowTextWidgets;
				break;
			case EYQZYStatDisplayMode::GraphOnly:
				bShowWidget = bShowGraphWidgets;
				break;
			case EYQZYStatDisplayMode::TextAndGraph:
				bShowWidget = bShowTextWidgets || bShowGraphWidgets;
				break;
			}

			TypedWidget->SetVisibility(bShowWidget ? ESlateVisibility::HitTestInvisible : ESlateVisibility::Collapsed);
		}
	});
}

