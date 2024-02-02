// Fill out your copyright notice in the Description page of Project Settings.


#include "FirstLevelDelegate.h"
#include "Components/BoxComponent.h"
// Sets default values
AFirstLevelDelegate::AFirstLevelDelegate()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComp"));
	BoxComp->SetBoxExtent(FVector(128, 128, 64));
	BoxComp->SetVisibility(true);
}

// Called when the game starts or when spawned
void AFirstLevelDelegate::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFirstLevelDelegate::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AFirstLevelDelegate::NotifyActorBeginOverlap(AActor* otherActor)
{
	FirstEvent();
}

void AFirstLevelDelegate::FirstEvent()
{
	OnInteractive.ExecuteIfBound();
}
