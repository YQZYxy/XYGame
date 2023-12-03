// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "GameplayEffectExecutionCalculation.h"

#include "YQZYDamageExecution.generated.h"

class UObject;


/**
 * UYQZYDamageExecution
 *
 *	Execution used by gameplay effects to apply damage to the health attributes.
 */
UCLASS()
class UYQZYDamageExecution : public UGameplayEffectExecutionCalculation
{
	GENERATED_BODY()

public:

	UYQZYDamageExecution();

protected:

	virtual void Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const override;
};
