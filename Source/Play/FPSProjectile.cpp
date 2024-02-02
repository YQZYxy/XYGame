// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSProjectile.h"
#include "Kismet/GameplayStatics.h"
#include "PhysicsEngine/BodyInstance.h"
#include "TimerManager.h"

// Sets default values
AFPSProjectile::AFPSProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	if (!RootComponent)
	{
		RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("ProjectileSceneComponent"));
	}
	if (!CollisionComponent)
	{
		// 用球体进行简单的碰撞展示。
		CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
		// 设置球体的碰撞半径。
		CollisionComponent->InitSphereRadius(15.0f);
		// 将根组件设置为碰撞组件。
		RootComponent = CollisionComponent;
	}

	// 使用此组件驱动发射物的移动。
	if (!ProjectileMovementComponent)
	{
		
		ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
		ProjectileMovementComponent->SetUpdatedComponent(CollisionComponent);
		ProjectileMovementComponent->InitialSpeed = 1000.0f;
		ProjectileMovementComponent->MaxSpeed = 3000.0f;
		ProjectileMovementComponent->bRotationFollowsVelocity = true;
		ProjectileMovementComponent->bShouldBounce = true;
		ProjectileMovementComponent->Bounciness = 0.3f;
		ProjectileMovementComponent->ProjectileGravityScale = 0.0f;
	}
}

// Called when the game starts or when spawned
void AFPSProjectile::BeginPlay()
{
	Super::BeginPlay();

	CollisionComponent->OnComponentHit.AddDynamic(this, &AFPSProjectile::EventHit);  //添加碰撞动态委托(EventHit)
	PlayerController = Cast<APlayerController>(GetWorld()->GetFirstPlayerController());
}

// Called every frame
void AFPSProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// 初始化射击方向上发射物速度的函数。
void AFPSProjectile::FireInDirection(const FVector& ShootDirection)
{
	ProjectileMovementComponent->Velocity = ShootDirection * ProjectileMovementComponent->InitialSpeed;
}

void AFPSProjectile::EventHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hitler)
{
	//检测碰撞物体模拟物理是否打开
	if (OtherComponent->IsAnySimulatingPhysics())
	{
		//设置冲量
		OtherComponent->AddImpulse(ProjectileMovementComponent->Velocity*FVector(1.0f), NAME_None, false);  
	}
	//制造损伤
	//UGameplayStatics::ApplyDamage(Hitler.GetActor(), BaseDamage, PlayerController, this, NULL);
	UGameplayStatics::ApplyPointDamage(Hitler.GetActor(), BaseDamage, Hitler.Location, Hitler, NULL, this, NULL);

	TimerDelegate(1);		//启动定时器执行碰撞后事件  延迟时间
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), CollisionEndedFX, this->GetActorLocation(), this->GetActorRotation(), FVector(1.0), true, EPSCPoolMethod::AutoRelease, true);   //在碰撞处生成粒子特效;
}

//开启定时器
void AFPSProjectile::TimerDelegate(int delay_Time)
{
	GetWorld()->GetTimerManager().SetTimer(DestroyActorTimerHandle, this, &AFPSProjectile::DestroyActorEvent, delay_Time);
}

void AFPSProjectile::DestroyActorEvent()
{
	//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("子弹销毁"));
	Destroy();
	GetWorld()->GetTimerManager().ClearTimer(DestroyActorTimerHandle);  
}

