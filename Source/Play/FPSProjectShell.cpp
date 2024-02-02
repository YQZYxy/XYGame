// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSProjectShell.h"
#include "TimerManager.h"

// Sets default values
AFPSProjectShell::AFPSProjectShell()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	if (!RootComponent)
	{
		RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("ProjectileSceneComponent"));;
	}
	if (!CollisionComponent)
	{
		// 用球体进行简单的碰撞展示。
		CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
		// 设置球体的碰撞半径。
		CollisionComponent->InitSphereRadius(2.0f);
		// 将根组件设置为碰撞组件。

		RootComponent = CollisionComponent;

	
	}

	if (!ProjectileMovementComponent)
	{
		// 使用此组件驱动发射物的移动。
		ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
		ProjectileMovementComponent->SetUpdatedComponent(CollisionComponent);
		ProjectileMovementComponent->InitialSpeed = 200.0f;
		ProjectileMovementComponent->MaxSpeed = 200.0f;
		ProjectileMovementComponent->bRotationFollowsVelocity = true;
		ProjectileMovementComponent->bShouldBounce = true;
		ProjectileMovementComponent->Bounciness = 0.6f;
		ProjectileMovementComponent->ProjectileGravityScale = 1.0f;
	}
}

// Called when the game starts or when spawned
void AFPSProjectShell::BeginPlay()
{
	Super::BeginPlay();
	//

	FTimerHandle InOutHandle;
	GetWorld()->GetTimerManager().SetTimer(InOutHandle, this, &AFPSProjectShell::DestroyACtor, 10.0f, false);
}

// Called every frame
void AFPSProjectShell::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// 初始化射击方向上发射物速度的函数。
void AFPSProjectShell::FireInDirection(const FVector& ShootDirection)
{
	ProjectileMovementComponent->Velocity = ShootDirection * ProjectileMovementComponent->InitialSpeed;
}

void AFPSProjectShell::DestroyACtor()
{
	Destroy();
	//GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Blue, TEXT("销毁弹壳"));
}