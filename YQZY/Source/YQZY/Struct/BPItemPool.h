// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Config/LogicConfig.h"
#include "CoreMinimal.h"
#include "BPItemPool.generated.h"


USTRUCT(BlueprintType)
struct FItemBaseData : public FTableRowBase
{
	GENERATED_BODY()
public:

	bool IsValid()
	{
		return  0 != item_id;
	}
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DataTable int")
		int32 type=0;		// 类型 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DataTable int")
		int32 item_id = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DataTable int")
		int64 max_num = 0;		//最大数量  
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DataTable int")
		int32 IsOverlapping = 0;	//是否可以重叠
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DataTable int")
		int32 IsDiscard = 0;		//是否可以丢弃

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DataTable FString")
		FString name;			//物品名
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DataTable FString")
		FString description;	//描述说明

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DataTable 2D")
	//	TSoftObjectPtr<UTexture> item_ui; //物品显示UI
};

static const uint32_t MAX_ITEM_ID = 65535;
#define ITEMPOOL UBPItemPool::Instance()
/**
 *
 */
UCLASS(Config = Game)
class UBPItemPool : public UObject
{
	GENERATED_BODY()
public:
	UBPItemPool();

	UFUNCTION(BlueprintCallable, Category = "ItemPool")
	bool Init();

	UFUNCTION(BlueprintCallable, Category = "ItemPool")
	static bool OnReload();
	UFUNCTION(BlueprintCallable, Category = "ItemPool")
	static UBPItemPool* Instance();
	UFUNCTION(BlueprintCallable, Category = "ItemPool")
	static void DeleteUObject();

	UFUNCTION(BlueprintCallable, Category = "ItemPool")
	bool FindItemById(int item_id);
	UFUNCTION(BlueprintCallable,Category = "ItemPool")
	const FItemBaseData GetItemBaseData(int item_id)const;
	

	const FItemBaseData* GetItemBaseDataPtr(int item_id)const;

private:
	UPROPERTY()
	TMap< int32,FItemBaseData> m_item_pool;//TArray<struct FItemBaseData> item_pool;
};







