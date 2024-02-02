// Fill out your copyright notice in the Description page of Project Settings.


#include "BossActorDelegate.h"
#include "Components/BoxComponent.h"
// Sets default values
ABossActorDelegate::ABossActorDelegate()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	BoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComp"));
    BoxComp->SetBoxExtent(FVector(128, 128, 64));
    BoxComp->SetVisibility(true);

}

// Called when the game starts or when spawned
void ABossActorDelegate::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ABossActorDelegate::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void ABossActorDelegate::NotifyActorBeginOverlap(AActor* OtherActor)
{
	HandleBossDiedEvent();
}

void ABossActorDelegate::HandleBossDiedEvent()
{
	OnBossDied.ExecuteIfBound();
}


