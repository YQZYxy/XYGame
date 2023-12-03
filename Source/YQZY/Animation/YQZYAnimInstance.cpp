// Copyright Epic Games, Inc. All Rights Reserved.

#include "YQZYAnimInstance.h"
#include "AbilitySystemGlobals.h"
#include "Character/YQZYCharacter.h"
#include "Character/YQZYCharacterMovementComponent.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(YQZYAnimInstance)


UYQZYAnimInstance::UYQZYAnimInstance(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

void UYQZYAnimInstance::InitializeWithAbilitySystem(UAbilitySystemComponent* ASC)
{
	check(ASC);

	GameplayTagPropertyMap.Initialize(this, ASC);
}

#if WITH_EDITOR
EDataValidationResult UYQZYAnimInstance::IsDataValid(TArray<FText>& ValidationErrors)
{
	Super::IsDataValid(ValidationErrors);

	GameplayTagPropertyMap.IsDataValid(this, ValidationErrors);

	return ((ValidationErrors.Num() > 0) ? EDataValidationResult::Invalid : EDataValidationResult::Valid);
}
#endif // WITH_EDITOR

void UYQZYAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	if (AActor* OwningActor = GetOwningActor())
	{
		if (UAbilitySystemComponent* ASC = UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(OwningActor))
		{
			InitializeWithAbilitySystem(ASC);
		}
	}
}

void UYQZYAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	const AYQZYCharacter* Character = Cast<AYQZYCharacter>(GetOwningActor());
	if (!Character)
	{
		return;
	}

	UYQZYCharacterMovementComponent* CharMoveComp = CastChecked<UYQZYCharacterMovementComponent>(Character->GetCharacterMovement());
	const FYQZYCharacterGroundInfo& GroundInfo = CharMoveComp->GetGroundInfo();
	GroundDistance = GroundInfo.GroundDistance;
}

