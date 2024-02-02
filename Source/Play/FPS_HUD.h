// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "FPSCharacter.h"
#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "FPS_HUD.generated.h"

/**
 * 
 */
UCLASS()
class PLAY_API AFPS_HUD : public AHUD
{
	GENERATED_BODY()

public:

	AFPS_HUD();

protected:
	virtual void BeginPlay() override;
	
public:
	//玩家状态UI
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSubclassOf<class UUserWidget>  HUDAsset;
	//渐变渲染度类
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSubclassOf<class UUserWidget>  MenuBackgroundUIAsset;
	//菜单类
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSubclassOf<class UUserWidget>  PlayGameMenuUIAsset;
	//菜单设置类
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSubclassOf<class UUserWidget>  PlayGameMenuSettingUIAsset;
	//菜单背景类
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSubclassOf<class UUserWidget>  BlackBackgroundUIAsset;


	//玩家状态UI
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UUserWidget* HUD;
	// 菜单背景UI  
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UUserWidget* MenuBackgroundUI;
	//菜单交互UI
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UUserWidget* PlayGameMenuUI;
	//菜单设置交互UI
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UUserWidget* PlayGameMenuSettingUI;
	//渲染度动画  修饰UI                                                 
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UUserWidget* BlackBackgroundUI;

public:
	//菜单是否在视口
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		bool bMenuInViewport;

	//玩家控制器
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	 APlayerController* FPSCharacterColler;


public:
	//玩家角色引用  绑定角色输入委托
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite)
		AFPSCharacter* FPSCharacter;

public:
	//调用生成删除菜单
	UFUNCTION(BlueprintCallable)
		void MenuCallFunction();
	//生成菜单UI
	UFUNCTION(BlueprintCallable)
		void CreateMenuFunction();
	//删除菜单UI
	UFUNCTION(BlueprintCallable)
		void RemoveMenuFunction();
	//调用蓝图实现覆盖
	UFUNCTION(BlueprintImplementableEvent)
		void MenuCallEvent();
	//隐藏玩家的抬头显示
	UFUNCTION(BlueprintCallable)
	void SetVisibilityHUD(bool bOnAndOffVisibility);

};
