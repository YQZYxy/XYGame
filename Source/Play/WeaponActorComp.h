// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "FPSProjectShell.h"
#include "FPSProjectile.h"
#include "GameFramework/Actor.h"
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "WeaponActorComp.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PLAY_API UWeaponActorComp : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UWeaponActorComp();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	//射击速度
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float FireOfSpeed;
	//武器当前子弹数
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		int32 AmmunitionAmount_Now;
	//武器骨骼网络体
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		USkeletalMeshComponent* WeaponMesh;
	//发射物类
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSubclassOf<class AFPSProjectile> Projectile;
	//弹壳类
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSubclassOf<class AFPSProjectShell> ProjectShell;
	//枪口骨骼插槽
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FName MuzzleFlashSocket;
	//弹壳骨骼插槽
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FName BulletShellSocket;
	//枪口粒子组件
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UParticleSystemComponent* MuzzleParticleComp;
	//粒子资产
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UParticleSystem* MuzzleFX;
	//影响开火状态
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool bShouldFire;
	//子弹是否耗尽耗尽
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool bAmmunitionEnd;
	//全自动开火定时器句柄
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FTimerHandle InOutHandle;
	//子弹命中伤害量
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float Damage;

private:
	
	
	//开火按键状态
	UPROPERTY()
	bool bFirePressed;
	//粒子组件是否可以生成
	UPROPERTY()
	bool bParticleIsValid;

public:
	//鼠标左键按下状态
	UFUNCTION(BlueprintCallable)
		void FireButtonPressed();
	UFUNCTION(BlueprintCallable)
		void FireButtonReleased();
	//定时器,间接递归Fire()函数和AutoFire(),左键按下循环调用形成自动开火
	UFUNCTION(BlueprintCallable)
		void TimerDelegate();
	//武器开火时执行的各事件状态
	UFUNCTION(BlueprintCallable)
		void Fire();
	//自动开火武器函数调用
	UFUNCTION(BlueprintCallable)
		void AutoFire();
	//换弹
	UFUNCTION(BlueprintCallable)
		void Reload(int ReloadAmmo);
	//使定时器无效  达到停止开火
	UFUNCTION(BlueprintCallable)
		void StopFire();
	//设置子弹命中伤害
	UFUNCTION(BlueprintCallable)
		void SetAmmunitionDamage(int WeaponDamage);

};
