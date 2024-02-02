// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSPlayerController.h"
#include "Blueprint/UserWidget.h"
#include "FPSCharacter.h"
#include "TimerManager.h"
#include "Kismet/GameplayStatics.h"

AFPSPlayerController::AFPSPlayerController()
{
	bShowMouseCursor = true;
	//DefaultMouseCursor = EMouseCursor::Crosshairs;  //鼠标形状
	bEnableClickEvents = true;
	bEnableMouseOverEvents = true;

	bMenuInViewport = false;  //默认还没显示菜单
}

void AFPSPlayerController::BeginPlay()
{
	Super::BeginPlay();

	//绑定玩家按下Esc事件发生
	FPSCharacter = Cast<AFPSCharacter>(this->GetCharacter());
	if (IsValid(FPSCharacter))
	{
		FPSCharacter->EscClickDelegate.AddUObject(this, &AFPSPlayerController::MenuCallDelegate);
	}
	
};


//Esc 按键设置玩家输入模式  设置鼠标显示
void AFPSPlayerController::MenuCallFunction()
{
	GetWorldTimerManager().ClearTimer(InOutHandle);
	if (bMenuInViewport)
	{
		bMenuInViewport = false;
		this->bShowMouseCursor = false;  //隐藏鼠标

		FInputModeGameOnly InputModeGameOnly;
		this->SetInputMode(InputModeGameOnly);

	}
	else
	{
		bMenuInViewport = true;
		this->bShowMouseCursor = true;    //显示鼠标
		FInputModeUIOnly InputModeUIOnly;
		this->SetInputMode(InputModeUIOnly);
		UGameplayStatics::SetGamePaused(this, true);  //暂停游戏
	}
}

void AFPSPlayerController::MenuCallDelegate()
{
	UGameplayStatics::SetGamePaused(this, false);   //解除游戏暂停

	//开启定时器  延迟0.2ms再设置玩家输入模式
	GetWorldTimerManager().SetTimer(InOutHandle, this, &AFPSPlayerController::MenuCallFunction, 0.2f);
}
