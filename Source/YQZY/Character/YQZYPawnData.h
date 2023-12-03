// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Engine/DataAsset.h"

#include "YQZYPawnData.generated.h"

class APawn;
class UYQZYAbilitySet;
class UYQZYAbilityTagRelationshipMapping;
class UYQZYCameraMode;
class UYQZYInputConfig;
class UObject;


/**
 * UYQZYPawnData
 *
 *	Non-mutable data asset that contains properties used to define a pawn.
 */
UCLASS(BlueprintType, Const, Meta = (DisplayName = "YQZY Pawn Data", ShortTooltip = "Data asset used to define a Pawn."))
class YQZY_API UYQZYPawnData : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:

	UYQZYPawnData(const FObjectInitializer& ObjectInitializer);

public:

	// Class to instantiate for this pawn (should usually derive from AYQZYPawn or AYQZYCharacter).
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "YQZY|Pawn")
	TSubclassOf<APawn> PawnClass;

	// Ability sets to grant to this pawn's ability system.
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "YQZY|Abilities")
	TArray<TObjectPtr<UYQZYAbilitySet>> AbilitySets;

	// What mapping of ability tags to use for actions taking by this pawn
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "YQZY|Abilities")
	TObjectPtr<UYQZYAbilityTagRelationshipMapping> TagRelationshipMapping;

	// Input configuration used by player controlled pawns to create input mappings and bind input actions.
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "YQZY|Input")
	TObjectPtr<UYQZYInputConfig> InputConfig;

	// Default camera mode used by player controlled pawns.
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "YQZY|Camera")
	TSubclassOf<UYQZYCameraMode> DefaultCameraMode;
};
