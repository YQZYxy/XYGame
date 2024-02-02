// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ItemStruct.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "Components/Button.h"
 
#include "ItemUI.generated.h"

/**
 * 
 */
UCLASS()
class PLAY_API UItemUI : public UUserWidget
{
	GENERATED_BODY()

public:
	//UPROPERTY(Meta = (BindWidget))
		//UButton* ItemButton;
	UPROPERTY(Meta = (BindWidget))
		UImage* ItemImage;
	UPROPERTY(Meta = (BindWidget))
		UTextBlock* ItemName;

	//拼接
	UPROPERTY()
	FString Splicing;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
		FItemStruct ItemStruct_C;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int Backpacklatticelocation;


public:

	virtual bool Initialize() override;

	UFUNCTION(BlueprintCallable)
		void CreateImageAndTextBlock(FItemStruct IncomingItemStruct);//, UTextBlock* ItemName_in, UImage* ItemImage_in
};
