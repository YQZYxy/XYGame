// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BossActorDelegate.generated.h"

DECLARE_DELEGATE(FOnBossDiedDelegate);  //Declare Delegate
UCLASS()
class PLAY_API ABossActorDelegate : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABossActorDelegate();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


	UPROPERTY(EditInstanceOnly, BlueprintReadWrite)
		class UBoxComponent* BoxComp;

	UFUNCTION()
		void HandleBossDiedEvent();

	virtual void NotifyActorBeginOverlap(AActor* OtherActor);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	FOnBossDiedDelegate OnBossDied;

};
