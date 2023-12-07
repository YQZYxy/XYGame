// Fill out your copyright notice in the Description page of Project Settings.


#include "LineTreaComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Engine/World.h"
#include "Camera/CameraComponent.h"
#include "YQZYLog.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(LineTreaComponent)

// Sets default values for this component's properties
ULineTreaComponent::ULineTreaComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	m_CameraComp = nullptr;
	m_CollisionChannel = ECC_GameTraceChannel1;  //射线检测通道
}


// Called when the game starts
void ULineTreaComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void ULineTreaComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!m_LineTraceOnOff)
	{
		return;
	}

	CreateLineTreaSingleByCamera();

	if (m_HitResult.bBlockingHit)
	{
		if (m_HitResult.GetActor())
		{
			UKismetSystemLibrary::PrintString(GetWorld(), m_HitResult.GetActor()->GetName());  //显示射线检测物品名称	
			//if (Interface != nullptr)
			//{
			//	//射线检测场景物品信息
			//	Interface->Execute_OnFocusEvent(m_HitResult.GetActor());
			//	UKismetSystemLibrary::PrintString(GetWorld(), m_HitResult.GetActor()->GetName());  //显示射线检测物品名称	
			//}
			//else
			//{
			//	Interface = Cast<IInteractInterface>(m_HitResult.Actor);
			//}
		}
	}
	else
	{
		//Interface = nullptr;
	}
	
}

void ULineTreaComponent::OnOpenLineTrea()
{
	m_LineTraceOnOff = true;
}

void ULineTreaComponent::OnCloseLineTrea()
{
	m_LineTraceOnOff = false;
}

//射线检测
void ULineTreaComponent::CreateLineTreaSingleByCamera()
{
	m_HitResult.Reset();
	if (!m_CameraComp)
	{
		return;
	}

	if (0.0f == m_LengthLoc )
	{
		return;
	}

	//FVector BeginLoc = GetWorld()->GetFirstPlayerController()->PlayerCameraManager->GetCameraLocation(); //射线生成时开始的位置
	FVector BeginLoc = m_CameraComp->GetComponentLocation();
	FVector EndLoc = BeginLoc + m_CameraComp->GetForwardVector() * m_LengthLoc;  //射线结束位置

	YQZYError("BeginLoc[%d] EndLoc[%d] Forward[%d], ", BeginLoc, EndLoc, m_CameraComp->GetForwardVector());
	if (nullptr == m_IgnoredActor)
	{
		m_HitResult = CreateLineTreaSingleByChannel(nullptr, BeginLoc, EndLoc,m_CollisionChannel);
	}
	else
	{
		m_HitResult = CreateLineTreaSingleByChannel(m_IgnoredActor, BeginLoc, EndLoc,m_CollisionChannel);
	}
	
}



FHitResult ULineTreaComponent::CreateLineTreaByVector(const AActor* Ignored, FVector BeginLoc, FVector Forward, float LengthLoc, ECollisionChannel CollisionChannel)
{
	static FVector EndLoc = BeginLoc + Forward * LengthLoc;

	if (nullptr == Ignored)
	{
		return CreateLineTreaSingleByChannel(nullptr, BeginLoc, EndLoc,CollisionChannel);
	}

	return CreateLineTreaSingleByChannel(Ignored, BeginLoc, EndLoc,CollisionChannel);
}

TArray<struct FHitResult> ULineTreaComponent::CreateLineTreaMultiByVector(const AActor* Ignored, FVector BeginLoc, FVector Forward, float LengthLoc, ECollisionChannel CollisionChannel)
{
	static FVector EndLoc = BeginLoc + Forward * LengthLoc;

	if (nullptr == Ignored)
	{
		return CreateLineTreaMultiByChannel(nullptr, BeginLoc, EndLoc,CollisionChannel);
	}

	return CreateLineTreaMultiByChannel(Ignored, BeginLoc, EndLoc,CollisionChannel);
}
	

FHitResult ULineTreaComponent::CreateLineTreaSingleByChannel(const AActor* Ignored,  FVector BeginLoc,  FVector EndLoc, ECollisionChannel CollisionChannel)
{
	static FHitResult HitResult;
	HitResult.Reset();

	m_bIsHit = false;

	//参数
	static FCollisionQueryParams CollisonQueryParams(TEXT("QueryParams"), true, NULL);
	CollisonQueryParams.bTraceComplex = true;
	CollisonQueryParams.bReturnPhysicalMaterial = false;
	
	if (nullptr != Ignored)
	{
		CollisonQueryParams.AddIgnoredActor(Ignored);
	}

	m_bIsHit = GetWorld()->LineTraceSingleByChannel(HitResult, BeginLoc, EndLoc, CollisionChannel, CollisonQueryParams);

	UKismetSystemLibrary::DrawDebugLine(GetWorld(), BeginLoc, HitResult.GetActor() ? HitResult.Location : EndLoc, FColor::Red, 0.1f, 1.0f);  //绘画

	return HitResult;
}

TArray<struct FHitResult> ULineTreaComponent::CreateLineTreaMultiByChannel(const AActor* Ignored, FVector BeginLoc, FVector EndLoc, ECollisionChannel CollisionChannel)
{
	static TArray<struct FHitResult> HitResult;
	HitResult.Reset();

	//参数
	static FCollisionQueryParams CollisonQueryParams(TEXT("QueryParams"), true, NULL);
	CollisonQueryParams.bTraceComplex = true;
	CollisonQueryParams.bReturnPhysicalMaterial = false;
	
	if (nullptr != Ignored)
	{
		CollisonQueryParams.AddIgnoredActor(Ignored);
	}

	GetWorld()->LineTraceMultiByChannel(HitResult, BeginLoc, EndLoc, CollisionChannel, CollisonQueryParams);

	UKismetSystemLibrary::DrawDebugLine(GetWorld(), BeginLoc, HitResult[HitResult.Num()-1].GetActor() ?HitResult[HitResult.Num()-1].Location : EndLoc, FColor::Red, 0.1f, 1.0f);  //绘画

	return HitResult;
}
