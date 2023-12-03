// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CommonUserWidget.h"

#include "YQZYWeaponUserInterface.generated.h"

class UYQZYWeaponInstance;
class UObject;
struct FGeometry;

UCLASS()
class UYQZYWeaponUserInterface : public UCommonUserWidget
{
	GENERATED_BODY()

public:
	UYQZYWeaponUserInterface(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	UFUNCTION(BlueprintImplementableEvent)
	void OnWeaponChanged(UYQZYWeaponInstance* OldWeapon, UYQZYWeaponInstance* NewWeapon);

private:
	void RebuildWidgetFromWeapon();

private:
	UPROPERTY(Transient)
	TObjectPtr<UYQZYWeaponInstance> CurrentInstance;
};
