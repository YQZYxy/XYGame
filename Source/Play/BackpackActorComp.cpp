// Fill out your copyright notice in the Description page of Project Settings.


#include "BackpackActorComp.h"
#include "GameFramework/Actor.h"
#include "ItemBaseClass.h"
#include "FPSPlayerController.h"



// Sets default values for this component's properties
UBackpackActorComp::UBackpackActorComp()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;


}


// Called when the game starts
void UBackpackActorComp::BeginPlay()
{
	Super::BeginPlay();


}                                              


// Called every frame
void UBackpackActorComp::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}


//初始化背包
void UBackpackActorComp::Initialization_Event()
{

	//获取玩家角色
	OwnerPawn = Cast<APawn>(GetOwner());
	//获取玩家控制器
	PlayerController = Cast<AFPSPlayerController>(OwnerPawn->GetController());
	//创建背包UI
	if (BcakpackUIClass)
	{
		if (IsValid(PlayerController))
		{
			BackpackUI = CreateWidget<UBackpackUI>(PlayerController, BcakpackUIClass);
		}
	}
	if (BackpackUI)
	{
		BackpackUI->ItemUIClass = ItemUIClass;
		BackpackUI->BackpackComp = this;
		BackpackUI->AddToViewport();
		BackpackUI->SetVisibility(ESlateVisibility::Hidden);
		BackpackUI->UpdateItemList_Event();
	}

	//默认背包格子数
	ItemNum = 9;
	//Initialization_Event();  //初始化背包


	for (int Index = 0; Index < ItemNum; Index++)
	{
		BackpackStruct.Add(EmptyItem);
	}

}

//拾取物品
void UBackpackActorComp::IncomingItem_Event(FItemStruct IncomingItem)
{
	Incoming = IncomingItem;
	if (Incoming.IsOverlapping)
	{
		bool BreakInquireItem = false;  //检测背包内是否有相同物品名?

		//若物品可以叠加,则遍历背包内同名物品,更改物品数量属性
		for (auto& str : BackpackStruct)
		{
			if (str.Name == Incoming.Name)
			{
				str.Num = Incoming.Num + str.Num;
				BreakInquireItem = true;
				break; 
			}					
		}

		if (BreakInquireItem)
		{
			
			BreakInquireItem = false;  //结束遍历背包
			
			BackpackUI->UpdateItemList_Event();  //***更新背包***
		}
		else
		{
			//未找到同名物品,查找背包空位图标,插入拾取物品图标
			for (auto& str:BackpackStruct)
			{
				if (str.Name == EmptyItem.Name)
				{
					str = Incoming;
					break; 
				}
			}

			BackpackUI->UpdateItemList_Event();	 //***更新背包***
		}
	}
	else
	{	
		//不可叠加的物品,遍历背包第一个空位图标,插入
		for (auto& str : BackpackStruct)
		{
			if (str.Name == EmptyItem.Name)
			{
				str = Incoming;
				break;
			}
		}

		BackpackUI->UpdateItemList_Event();		//***更新背包***
	}
}

//丢弃物品
void UBackpackActorComp::RemoveItem_Event(int32 Lattice, int32 RemoveNum)
{
	if (RemoveNum > 0)
	{
		if (RemoveNum >= BackpackStruct[Lattice].Num)
		{
			ThrowItem_Event(BackpackStruct[Lattice]);
			BackpackStruct[Lattice] = EmptyItem;
		}
		else
		{
			FItemStruct RemoveItemStruct;
			RemoveItemStruct = BackpackStruct[Lattice];
			RemoveItemStruct.Num = RemoveNum;

			//调用生成丢弃物品函数
			ThrowItem_Event(RemoveItemStruct);

			BackpackStruct[Lattice].Num -= RemoveNum;
		}

		BackpackUI->UpdateItemList_Event();	 //***更新背包***
	}
}

//销毁物品
void UBackpackActorComp::Destroyed_Event(int32 Lattice, int32 RemoveNum)
{
	if (RemoveNum > 0)
	{
		if (RemoveNum >= BackpackStruct[Lattice].Num)
		{
			BackpackStruct[Lattice] = EmptyItem;
		}
		else
		{
			FItemStruct RemoveItemStruct;
			RemoveItemStruct = BackpackStruct[Lattice];
			RemoveItemStruct.Num = RemoveNum;

			BackpackStruct[Lattice].Num -= RemoveNum;
		}

		BackpackUI->UpdateItemList_Event();	 //***更新背包***
	}
}


//生成丢弃的物品  消耗物或者销毁则不生成物品
void UBackpackActorComp::ThrowItem_Event(FItemStruct IncomingItem)
{
	if (IsValid(ItemBaseClass))
	{
		Incoming = IncomingItem;

		FVector ItemLocation = OwnerPawn->GetActorLocation();
		FVector ItemForward = PlayerController->AActor::GetActorForwardVector() * 100;
		FVector ItemTransform = ItemForward + ItemLocation;

		FActorSpawnParameters ItemParameters;

		AItemBaseClass* ReturnValue = GetWorld()->SpawnActor<AItemBaseClass>(ItemBaseClass, ItemTransform, FRotator(0.0f), ItemParameters);

		ReturnValue->ItemStruct = IncomingItem;
		ReturnValue->SpawnItem();
	}
	
}


//互换物品格
void UBackpackActorComp::SwapItem(int32 Lattice_A, int32 Lattice_B)
{
	BackpackStruct.Swap(Lattice_A, Lattice_B);
	BackpackUI->UpdateItemList_Event();	 //***更新背包***
}

//打开背包
void UBackpackActorComp::OnBackpack_Event()
{
	if (BackpackUI)
	{
		if (BackpackUI->IsVisible())
		{
			//隐藏背包和鼠标
			BackpackUI->SetVisibility(ESlateVisibility::Hidden);
			PlayerController->bShowMouseCursor = false;
			//设置游戏输入模式
			FInputModeGameOnly InputModeGameOnly;
			PlayerController->SetInputMode(InputModeGameOnly);
		}
		else
		{
			//显示背包和鼠标
			BackpackUI->UpdateItemList_Event();	 //***更新背包***
			BackpackUI->SetVisibility(ESlateVisibility::Visible);
			PlayerController->bShowMouseCursor = true; 
			//设置游戏和UI输入模式
			FInputModeGameAndUI InputModeGameAndUI;
			InputModeGameAndUI.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
			PlayerController->SetInputMode(InputModeGameAndUI);

		}
		
	}
	
}

//关闭背包
void UBackpackActorComp::OffBackpack_Event()
{
	if (BackpackUI)
	{
		//隐藏背包和鼠标
		BackpackUI->SetVisibility(ESlateVisibility::Hidden);
		PlayerController->bShowMouseCursor = false;
		//设置游戏输入模式
		FInputModeGameOnly InputModeGameOnly;
		PlayerController->SetInputMode(InputModeGameOnly);
	}
}
