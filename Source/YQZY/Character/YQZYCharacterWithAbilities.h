// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Character/YQZYCharacter.h"

#include "YQZYCharacterWithAbilities.generated.h"

class UAbilitySystemComponent;
class UYQZYAbilitySystemComponent;
class UObject;

// AYQZYCharacter typically gets the ability system component from the possessing player state
// This represents a character with a self-contained ability system component.
UCLASS(Blueprintable)
class YQZY_API AYQZYCharacterWithAbilities : public AYQZYCharacter
{
	GENERATED_BODY()

public:
	AYQZYCharacterWithAbilities(const FObjectInitializer& ObjectInitializer);

	virtual void PostInitializeComponents() override;

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

private:

	// The ability system component sub-object used by player characters.
	UPROPERTY(VisibleAnywhere, Category = "YQZY|PlayerState")
	TObjectPtr<UYQZYAbilitySystemComponent> AbilitySystemComponent;
};
