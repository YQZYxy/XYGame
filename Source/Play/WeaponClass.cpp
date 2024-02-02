// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponClass.h"
#include "Components/BoxComponent.h"
#include "Components/PostProcessComponent.h"


// Sets default values
AWeaponClass::AWeaponClass()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WeaponMesh"));
	ClipMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("ClipMesh"));
	BoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComp"));
	PostProcessComp = CreateDefaultSubobject<UPostProcessComponent>(TEXT("PostProcessComp"));
	WeaponActorComp = CreateDefaultSubobject<UWeaponActorComp>(TEXT("WeaponActorComp"));

	RootComponent = WeaponMesh;
	ClipMesh->SetupAttachment(WeaponMesh);
	BoxComp->SetupAttachment(WeaponMesh);
	PostProcessComp->SetupAttachment(WeaponMesh);


}

// Called when the game starts or when spawned
void AWeaponClass::BeginPlay()
{
	Super::BeginPlay();

	ClipMesh->AttachToComponent(WeaponMesh, FAttachmentTransformRules::SnapToTargetNotIncludingScale, "ClipSocket");
	
	//设置子弹伤害
	if (WeaponActorComp)
	{
		WeaponActorComp->SetAmmunitionDamage(Damage);
	}
}

// Called every frame
void AWeaponClass::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AWeaponClass::FireButtonPressed()
{
	WeaponActorComp->FireButtonPressed();
}

void AWeaponClass::FireButtonReleased()
{
	WeaponActorComp->FireButtonReleased();
}

void AWeaponClass::R_ButtonPressed()
{
	MaxAmmunitionSum = WeaponActorComp->AmmunitionAmount_Now + BackpackAmmunitionSum;   //获取角色拥有的所有子弹
	//检测所有的子弹是否大于弹夹容量   
	if (MaxAmmunitionSum > ClipAmmunitionSum)			 
	{
		//如果所有的子弹大于弹夹容量,则"销毁背包内的子弹数"为弹夹内现有子弹再填满弹夹所需的"子弹数"
		DestroyAmmunitionSum = ClipAmmunitionSum - WeaponActorComp->AmmunitionAmount_Now;  
		WeaponActorComp->Reload(ClipAmmunitionSum);  //换满一个弹夹
		BackpackAmmunitionSum = MaxAmmunitionSum - ClipAmmunitionSum;
	}
	else								
	{
		//如果所有的子弹小于弹夹容量,则应该销毁背包内所有子弹
		DestroyAmmunitionSum = MaxAmmunitionSum - WeaponActorComp->AmmunitionAmount_Now; 
		WeaponActorComp->Reload(MaxAmmunitionSum);   //换不足一个弹夹的子弹量
		MaxAmmunitionSum = 0;
		BackpackAmmunitionSum = 0;
	}
}

//寻找背包内同名的子弹  获取背包内所有子弹数
void AWeaponClass::FindBackpackAmmunitionSum(UBackpackActorComp* BackpackComp)
{
	//初始化背包内子弹数量
	BackpackAmmunitionSum = 0;			
	if(IsValid(BackpackComp))
	{
		for (auto& Target : BackpackComp->BackpackStruct)   
		{
			if (Target.Name == AmmunitionName)
			{
				BackpackAmmunitionSum += Target.Num;		
			}
		}
	}

}

//寻找背包内特定名字的子弹  销毁所需要的子弹数量
void AWeaponClass::FindBackpackDestroyAmmunition(UBackpackActorComp* BackpackComp)
{
	if (IsValid(BackpackComp))
	{
		for (auto& Target : BackpackComp->BackpackStruct)
		{
			//背包内是否有同名子弹
			if (Target.Name == AmmunitionName)			
			{
				//查找背包单个格子的子弹数量是否大于需要销毁的子弹数(DestroyAmmunitionSum=0);
				if (Target.Num > DestroyAmmunitionSum)		
				{
					//单个格子子弹数大于需要销毁的子弹数  则背包格子弹数直接减去需要销毁的子弹即可  需要销毁的子弹数赋为0
					Target.Num -= DestroyAmmunitionSum;
					DestroyAmmunitionSum = 0;
				}
				else									
				{
					//若单个背包格子弹数小于需要销毁的子弹  则吧背包格初始化  所需要销毁的子弹数等于减去背包格子弹数
					DestroyAmmunitionSum -= Target.Num;
					Target = BackpackComp->EmptyItem;			
				}
			}
			if (DestroyAmmunitionSum == 0) break;		//如果所需销毁的子弹数销毁完  退出遍历
		}
	}
	
}



