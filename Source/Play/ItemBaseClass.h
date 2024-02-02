// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Components/TimelineComponent.h"
#include "InteractInterface.h"
#include"ItemStruct.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ItemBaseClass.generated.h"


UCLASS()
class PLAY_API AItemBaseClass : public AActor, public IInteractInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AItemBaseClass();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//virtual void NotifyActorBeginOverlap(AActor* OtherActor);
	//virtual void NotifyActorEndOverlap(AActor* OtherActor);

	UFUNCTION()
	virtual void OnOverlayBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	virtual void OnOverlayEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

public:
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UStaticMeshComponent* StaticMeshComp;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UBoxComponent* BoxComp;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UPostProcessComponent* PostProcessComp;
	//拾取物信息
	UPROPERTY(EditAnywhere, BlueprintReadWrite ,Category="Assets")
		FItemStruct ItemStruct;
	//控制的玩家
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Assets")
		class AFPSCharacter* AsFPSCharacter;

	//保存蓝图调用函数传入的蓝图资产
	UPROPERTY()
		FVector RelativeLocation;
	UPROPERTY()
		FRotator RelativeRotator;
	UPROPERTY()
		UUserWidget* Widget;

	//物品自身当前位置
	UPROPERTY()
		FVector SelfLocation;
	UPROPERTY()
		FRotator SelfRotator;

	// 用于保留曲线资产的变量
	UPROPERTY(EditAnywhere)
		UCurveFloat* ItemTimelineFloatCurve;
	//用于对门网格体进行动画处理的时间轴组件
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		class UTimelineComponent* ItemTimelineComp;
	//用于处理我们的更新轨道事件的浮点轨道签名
	UPROPERTY()
	FOnTimelineFloat UpdateFunctionFloat;

public:



	//生成丢弃物品
	UFUNCTION(BlueprintCallable)
		void SpawnItem();					

	//拾取物品后移动物品使玩家镜头聚焦物品  生成提示UI
	UFUNCTION(BlueprintCallable)
		void PickUpFocus(UUserWidget* UserWidget, FVector MoveRelativeLocation, FRotator MoveRelativeRotator, float DelayTime);
	//定时器句柄
	FTimerHandle InOutHandle;

	//生成拾取成功提示UI
	UFUNCTION(BlueprintCallable)
		void CreateHintUI();

	//用于使用时间轴图表更新物品相对位置的函数
	UFUNCTION()
		void UpdateTimelineComp(float Output);

	//销毁物品自身
	UFUNCTION(BlueprintCallable)
		void DestroySelf();
};
