// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ItemStruct.h"
#include "Components/WrapBox.h"

#include "BackpackUI.generated.h"

/**
 * 
 */
UCLASS()
class PLAY_API UBackpackUI : public UUserWidget
{
	GENERATED_BODY()
	

public:

	//包裹组件
	UPROPERTY(Meta = (BindWidget))
		UWrapBox* Backpack;
	//传入物品结构体信息
	//UPROPERTY(EditAnywhere, BlueprintReadWrite)
		//FItemStruct ItemStruct_C;
	//创建的图标UI的类
	UPROPERTY(BlueprintReadWrite)
		TSubclassOf<class UItemUI> ItemUIClass;
	
	//保存玩家控制器
	UPROPERTY()
	class APlayerController* PlayerController;
	//保存背包组件
	UPROPERTY()
	class UBackpackActorComp* BackpackComp;
public:
	//更新背包事件,UUserWidget* IncomingItemUI
	UFUNCTION(BlueprintCallable)
		void UpdateItemList_Event();
	//更新背包事件,蓝图调用
	UFUNCTION(BlueprintCallable)
		void UpdateItemList_Event_BP(UBackpackActorComp* ImportBackpackComp);

	virtual bool Initialize() override;


};
