// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "InteractInterface.h"
#include "BackpackActorComp.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InteractableActorBaseClass.generated.h"

UCLASS()
class PLAY_API AInteractableActorBaseClass : public AActor, public IInteractInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AInteractableActorBaseClass();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UStaticMeshComponent* RootStaticMesh;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UPostProcessComponent* PostProcessComp;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UBoxComponent* BoxComp;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UWidgetComponent* WidgetComp;


public:
		
	//virtual void () override;
	UFUNCTION()
	virtual void OnOverlayBegin( UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	virtual void OnOverlayEnd( UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	
	//在背包内寻找同名物品
	UFUNCTION(BlueprintCallable)
		int findItemStruct(UBackpackActorComp* BackpackComp, FItemStruct ItemName);   

	//获取玩家相对自己的位置
	UFUNCTION(BlueprintCallable)
		int GetPlayerRelativeLocation(int DistanceProportion, APlayerController* CharacterPlayerController);

	//球体检测 使碰撞物附加损伤  OutHits输入的命中结果数组  BaseDamage施加伤害量 
	UFUNCTION(BlueprintCallable)
		void ApplySphereByChannelDamage(TArray<struct FHitResult> OutHits, float BaseDamage);

};
