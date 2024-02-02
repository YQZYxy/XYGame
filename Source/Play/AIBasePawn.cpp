// Fill out your copyright notice in the Description page of Project Settings.


#include "AIBasePawn.h"
#include "Chaos/Rotation.h"


// Sets default values
AAIBasePawn::AAIBasePawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	SkeletalMeshComp = CreateDefaultSubobject<USkeletalMeshComponent>("SkeletalMeshComp");
	CapsuleComp = CreateDefaultSubobject<UCapsuleComponent>("CapsuleComp");
	SceneComp = CreateDefaultSubobject<USceneComponent>("SceneComp");

	RootComponent = SceneComp;
	CapsuleComp->SetupAttachment(SceneComp);
	SkeletalMeshComp->SetupAttachment(SceneComp);
}

// Called when the game starts or when spawned
void AAIBasePawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAIBasePawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AAIBasePawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

