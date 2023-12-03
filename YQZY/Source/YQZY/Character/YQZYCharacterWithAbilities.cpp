// Copyright Epic Games, Inc. All Rights Reserved.

#include "YQZYCharacterWithAbilities.h"

#include "AbilitySystem/Attributes/YQZYCombatSet.h"
#include "AbilitySystem/Attributes/YQZYHealthSet.h"
#include "AbilitySystem/YQZYAbilitySystemComponent.h"
#include "Async/TaskGraphInterfaces.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(YQZYCharacterWithAbilities)

AYQZYCharacterWithAbilities::AYQZYCharacterWithAbilities(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	AbilitySystemComponent = ObjectInitializer.CreateDefaultSubobject<UYQZYAbilitySystemComponent>(this, TEXT("AbilitySystemComponent"));
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);

	CreateDefaultSubobject<UYQZYHealthSet>(TEXT("HealthSet"));
	CreateDefaultSubobject<UYQZYCombatSet>(TEXT("CombatSet"));

	// AbilitySystemComponent needs to be updated at a high frequency.
	NetUpdateFrequency = 100.0f;
}

void AYQZYCharacterWithAbilities::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	check(AbilitySystemComponent);
	AbilitySystemComponent->InitAbilityActorInfo(this, this);
}

UAbilitySystemComponent* AYQZYCharacterWithAbilities::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

