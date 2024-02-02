// Fill out your copyright notice in the Description page of Project Settings.


#include "FPS_HUD.h"
#include "FPSPlayerController.h"
#include "Blueprint/UserWidget.h"


AFPS_HUD::AFPS_HUD()
{
	bMenuInViewport = false;  //默认还没显示菜单

}

void AFPS_HUD::BeginPlay()
{
	Super::BeginPlay();

	FPSCharacterColler = GetWorld()->GetFirstPlayerController();

	FPSCharacter = Cast<AFPSCharacter>(FPSCharacterColler->GetCharacter());


	//绑定玩家键盘Esc映射委托
	if (IsValid(FPSCharacter))
	{
		FPSCharacter->EscClickDelegate.AddUObject(this, &AFPS_HUD::MenuCallFunction);
	}

	if (HUDAsset)
	{
		HUD = CreateWidget<UUserWidget>(FPSCharacterColler, HUDAsset);
	}
	if (HUD)
	{
		HUD->AddToViewport();
		//HUD->SetVisibility(ESlateVisibility::Hidden); //默认隐藏玩家状态UI
	}
}

void AFPS_HUD::MenuCallFunction()
{
	
	if ( bMenuInViewport )
	{
		RemoveMenuFunction();    //删除菜单
		bMenuInViewport = false;   //菜单已删除标志
		HUD->SetVisibility(ESlateVisibility::Visible);  //显示玩家状态UI

	}
	else
	{
		CreateMenuFunction();  //生成菜单
		bMenuInViewport = true;     //菜单已生成标志  
		HUD->SetVisibility(ESlateVisibility::Hidden);   //隐藏玩家状态UI
	}

	MenuCallEvent();  //调用蓝图事件
}


//生成菜单UI
void AFPS_HUD::CreateMenuFunction()
{

	if (MenuBackgroundUIAsset)
	{
		MenuBackgroundUI = CreateWidget<UUserWidget>(FPSCharacterColler, MenuBackgroundUIAsset);
	}
	if (MenuBackgroundUI)
	{
		MenuBackgroundUI->AddToViewport();
	}

	if (PlayGameMenuUIAsset)
	{
		PlayGameMenuUI = CreateWidget<UUserWidget>(FPSCharacterColler, PlayGameMenuUIAsset);
	}
	if (PlayGameMenuUI)
	{
		PlayGameMenuUI->AddToViewport();
	}

	if (PlayGameMenuSettingUIAsset)
	{
		PlayGameMenuSettingUI = CreateWidget<UUserWidget>(FPSCharacterColler, PlayGameMenuSettingUIAsset);
	}
	if (PlayGameMenuSettingUI)
	{
		PlayGameMenuSettingUI->AddToViewport();
		PlayGameMenuSettingUI->SetVisibility(ESlateVisibility::Hidden);  //默认隐藏菜单设置UI
	}

	if (BlackBackgroundUIAsset)
	{
		BlackBackgroundUI = CreateWidget<UUserWidget>(FPSCharacterColler, BlackBackgroundUIAsset);
	}
	if (BlackBackgroundUI)
	{
		BlackBackgroundUI->AddToViewport();
		BlackBackgroundUI->SetVisibility(ESlateVisibility::SelfHitTestInvisible);  //设置不可交互菜单背景UI
	}

}

//删除菜单
void AFPS_HUD::RemoveMenuFunction()
{
	//检测菜单UI有效性
	bool MenuIsValid = IsValid(MenuBackgroundUI) && IsValid(PlayGameMenuUI) && IsValid(PlayGameMenuSettingUI) && IsValid(BlackBackgroundUI);

	if (MenuIsValid)
	{
		//MenuBackgroundUI->RemoveFromParent();
		//PlayGameMenuUI->RemoveFromParent();
		//PlayGameMenuSettingUI->RemoveFromParent();
		//BlackBackgroundUI->RemoveFromParent();

		MenuBackgroundUI->RemoveFromViewport();
		PlayGameMenuUI->RemoveFromViewport();
		PlayGameMenuSettingUI->RemoveFromViewport();
		BlackBackgroundUI->RemoveFromViewport();

		MenuBackgroundUI = nullptr;
		PlayGameMenuUI = nullptr;
		PlayGameMenuSettingUI = nullptr;
		BlackBackgroundUI = nullptr;
	}

}

void AFPS_HUD::SetVisibilityHUD(bool bOnAndOffVisibility)
{
	if (IsValid(HUD))
	{
		if (bOnAndOffVisibility)
		{
			HUD->SetVisibility(ESlateVisibility::Visible);
		}
		else
		{
			HUD->SetVisibility(ESlateVisibility::Hidden);
		}
	}
}

