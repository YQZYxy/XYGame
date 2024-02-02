// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "BackpackUI.h"
#include "Blueprint/UserWidget.h"
#include "ItemStruct.h"
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ItemUI.h"
#include "BackpackActorComp.generated.h"

//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("Hello world"));
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PLAY_API UBackpackActorComp : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UBackpackActorComp();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	//背包格子大小
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Assets")
		int ItemNum;
	//拥有者
	UPROPERTY(EditAnywhere,BlueprintReadOnly)
		APawn* OwnerPawn;
	//玩家控制器
	UPROPERTY(BlueprintReadOnly)
		class AFPSPlayerController* PlayerController;
	//背包结构体数组物品数据
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Assets")
		TArray< FItemStruct > BackpackStruct;
	//默认空的物品属性
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Assets")
		FItemStruct EmptyItem;
	//传入物品的属性数据
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		FItemStruct Incoming;
	//背包物品的类
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Assets")
		TSubclassOf<class AItemBaseClass> ItemBaseClass;
	//保存生成的背包UI
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
		class UBackpackUI* BackpackUI;
	//创建背包UI的类
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Assets")
		TSubclassOf<class UBackpackUI> BcakpackUIClass;
	//创建背包物品UI的类
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Assets")
		TSubclassOf<class UItemUI> ItemUIClass;

public:

	//初始化背包
	UFUNCTION(BlueprintCallable)
		void Initialization_Event();
	//拾取物品
	UFUNCTION(BlueprintCallable)
		void IncomingItem_Event(FItemStruct IncomingItem);
	//丢弃物品
	UFUNCTION(BlueprintCallable)
		void RemoveItem_Event(int32 Lattice, int32 RemoveNum);
	//销毁物品
	UFUNCTION(BlueprintCallable)
		void Destroyed_Event(int32 Lattice, int32 RemoveNum);
	//交换背包格子内物品
	UFUNCTION(BlueprintCallable)
		void SwapItem(int32 Lattice_A, int32 Lattice_B);
	//生成丢弃的物品
	UFUNCTION(BlueprintCallable)
		void ThrowItem_Event(FItemStruct IncomingItem);
	//打开背包事件
	UFUNCTION(BlueprintCallable)
		void OnBackpack_Event();
	//关闭背包事件
	UFUNCTION(BlueprintCallable)
		void OffBackpack_Event();

};
