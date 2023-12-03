// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"

#include "YQZYVerbMessageHelpers.generated.h"

struct FGameplayCueParameters;
struct FYQZYVerbMessage;

class APlayerController;
class APlayerState;
class UObject;
struct FFrame;


UCLASS()
class YQZY_API UYQZYVerbMessageHelpers : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "YQZY")
	static APlayerState* GetPlayerStateFromObject(UObject* Object);

	UFUNCTION(BlueprintCallable, Category = "YQZY")
	static APlayerController* GetPlayerControllerFromObject(UObject* Object);

	UFUNCTION(BlueprintCallable, Category = "YQZY")
	static FGameplayCueParameters VerbMessageToCueParameters(const FYQZYVerbMessage& Message);

	UFUNCTION(BlueprintCallable, Category = "YQZY")
	static FYQZYVerbMessage CueParametersToVerbMessage(const FGameplayCueParameters& Params);
};
