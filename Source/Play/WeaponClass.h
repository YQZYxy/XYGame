// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "ItemStruct.h"
#include "BackpackActorComp.h"
#include "InteractInterface.h"
#include "WeaponActorComp.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WeaponClass.generated.h"

UCLASS()
class PLAY_API AWeaponClass : public AActor, public IInteractInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWeaponClass();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		USkeletalMeshComponent* WeaponMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		USkeletalMeshComponent* ClipMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UBoxComponent* BoxComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UPostProcessComponent* PostProcessComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UWeaponActorComp* WeaponActorComp;
	//子弹名字
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category="Ammunition")
		FString AmmunitionName;
	//弹夹容量
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ammunition")
		int32 ClipAmmunitionSum;
	//所有子弹总数
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ammunition")
		int32 MaxAmmunitionSum;
	//背包内子弹总数
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ammunition")
		int32 BackpackAmmunitionSum;
	//需要销毁背包内的子弹数
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ammunition")
		int32 DestroyAmmunitionSum;
	//子弹命中伤害量
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float Damage;
public:
	//鼠标左键按下反馈
	UFUNCTION(BlueprintCallable)
		void FireButtonPressed();
	UFUNCTION(BlueprintCallable)
		void FireButtonReleased();

	//R 键按下反馈
	UFUNCTION(BlueprintCallable)
		void R_ButtonPressed();

	//遍历背包内武器的弹药总数
	UFUNCTION(BlueprintCallable)
		void FindBackpackAmmunitionSum(UBackpackActorComp* BackpackComp);
	//遍历背包内弹药  销毁发射出去的子弹
	UFUNCTION(BlueprintCallable)
		void FindBackpackDestroyAmmunition(UBackpackActorComp* BackpackComp);

};
