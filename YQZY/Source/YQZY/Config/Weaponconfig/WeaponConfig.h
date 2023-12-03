// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Config/LogicConfig.h"
#include "CoreMinimal.h"
#include "WeaponConfig.generated.h"

USTRUCT(BlueprintType)
struct FWeaponData : public FTableRowBase
{
	GENERATED_BODY()
public:
	FWeaponData(){}
	void Reset()
	{
		item_id = 0;
		max_num = 0;		
		IsOverlapping = 0;	
		IsDiscard = 0;		
	}
	bool IsValid()
	{
		return  0 != item_id;
	}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DataTable FString")
	int32 item_id = 0;
	int64 max_num = 0;		
	int32 IsOverlapping = 0;	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DataTable FString")
	int32 IsDiscard = 0;	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DataTable FString")
	FString name;		
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DataTable FString")
	FString description;	
};

class ULogicConfig;

UCLASS()
class YQZY_API UWeaponConfig : public ULogicConfig
{
	GENERATED_BODY()
public:
	virtual bool Init(const FName& path, FString& err)override;

	UFUNCTION(BlueprintCallable, Category = "AYQZY_WeaponConfig")
		bool FindItemById(int item_id);
	UFUNCTION(BlueprintCallable, Category = "")
		const FWeaponData GetItemBaseData(int item_id)const;

	const FWeaponData* GetItemBaseDataPtr(int item_id)const;

private:
	bool InitWeaponDataCfg(const FName& path, FString& err);

	TMap< int32, FWeaponData> item_pool;
};
