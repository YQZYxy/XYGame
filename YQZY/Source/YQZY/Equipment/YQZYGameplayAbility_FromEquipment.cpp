// Copyright Epic Games, Inc. All Rights Reserved.

#include "YQZYGameplayAbility_FromEquipment.h"
#include "YQZYEquipmentInstance.h"
#include "Inventory/YQZYInventoryItemInstance.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(YQZYGameplayAbility_FromEquipment)

UYQZYGameplayAbility_FromEquipment::UYQZYGameplayAbility_FromEquipment(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

UYQZYEquipmentInstance* UYQZYGameplayAbility_FromEquipment::GetAssociatedEquipment() const
{
	if (FGameplayAbilitySpec* Spec = UGameplayAbility::GetCurrentAbilitySpec())
	{
		return Cast<UYQZYEquipmentInstance>(Spec->SourceObject.Get());
	}

	return nullptr;
}

UYQZYInventoryItemInstance* UYQZYGameplayAbility_FromEquipment::GetAssociatedItem() const
{
	if (UYQZYEquipmentInstance* Equipment = GetAssociatedEquipment())
	{
		return Cast<UYQZYInventoryItemInstance>(Equipment->GetInstigator());
	}
	return nullptr;
}


#if WITH_EDITOR
EDataValidationResult UYQZYGameplayAbility_FromEquipment::IsDataValid(TArray<FText>& ValidationErrors)
{
	EDataValidationResult Result = Super::IsDataValid(ValidationErrors);

	if (InstancingPolicy == EGameplayAbilityInstancingPolicy::NonInstanced)
	{
		ValidationErrors.Add(NSLOCTEXT("YQZY", "EquipmentAbilityMustBeInstanced", "Equipment ability must be instanced"));
		Result = EDataValidationResult::Invalid;
	}

	return Result;
}

#endif
