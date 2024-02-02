// Fill out your copyright notice in the Description page of Project Settings.


#include "BackpackUI.h"
#include "ItemUI.h"
#include "BackpackActorComp.h"
#include "FPSPlayerController.h"
#include "Kismet/GameplayStatics.h"


bool UBackpackUI::Initialize()
{
	if (!Super::Initialize())
	{
		return false;
	}
	

	PlayerController = Cast<APlayerController>(GetOwningPlayer());

	//更新背包
	//UpdateItemList_Event();

	return true;
}


//更新背包事件,UUserWidget* IncomingItemUI
void UBackpackUI::UpdateItemList_Event()
{

	if (IsValid(BackpackComp) && IsValid(Backpack))
	{
		int ArrayIndex = 0;
		Backpack->ClearChildren();
		for (auto& str : BackpackComp->BackpackStruct)
		{

			UItemUI* ItemUI = CreateWidget<UItemUI>(PlayerController, ItemUIClass);
			
			//设置物品背包格位置
			ItemUI->Backpacklatticelocation = ArrayIndex;
			ArrayIndex += 1;
	
			if (IsValid(ItemUI))
			{
				ItemUI->CreateImageAndTextBlock(str);
				Backpack->AddChild(ItemUI);
			}
		}
	}
	
}

//更新背包事件,蓝图调用
void UBackpackUI::UpdateItemList_Event_BP(UBackpackActorComp* ImportBackpackComp)
{
	if (IsValid(ImportBackpackComp) && IsValid(Backpack))
	{
		int ArrayIndex = 0;
		Backpack->ClearChildren();
		for (auto& str : ImportBackpackComp->BackpackStruct)
		{

			UItemUI* ItemUI = CreateWidget<UItemUI>(PlayerController, ItemUIClass);

			//设置物品背包格位置
			ItemUI->Backpacklatticelocation = ArrayIndex;
			ArrayIndex += 1;

			if (IsValid(ItemUI))
			{
				ItemUI->CreateImageAndTextBlock(str);
				Backpack->AddChild(ItemUI);
			}
		}
	}
}
