// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractableActorBaseClass.h"
#include "Components/PostProcessComponent.h"
#include "Components/BoxComponent.h"
#include "Components/WidgetComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"
// Sets default values
AInteractableActorBaseClass::AInteractableActorBaseClass()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootStaticMesh = CreateDefaultSubobject<UStaticMeshComponent>("RootStaticMesh");
	PostProcessComp = CreateDefaultSubobject<UPostProcessComponent>("PostProcessComp");
	BoxComp = CreateDefaultSubobject<UBoxComponent>("BoxComp");
	WidgetComp = CreateDefaultSubobject<UWidgetComponent>("WidgetComp");

	RootComponent = RootStaticMesh;
	PostProcessComp->SetupAttachment(RootStaticMesh);
	BoxComp->SetupAttachment(RootStaticMesh);
	WidgetComp->SetupAttachment(RootStaticMesh);

}

// Called when the game starts or when spawned
void AInteractableActorBaseClass::BeginPlay()
{
	Super::BeginPlay();
	//BoxComp->OnComponentBeginOverlap.AddDynamic(this, &AInteractableActorBaseClass::OnOverlayBegin);
	//BoxComp->OnComponentEndOverlap.AddDynamic(this, &AInteractableActorBaseClass::OnOverlayEnd);
}

// Called every frame
void AInteractableActorBaseClass::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AInteractableActorBaseClass::OnOverlayBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp,Warning, TEXT("AInteractableActorBaseClass::OnOverlayBegin"));
}

void AInteractableActorBaseClass::OnOverlayEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	UE_LOG(LogTemp, Warning, TEXT("AInteractableActorBaseClass::OnOverlayEnd"));

}

//在背包内寻找同名物品
int AInteractableActorBaseClass::findItemStruct(UBackpackActorComp* BackpackComp, FItemStruct ItemName) 
{
	int index = 0;
	for (auto& Target : BackpackComp->BackpackStruct)
	{
		bool TRUE = Target.Name == ItemName.Name && Target.Photo == ItemName.Photo && Target.StaticMesh == ItemName.StaticMesh;  //查找  匹配物品的信息
		if (TRUE)
		{
			return index;
		}
		index++;
	}
	return -1;
} 





int AInteractableActorBaseClass::GetPlayerRelativeLocation(int DistanceProportion, APlayerController* CharacterPlayerController)
{
	FVector CharacterLoc = CharacterPlayerController->GetPawn()->GetActorLocation();
	//FVector CharacterLoc = GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation();  //玩家位置
	FVector SelfLoc = GetActorLocation();		 //获取自身位置
	FVector RelativeLocation = CharacterLoc - SelfLoc;	  //相对位置的向量差
	int Result = pow(RelativeLocation.X,2)  + pow(RelativeLocation.Y,2) + pow(RelativeLocation.Z,2);	//获取相对距离平方和
 
	return sqrt(Result)/ DistanceProportion;		//返回开根号  除以显示实际距离比例(DistanceProportion);
}

//对球体检测碰撞特定物体时施加伤害
void AInteractableActorBaseClass::ApplySphereByChannelDamage(TArray<struct FHitResult> OutHits, float BaseDamage)
{
	for(auto& HitResult : OutHits)
	{
		//制造损伤
		UGameplayStatics::ApplyPointDamage(HitResult.GetActor(), BaseDamage, HitResult.Location , HitResult, NULL, this, NULL);
		//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, HitResult.GetActor()->GetName());
	}

}
