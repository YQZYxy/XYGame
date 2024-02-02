// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FirstLevelDelegate.generated.h"

DECLARE_DELEGATE(OpenInteractive);
UCLASS()
class PLAY_API AFirstLevelDelegate : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFirstLevelDelegate();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:

	OpenInteractive OnInteractive;

	virtual void NotifyActorBeginOverlap(AActor* OtherActor); 

public:
	UPROPERTY(EditInstanceOnly, BlueprintReadwrite)
		class UBoxComponent* BoxComp;

	UFUNCTION()
		void FirstEvent();
	
};
