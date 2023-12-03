// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "AbilitySystem/Attributes/YQZYAttributeSet.h"
#include "AbilitySystemComponent.h"

#include "XYGameAttributeSet.generated.h"

class UObject;
struct FFrame;

/**
 * UXYGameAttributeSet
 *
 *	Class that defines attributes specific to the top-down arena gameplay mode.
 */
UCLASS(BlueprintType)
class UXYGameAttributeSet : public UYQZYAttributeSet
{
	GENERATED_BODY()

public:
	UXYGameAttributeSet();

	ATTRIBUTE_ACCESSORS(ThisClass, BombsRemaining);
	ATTRIBUTE_ACCESSORS(ThisClass, BombCapacity);
	ATTRIBUTE_ACCESSORS(ThisClass, BombRange);
	ATTRIBUTE_ACCESSORS(ThisClass, MovementSpeed);

	//~UAttributeSet interface
	virtual void PreAttributeBaseChange(const FGameplayAttribute& Attribute, float& NewValue) const override;
	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	//~End of UAttributeSet interface

protected:

	UFUNCTION()
	void OnRep_BombsRemaining(const FGameplayAttributeData& OldValue);

	UFUNCTION()
	void OnRep_BombCapacity(const FGameplayAttributeData& OldValue);

	UFUNCTION()
	void OnRep_BombRange(const FGameplayAttributeData& OldValue);
	
	UFUNCTION()
	void OnRep_MovementSpeed(const FGameplayAttributeData& OldValue);

	void ClampAttribute(const FGameplayAttribute& Attribute, float& NewValue) const;

private:
	// The number of bombs remaining
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing=OnRep_BombsRemaining, Category="XYGame", Meta=(AllowPrivateAccess=true))
	FGameplayAttributeData BombsRemaining;

	// The maximum number of bombs that can be placed at once
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing=OnRep_BombCapacity, Category="XYGame", Meta=(AllowPrivateAccess=true))
	FGameplayAttributeData BombCapacity;

	// The range/radius of bomb blasts
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing=OnRep_BombRange, Category="XYGame", Meta=(AllowPrivateAccess=true))
	FGameplayAttributeData BombRange;

	// The range/radius of bomb blasts
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing=OnRep_MovementSpeed, Category="XYGame", Meta=(AllowPrivateAccess=true))
	FGameplayAttributeData MovementSpeed;
};
