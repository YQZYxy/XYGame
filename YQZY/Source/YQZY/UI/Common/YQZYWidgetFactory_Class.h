// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "YQZYWidgetFactory.h"
#include "Templates/SubclassOf.h"
#include "UObject/SoftObjectPtr.h"

#include "YQZYWidgetFactory_Class.generated.h"

class UObject;
class UUserWidget;

UCLASS()
class YQZY_API UYQZYWidgetFactory_Class : public UYQZYWidgetFactory
{
	GENERATED_BODY()

public:
	UYQZYWidgetFactory_Class() { }

	virtual TSubclassOf<UUserWidget> FindWidgetClassForData_Implementation(const UObject* Data) const override;
	
protected:
	UPROPERTY(EditAnywhere, Category = ListEntries, meta = (AllowAbstract))
	TMap<TSoftClassPtr<UObject>, TSubclassOf<UUserWidget>> EntryWidgetForClass;
};
