// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Subsystems/GameInstanceSubsystem.h"
#include "Game/Config/LogicConfig.h"
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
		int32 type=0;		
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DataTable int")
		int32 item_id = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DataTable int")
		int64 max_num = 0;		
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DataTable int")
		int32 IsOverlapping = 0;	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DataTable int")
		int32 IsDiscard = 0;		

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DataTable FString")
		FString name;			
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DataTable FString")
		FString description;	

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DataTable 2D")
	//	TSoftObjectPtr<UTexture> item_ui; 
};

static const uint32_t MAX_ITEM_ID = 65535;
#define ITEMPOOL(world) UBPItemPool::GetBPItemPool(world)
/**
 *
 */
UCLASS(Config = Game)
class UBPItemPool : public UGameInstanceSubsystem
{
	GENERATED_BODY()
public:
	UBPItemPool();
	virtual bool ShouldCreateSubsystem(UObject* Outer) const;
	virtual void Initialize(FSubsystemCollectionBase& Collection);
	virtual void Deinitialize();

	UFUNCTION(BlueprintCallable, Category = "AYQZY_ItemPool")
	static UBPItemPool* GetBPItemPool(UWorld* world);

	UFUNCTION(BlueprintCallable, Category = "AYQZY_ItemPool")
	bool Init();

	UFUNCTION(BlueprintCallable, Category = "AYQZY_ItemPool")
	static bool OnReload();


	UFUNCTION(BlueprintCallable, Category = "AYQZY_ItemPool")
	bool FindItemById(int item_id);
	UFUNCTION(BlueprintCallable,Category = "AYQZY_ItemPool")
	const FItemBaseData GetItemBaseData(int item_id)const;
	

	const FItemBaseData* GetItemBaseDataPtr(int item_id)const;

private:
	UPROPERTY()
	TMap< int32,FItemBaseData> m_item_pool;//TArray<struct FItemBaseData> item_pool;
};







