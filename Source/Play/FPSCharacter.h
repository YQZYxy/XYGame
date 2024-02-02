// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "WeaponClass.h"
#include "ItemStruct.h"
#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "FPSCharacter.generated.h"

DECLARE_MULTICAST_DELEGATE(FClickEscDelegate);

#define PickupChannel ECC_GameTraceChannel3
#define InteractChannel ECC_GameTraceChannel1

//角色类 常规运动状态  以包含射线检测,挂载Component组件
UCLASS()
class PLAY_API AFPSCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AFPSCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

public:
	// 处理用于前后移动的输入。
	UFUNCTION()
		void MoveForward(float Value);

	// 处理用于左右移动的输入。
	UFUNCTION()
		void MoveRight(float Value);

	// 按下键时，设置跳跃标记。
	UFUNCTION()
		void StartJump();

	// 释放键时，清除跳跃标记。
	UFUNCTION()
		void StopJump();

public:


	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite)
		USkeletalMeshComponent* CharacterHandMesh;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UCameraComponent* CameraComp;
	//传入的物品信息结构体
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
		FItemStruct Incoming;
	//蓝图指定武器类
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Assets")
	    TSubclassOf<class AWeaponClass> WeaponClass; 
	//左右手骨骼插槽名称
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Assets")
		FName LeftSocketName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Assets")
		FName RightSocketName;
	//角色状态
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CharacterState")
		float MaxHP;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		float HP;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CharacterState")
		float MaxEP;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		float EP;
	//体力恢复量
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float EPRecover;
	//体力自动回复定时器
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		FTimerHandle EPTimerHandle;
	//受到的伤害
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		float ReceiveDamage;
	//生成的武器
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Weapon")
		AWeaponClass* Weapon;


	//通道检测返回的信息
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		FHitResult HitResult;
	//射线检测开关
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool LineTraceOnOff;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		bool bIsHit;
	//判断是否获取了武器?
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool isPickUpWeapon = false;
	//拾取事件开关
	UPROPERTY()
		bool isPickUp = false;
	//体力条是否可以扣取标志
	UPROPERTY()
		bool isEPFunctionEnd;

public:
		//Esc 按键按下的委托
		FClickEscDelegate EscClickDelegate;

public:

	//射线检测到的物品执行接口函数  接口调用
		IInteractInterface* Interface;
	//射线检测
	UFUNCTION(BlueprintCallable)
		FHitResult CreateLineTreaByChannel();

public:
	//角色HP=0时死亡  调用蓝图实现事件
	UFUNCTION(BlueprintImplementableEvent)
		void CharacterDieEvent();


public:

	//角色HP=0时死亡 C++实现
	//UFUNCTION(BlueprintCallable)
	//	void CharacterDieFunction();
	//血条
	UFUNCTION(BlueprintCallable)
		void HPFunction(int ConsumeHP);
	//能量条/体力条
	UFUNCTION(BlueprintCallable)
		void EPFunction();
	//拾取武器
	UFUNCTION(BlueprintCallable)
		void PickUpWeapon();
public:
	//E 键按下反馈
	UFUNCTION(BlueprintCallable)
		void E_ButtonPressed();
	//F 键按下反馈
	UFUNCTION(BlueprintCallable)
		void F_ButtonPressed();
	//Esc 键按下反馈
	UFUNCTION(BlueprintCallable)
		void Esc_ButtonPressed();
};
