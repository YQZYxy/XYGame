// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/YQZYCharacter.h"
#include "RoleModule.generated.h"

/**
 * 
 */
UCLASS()
class YQZY_API ARoleModule : public AYQZYCharacter
{
	GENERATED_BODY()
public:
	ARoleModule();

	//virtual void BeginPlay() override;
	void BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepHitResult);


private:
};
