// Fill out your copyright notice in the Description page of Project Settings.

#include "ItemBaseClass.h"
#include "FPSCharacter.h"
#include"Components/BoxComponent.h"
#include "Components/PostProcessComponent.h"
#include "openexr/Deploy/OpenEXR-2.3.0/OpenEXR/include/ImathFun.h"



// Sets default values
AItemBaseClass::AItemBaseClass()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComp"));
	BoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComp"));
	PostProcessComp = CreateDefaultSubobject<UPostProcessComponent>("PostProcessComp");
	ItemTimelineComp = CreateDefaultSubobject<UTimelineComponent>(TEXT("ItemTimelineComp"));

	RootComponent = StaticMeshComp;
	BoxComp->SetupAttachment(StaticMeshComp);
	PostProcessComp->SetupAttachment(StaticMeshComp);
}

// Called when the game starts or when spawned
void AItemBaseClass::BeginPlay()
{
	Super::BeginPlay();

	//将浮点轨道绑定到UpdateTimelineComp函数的输出
	UpdateFunctionFloat.BindDynamic(this, &AItemBaseClass::UpdateTimelineComp);

	//将其图表绑定到更新函数
	if (ItemTimelineFloatCurve)
	{
		ItemTimelineComp->AddInterpFloat(ItemTimelineFloatCurve, UpdateFunctionFloat);
	}

}

// Called every frame
void AItemBaseClass::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AItemBaseClass::OnOverlayBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

}

void AItemBaseClass::OnOverlayEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{

}

//void AItemBaseClass::NotifyActorBeginOverlap(AActor* OtherActor)
//{
//}
//
//
//void AItemBaseClass::NotifyActorEndOverlap(AActor* OtherActor)
//{
//	//AsFPSCharacter = Cast<AFPSCharacter>(OtherActor);
//	//AsFPSCharacter->LineTraceOnOff = false;
//
//}

void AItemBaseClass::SpawnItem()
{
	StaticMeshComp->SetStaticMesh(ItemStruct.StaticMesh);
	StaticMeshComp->SetSimulatePhysics(true);
	StaticMeshComp->SetCollisionResponseToChannel(ECC_GameTraceChannel3, ECollisionResponse::ECR_Block);
}

void AItemBaseClass::PickUpFocus(UUserWidget* UserWidget, FVector MoveRelativeLocation, FRotator MoveRelativeRotator, float DelayTime = 1.0f)
{
	RelativeLocation = MoveRelativeLocation;
	RelativeRotator = MoveRelativeRotator;
	Widget = UserWidget;

	//正向播放时间轴
	ItemTimelineComp->Play();

	GetWorldTimerManager().SetTimer(InOutHandle, this, &AItemBaseClass::CreateHintUI, DelayTime);

}

void AItemBaseClass::CreateHintUI()
{
	if (Widget)
	{
		Widget->AddToViewport();
		DestroySelf();
	}
}

void AItemBaseClass::UpdateTimelineComp(float Output)
{
	SelfLocation = this->GetActorLocation();
	SelfRotator = this->GetActorRotation();

	FVector MoveActorLocation = SelfLocation * (1 - Output) + RelativeLocation * Output;
	FRotator MoveActorRotation = SelfRotator * (1 - Output) + RelativeRotator * Output;
	this->SetActorLocation(MoveActorLocation);
	this->SetActorRotation(MoveActorRotation);
}

void AItemBaseClass::DestroySelf()
{
	Widget->RemoveFromParent();
	Widget = NULL;
	GetWorldTimerManager().ClearTimer(InOutHandle);
	Destroy(true);
}

