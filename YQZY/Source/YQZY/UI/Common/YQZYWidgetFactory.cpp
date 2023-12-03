// Copyright Epic Games, Inc. All Rights Reserved.

#include "YQZYWidgetFactory.h"
#include "Templates/SubclassOf.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(YQZYWidgetFactory)

class UUserWidget;

TSubclassOf<UUserWidget> UYQZYWidgetFactory::FindWidgetClassForData_Implementation(const UObject* Data) const
{
	return TSubclassOf<UUserWidget>();
}
