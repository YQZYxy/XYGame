// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemUI.h"


bool UItemUI::Initialize()
{
	if (!Super::Initialize())
	{
		return false;
	}

	//ItemName = Cast<UTextBlock>(GetWidgetFromName("ItemName"));
	//ItemImage = Cast<UImage>(GetWidgetFromName("ItemImage"));
	
	return true;
}

void UItemUI::CreateImageAndTextBlock(FItemStruct IncomingItemStruct)
{
	ItemStruct_C = IncomingItemStruct;

	//初始化拼接字符串
	Splicing = NULL;
	if (IncomingItemStruct.Name == "")
	{
		if (IsValid(ItemName)&&IsValid(ItemImage))
		{
			ItemName->SetText(FText::FromString(""));
			ItemImage->SetOpacity(1.0f);
			//GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Yellow, TEXT("成功"));
		}
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Yellow, TEXT("拾取成功"));
		Splicing.Append(IncomingItemStruct.Name);
		Splicing.Append(FString::FromInt(IncomingItemStruct.Num));

		ItemName->SetText(FText::FromString(Splicing));
		ItemImage->SetBrushFromTexture(IncomingItemStruct.Photo);
	}
}
