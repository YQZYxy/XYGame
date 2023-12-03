// Fill out your copyright notice in the Description page of Project Settings.

#pragma once



#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Knapsack.generated.h"


struct FItemData;
class APlayerController;
class APawn;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class YQZY_API UKnapsack : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UKnapsack();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


	UFUNCTION(BlueprintCallable)
		void Init();

public:

	//添加物品
	UFUNCTION(BlueprintCallable, Category = "AYQZY_Knapsack")
		void OnAddItemList(TArray<FItemData> item_list, FString& reason);
	UFUNCTION(BlueprintCallable, Category = "Knapsack")
		void OnAddItemData(FItemData item, FString& reason);
	UFUNCTION(BlueprintCallable, Category = "Knapsack")
		int OnAddItemId(int32 item_id, int64 item_num, FString& reason);

	//消耗物品 
	UFUNCTION(BlueprintCallable, Category = "Knapsack")
		void OnConsumeItemList(TArray<FItemData>& item_list, FString& reason);
	UFUNCTION(BlueprintCallable, Category = "Knapsack")
		void OnConsumeItemData(FItemData item, FString& reason);
	UFUNCTION(BlueprintCallable, Category = "Knapsack")
		int OnConsumeItemId(int32 item_id, int64 item_num, FString& reason);
	 
	//销毁物品
	UFUNCTION(BlueprintCallable, Category = "Knapsack")
		void OnDestroyedItemByIdOrIndex(const int32 id, int32 index = -1);
	//交换背包格子内物品
	UFUNCTION(BlueprintCallable, Category = "Knapsack")
		void OnSwapItem(const int32 index_A, const int32 index_B);

public:
	//背包格子大小	默认9 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Assets")
		int32 knapsack_size;
	//拥有者
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		APawn* OwnerPawn;
	//玩家控制器
	UPROPERTY(BlueprintReadOnly)
		APlayerController* PlayerController;

protected:
	//背包结构体数组物品数据
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Assets")
		TArray<FItemData> m_knapsack;
};
