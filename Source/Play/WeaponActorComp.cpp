// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponActorComp.h"
#include "Kismet/GameplayStatics.h"
#include "Engine\Classes\Particles\ParticleSystemComponent.h"
#include "TimerManager.h"



// Sets default values for this component's properties
UWeaponActorComp::UWeaponActorComp()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	FireOfSpeed = 400.0f;  //默认每分钟的开火速率
	bShouldFire = false;    //默认不可以开火
	bParticleIsValid = false;   //开始粒子组件无效


	//武器骨骼插槽
	MuzzleFlashSocket = "MuzzleFlashSocket";
	BulletShellSocket = "BulletShellSocket";


	//Projectile = Class ;
	//AFPSProjectShell* ProjectShell;
}


// Called when the game starts
void UWeaponActorComp::BeginPlay()
{
	Super::BeginPlay();
	
}


// Called every frame
void UWeaponActorComp::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UWeaponActorComp::FireButtonPressed()
{
	bFirePressed = true;
	if (bShouldFire)
	{
		TimerDelegate();
	}
}

void UWeaponActorComp::FireButtonReleased()
{
	bFirePressed = false;
	StopFire(); //清除定时器句柄停止开火时的附带粒子等效果
}

//定时器控制开火时射速
void UWeaponActorComp::TimerDelegate()
{
	if (bShouldFire)
	{
		Fire();	

		float  LastFireTime;   //记录开始开火的时间
		float  TimeBetweenShots = 60 / FireOfSpeed;  //获取到开火时间间隔
		LastFireTime = GetWorld()->TimeSeconds;  //其中LastFireTime应当在武器开火函数结束后获取当前时间进行赋值：
		float  FirstDelay = FMath::Max(LastFireTime + TimeBetweenShots - GetWorld()->TimeSeconds, 0.0f);

		GetWorld()->GetTimerManager().SetTimer(InOutHandle, this, &UWeaponActorComp::AutoFire, TimeBetweenShots, false, FirstDelay);
	}
}

void UWeaponActorComp::Fire()
{
	if (bShouldFire)  //开火状态
	{
		bAmmunitionEnd = AmmunitionAmount_Now > 0;
		if (bAmmunitionEnd)	//弹药是否耗尽
		{
			bool isAssetsQuote = IsValid(WeaponMesh) && IsValid(Projectile) && IsValid(ProjectShell);  //资产是否引用
			if (isAssetsQuote)
			{
				//开火一次,子弹减 1 
				AmmunitionAmount_Now--;

				//播放枪声

				//从武器骨骼枪口插槽发射子弹
				FActorSpawnParameters SpawnParameters;
				SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
				FTransform MuzzleSocketTransform = WeaponMesh->GetSocketTransform(MuzzleFlashSocket, RTS_World);

				AFPSProjectile * ProjectileTest = GetWorld()->SpawnActor<AFPSProjectile>(Projectile, MuzzleSocketTransform.GetLocation(), MuzzleSocketTransform.GetRotation().Rotator(), SpawnParameters);

				//设置子弹伤害
				ProjectileTest->BaseDamage = Damage;  

				//从武器骨骼弹壳插槽抛出弹壳
				FTransform BulletShellSocketTransform = WeaponMesh->GetSocketTransform(BulletShellSocket, RTS_World);

				GetWorld()->SpawnActor<AFPSProjectShell>(ProjectShell, BulletShellSocketTransform.GetLocation(), BulletShellSocketTransform.GetRotation().Rotator(), SpawnParameters);

				//生成粒子
				if (!bParticleIsValid)
				{
					FVector WeaponMeshScale = WeaponMesh->GetComponentScale();

					MuzzleParticleComp = UGameplayStatics::SpawnEmitterAttached(MuzzleFX, WeaponMesh, FName(""), MuzzleSocketTransform.GetLocation(), MuzzleSocketTransform.GetRotation().Rotator(), WeaponMeshScale, EAttachLocation::KeepWorldPosition, false, EPSCPoolMethod::None, true);

					bParticleIsValid = true;
				}
				//MuzzleComp->bAutoDestroy = false; //如果希望 DeactivateSystem 之后，再次开启 ActivateSystem 的时候能自动激活特效，需要禁用自动销毁：
				//MuzzleComp->ActivateSystem(true);  //启动粒子ActivateSystem的bool参数表示开启特效后是否重置特效（从头播放）
				//MuzzleComp->DeactivateSystem(); //关闭粒子
				
			}
			else
			{
				GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("资产没引用"));
			}					
		}
		else
		{
			//停止开火
			bShouldFire = false;
			//卸载粒子组件
			if (IsValid(MuzzleParticleComp))
			{
				MuzzleParticleComp->DestroyComponent();
				bParticleIsValid = false;	
			}
		}

	}
	
}
//循环调用  全自动开火
void UWeaponActorComp::AutoFire()
{
	if (bFirePressed && bShouldFire)
	{
		TimerDelegate();
	}
}
//换弹
void UWeaponActorComp::Reload(int ReloadAmmo)
{
	AmmunitionAmount_Now = ReloadAmmo;
	//bShouldFire = true;
}

//停止开火
void UWeaponActorComp::StopFire()
{
	GetWorld()->GetTimerManager().ClearTimer(InOutHandle);
	//卸载粒子组件
	if (IsValid(MuzzleParticleComp))
	{
		MuzzleParticleComp->DestroyComponent();
		bParticleIsValid = false;
	}

}

void UWeaponActorComp::SetAmmunitionDamage(int WeaponDamage)
{
	if (WeaponDamage >= 0)
	{
		if(WeaponDamage != 0)
		{
			Damage= WeaponDamage;
		}
	}
}
