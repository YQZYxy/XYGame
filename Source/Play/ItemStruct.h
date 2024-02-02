// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemStruct.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct FItemStruct
{
	GENERATED_BODY()

public:
	//物品名字
	UPROPERTY(EditAnywhere, BlueprintReadWrite)		
		FString Name;
	//物品数量
	UPROPERTY(EditAnywhere,BlueprintReadWrite)		
		int32 Num;
	//物品网格体引用
	UPROPERTY(EditAnywhere, BlueprintReadWrite)		
		UStaticMesh* StaticMesh;
	//图片
	UPROPERTY(EditAnywhere, BlueprintReadWrite)     
		UTexture2D* Photo;
	//物品文本说明
	UPROPERTY(EditAnywhere, BlueprintReadWrite)		
		FText Discription;
	//是否可以重叠
	UPROPERTY(EditAnywhere, BlueprintReadWrite)		
		bool IsOverlapping;
	//是否可以丢弃
	UPROPERTY(EditAnywhere, BlueprintReadWrite)		
		bool IsDiscard;
};
