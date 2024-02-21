// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "LineTreaComponent.generated.h"

class UCameraComponent;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class YQZY_API ULineTreaComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	ULineTreaComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


	UFUNCTION(BlueprintCallable, Category = "AYQZY_LineTreaComp")
		void OnOpenLineTrea();
	UFUNCTION(BlueprintCallable, Category = "AYQZY_LineTreaComp")
		void OnCloseLineTrea();

	UFUNCTION(BlueprintCallable)
		void CreateLineTreaSingleByCamera();
	UFUNCTION(BlueprintCallable)
		FHitResult GetCameraHitResult() {return m_HitResult;}
	UFUNCTION(BlueprintCallable)
		bool GetCameraIsHit() {return m_bIsHit;}
	UFUNCTION(BlueprintCallable)
		bool GetCameraLineTraceOnOff() {return m_LineTraceOnOff;}


	UFUNCTION(BlueprintCallable)
		FHitResult CreateLineTreaByVector(const AActor* Ignored, FVector BeginLoc, FVector Forward, float LengthLoc , ECollisionChannel CollisionChannel);
	UFUNCTION(BlueprintCallable)
		TArray<struct FHitResult> CreateLineTreaMultiByVector(const AActor* Ignored, FVector BeginLoc, FVector Forward, float LengthLoc, ECollisionChannel CollisionChannel);
	
	//UFUNCTION(BlueprintCallable)
	FHitResult CreateLineTreaSingleByChannel(const AActor* Ignored, FVector BeginLoc, FVector EndLoc, ECollisionChannel CollisionChannel = ECollisionChannel::ECC_GameTraceChannel1);
	//UFUNCTION(BlueprintCallable)
	TArray<struct FHitResult> CreateLineTreaMultiByChannel(const AActor* Ignored, FVector BeginLoc, FVector EndLoc, ECollisionChannel CollisionChannel = ECollisionChannel::ECC_GameTraceChannel1);


public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AYQZY_LineTreaComp")
		float m_LengthLoc;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AYQZY_LineTreaComp")
		TEnumAsByte<ECollisionChannel> m_CollisionChannel;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AYQZY_LineTreaComp")
		TObjectPtr<UCameraComponent> m_CameraComp;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AYQZY_LineTreaComp")
		TObjectPtr<AActor> m_IgnoredActor;

private:
	FHitResult m_HitResult;
	bool m_LineTraceOnOff;
	bool m_bIsHit; //是否发生碰撞
};
