// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/TimelineComponent.h"

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DoorActor.generated.h"


UCLASS()
class PLAY_API ADoorActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADoorActor();

    // 用于保留曲线资产的变量
    UPROPERTY(EditInstanceOnly)
        UCurveFloat* DoorTimelineFloatCurve;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

    void BossDiedEventFunction();
    //引用事件分发器类
    UPROPERTY(EditInstanceOnly, BlueprintReadWrite)
        class ABossActorDelegate* BossActorReference;

    //门的网格体组件
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
        UStaticMeshComponent* DoorFrame;
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
        UStaticMeshComponent* Door;

    //门网格体进行动画处理的时间轴组件
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
        UTimelineComponent* DoorTimelineComp;

    //更新轨道事件的浮点轨道签名
    FOnTimelineFloat UpdateFunctionFloat;

    //使用时间轴图表更新门相对位置的函数
    UFUNCTION()
        void UpdateTimelineComp(float Output);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
