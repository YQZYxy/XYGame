// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FPSProjectile.generated.h"

UCLASS()
class PLAY_API AFPSProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFPSProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	// 球体碰撞组件。
	UPROPERTY(VisibleDefaultsOnly, Category = Projectile)
		USphereComponent* CollisionComponent;

	// 发射物移动组件。
	UPROPERTY(VisibleAnywhere, Category = Movement)
		UProjectileMovementComponent* ProjectileMovementComponent;

	//粒子资产
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UParticleSystem* CollisionEndedFX;
	//销毁Actor定时器句柄
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FTimerHandle DestroyActorTimerHandle;

	//制造伤害量
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float BaseDamage;

	//获取玩家控制器
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		APlayerController* PlayerController;

public:
	// 初始化射击方向上发射物速度的函数。
	UFUNCTION(BlueprintCallable)
	void FireInDirection(const FVector& ShootDirection);

	UFUNCTION(BlueprintCallable)
		void  EventHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hitler);
	//控制碰撞后延迟时间销毁Actor
	UFUNCTION(BlueprintCallable)
		void TimerDelegate(int delay_Time);
	//销毁Actor
	UFUNCTION(BlueprintCallable)
		void DestroyActorEvent();
};

