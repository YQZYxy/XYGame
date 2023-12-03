// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "GameplayEffectExecutionCalculation.h"

#include "YQZYHealExecution.generated.h"

class UObject;


/**
 * UYQZYHealExecution
 *
 *	Execution used by gameplay effects to apply healing to the health attributes.
 */
UCLASS()
class UYQZYHealExecution : public UGameplayEffectExecutionCalculation
{
	GENERATED_BODY()

public:

	UYQZYHealExecution();

protected:

	virtual void Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const override;
};
