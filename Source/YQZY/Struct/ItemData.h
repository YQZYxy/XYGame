#pragma once

#include "CoreMinimal.h"
#include "ItemData.generated.h"

USTRUCT(BlueprintType)
struct YQZY_API FItemData
{
	GENERATED_BODY()

public:
	FItemData() :item_id(0), num(0) {};
	FItemData(int _item_id, int _num) :item_id(_item_id), num(_num) {};

	void operator= (const FItemData in_item)
	{
		item_id = in_item.item_id;
		num = in_item.num;
	}

	void operator+= (const FItemData in_item)
	{
		num += in_item.num;
	}

	//void operator+ (const FItemData in_item)
	//{
	//	num += in_item.num;
	//}

	void Reset() { item_id = 0; num = 0; };
	bool InValid() const { return 0 != item_id && 0 < num; }

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 item_id;	// 物品ID 
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int64 num;		// 数量  
};
