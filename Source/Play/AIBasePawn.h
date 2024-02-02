// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Components/CapsuleComponent.h"
#include "Components/ArrowComponent.h"
#include "AIBasePawn.generated.h"

UCLASS()
class PLAY_API AAIBasePawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AAIBasePawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
		USkeletalMeshComponent* SkeletalMeshComp;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UCapsuleComponent* CapsuleComp;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		USceneComponent* SceneComp;

	//UFUNCTION(BlueprintImplementableEvent)
};
