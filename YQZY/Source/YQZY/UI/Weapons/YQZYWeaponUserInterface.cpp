// Copyright Epic Games, Inc. All Rights Reserved.

#include "YQZYWeaponUserInterface.h"

#include "Equipment/YQZYEquipmentManagerComponent.h"
#include "GameFramework/Pawn.h"
#include "Weapons/YQZYWeaponInstance.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(YQZYWeaponUserInterface)

struct FGeometry;

UYQZYWeaponUserInterface::UYQZYWeaponUserInterface(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

void UYQZYWeaponUserInterface::NativeConstruct()
{
	Super::NativeConstruct();
}

void UYQZYWeaponUserInterface::NativeDestruct()
{
	Super::NativeDestruct();
}

void UYQZYWeaponUserInterface::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if (APawn* Pawn = GetOwningPlayerPawn())
	{
		if (UYQZYEquipmentManagerComponent* EquipmentManager = Pawn->FindComponentByClass<UYQZYEquipmentManagerComponent>())
		{
			if (UYQZYWeaponInstance* NewInstance = EquipmentManager->GetFirstInstanceOfType<UYQZYWeaponInstance>())
			{
				if (NewInstance != CurrentInstance && NewInstance->GetInstigator() != nullptr)
				{
					UYQZYWeaponInstance* OldWeapon = CurrentInstance;
					CurrentInstance = NewInstance;
					RebuildWidgetFromWeapon();
					OnWeaponChanged(OldWeapon, CurrentInstance);
				}
			}
		}
	}
}

void UYQZYWeaponUserInterface::RebuildWidgetFromWeapon()
{
	
}

