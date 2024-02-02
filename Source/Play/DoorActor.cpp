// Fill out your copyright notice in the Description page of Project Settings.


#include "DoorActor.h"
#include "BossActorDelegate.h"



// Sets default values
ADoorActor::ADoorActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    //创建我们的默认组件
    DoorFrame = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DoorFrameMesh"));
    Door = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DoorMesh"));
    DoorTimelineComp = CreateDefaultSubobject<UTimelineComponent>(TEXT("DoorTimelineComp"));

    //设置组件附加
    DoorFrame->SetupAttachment(RootComponent);
    Door->AttachToComponent(DoorFrame, FAttachmentTransformRules::KeepRelativeTransform);
    Door->SetRelativeLocation(FVector(0, 35, 0));

}

// Called when the game starts or when spawned
void ADoorActor::BeginPlay()
{
	Super::BeginPlay();
	
    //将浮点轨道绑定到UpdateTimelineComp函数的输出
    UpdateFunctionFloat.BindDynamic(this, &ADoorActor::UpdateTimelineComp);

    //如果有浮点曲线，将其图表绑定到我们的更新函数
    if (DoorTimelineFloatCurve)
    {
        DoorTimelineComp->AddInterpFloat(DoorTimelineFloatCurve, UpdateFunctionFloat);
    }

    if (BossActorReference)
    {
        BossActorReference->OnBossDied.BindUObject(this, &ADoorActor::BossDiedEventFunction);
    }
}

// Called every frame
void ADoorActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void ADoorActor::BossDiedEventFunction()
{
    DoorTimelineComp->Play();
}

void ADoorActor::UpdateTimelineComp(float Output)
{
    // 基于时间轴曲线的输出，创建并设置门的新相对位置
    FRotator DoorNewRotation = FRotator(0.0f, Output, 0.f);
    Door->SetRelativeRotation(DoorNewRotation);
}

