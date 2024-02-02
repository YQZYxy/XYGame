// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "FPSPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class PLAY_API AFPSPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AFPSPlayerController();

protected:

	virtual void BeginPlay() override;

	//virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	//玩家引用
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class AFPSCharacter* FPSCharacter;

public:
	//菜单是否在视口
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		bool bMenuInViewport;

	//定时器句柄
	FTimerHandle InOutHandle;


public:
	//菜单调用
	UFUNCTION(BlueprintCallable)
		void MenuCallFunction();
	//委托菜单调用
	UFUNCTION(BlueprintCallable)
		void MenuCallDelegate();

};
