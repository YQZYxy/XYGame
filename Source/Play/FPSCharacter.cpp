// Fill out your copyright notice in the Description page of Project Settings.

#include "FPSCharacter.h"
#include "Components/SkeletalMeshComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "BackpackUI.h"
#include "InteractInterface.h"
#include "Engine/World.h"

// Sets default values
AFPSCharacter::AFPSCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CharacterHandMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterHandMesh"));
	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComp"));

	CameraComp->SetupAttachment(RootComponent);
	CharacterHandMesh->SetupAttachment(CameraComp);

	// 启用Pawn控制摄像机旋转。
	CameraComp->bUsePawnControlRotation = true;

	// 仅所属玩家可以看见此网格体。
	CharacterHandMesh->SetOnlyOwnerSee(true);

	// 禁用某些环境阴影以便实现只有单个网格体的感觉。
	CharacterHandMesh->bCastDynamicShadow = false;
	CharacterHandMesh->CastShadow = false;

	// 所属玩家看不到常规（第三人称）全身网格体。
	GetMesh()->SetOwnerNoSee(true);
	
	//左手骨骼插槽名字
	LeftSocketName = "Weapons";

	//默认初始体力
	HP = 100;
	MaxHP = 100;
	//默认初始能量
	EP = 100;
	MaxEP = 100;

	//默认关闭  射线检测开关标志
	LineTraceOnOff = false;
}

// Called when the game starts or when spawned
void AFPSCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	GetWorldTimerManager().SetTimer(EPTimerHandle, this, &AFPSCharacter::EPFunction, 1, true);
	
}
 
// Called every frame
void AFPSCharacter::Tick(float DeltaTime)
{
	
	Super::Tick(DeltaTime);

	if (LineTraceOnOff)
	{
		CreateLineTreaByChannel();  //开启射线
		if (HitResult.bBlockingHit)
		{
			if (HitResult.GetActor())
			{
				//UKismetSystemLibrary::PrintString(GetWorld(), HitResult.GetActor()->GetName());  //显示射线检测物品名称	
				if (Interface != nullptr)
				{
					//射线检测场景物品信息
					Interface->Execute_OnFocusEvent(HitResult.GetActor());
					//UKismetSystemLibrary::PrintString(GetWorld(), HitResult.GetActor()->GetName());  //显示射线检测物品名称	
				}
				else
				{
					Interface = Cast<IInteractInterface>(HitResult.Actor);
				}
			}
		}
		else
		{
			//Interface = nullptr;
		}
	}

}

// Called to bind functionality to input
void AFPSCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	//前后左右移动方向
	PlayerInputComponent->BindAxis("MoveForward", this, &AFPSCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AFPSCharacter::MoveRight);
	//上下左右视角
	PlayerInputComponent->BindAxis("LookRight", this, &AFPSCharacter::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &AFPSCharacter::AddControllerPitchInput);
	//跳跃
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AFPSCharacter::StartJump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &AFPSCharacter::StopJump);
	////左键状态
	//PlayerInputComponent->BindAction("MouseLeft", IE_Pressed, this, &AFPSCharacter::LeftMouseButtonPressed);
	//PlayerInputComponent->BindAction("MouseLeft", IE_Released, this, &AFPSCharacter::LeftMouseButtonReleased);
	//E 键状态
	PlayerInputComponent->BindAction("E_Button", IE_Pressed, this, &AFPSCharacter::E_ButtonPressed);
	//F 键状态
	PlayerInputComponent->BindAction("F_Button", IE_Pressed, this, &AFPSCharacter::F_ButtonPressed);
	//Esc 键状态
	PlayerInputComponent->BindAction("Esc_Button", IE_Pressed, this, &AFPSCharacter::Esc_ButtonPressed);

}

//受到伤害时调用
float AFPSCharacter::TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	if (HP>=0)
	{
		HP -= Damage;
		ReceiveDamage = Damage;
		//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue,ToString(Damage));
		if (HP<=0)
		{
			HP = 0;
			//在蓝图调用角色死亡后事件
			CharacterDieEvent();  
		}
	}
	return Damage;
}

void AFPSCharacter::MoveForward(float Value)
{
	// 找出"前进"方向 设置玩家移动
	FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::X);
	AddMovementInput(Direction, Value);
}

void AFPSCharacter::MoveRight(float Value)
{
	// 找出"右侧"方向 设置玩家移动
	FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::Y);
	AddMovementInput(Direction, Value);
}

void AFPSCharacter::StartJump()
{
	bPressedJump = true;
}

void AFPSCharacter::StopJump()
{
	bPressedJump = false;
}

//射线检测
FHitResult AFPSCharacter::CreateLineTreaByChannel()
{	
	FVector BeginLoc = GetWorld()->GetFirstPlayerController()->PlayerCameraManager->GetCameraLocation(); //射线生成时开始的位置
	FVector EndLoc = BeginLoc + CameraComp->GetForwardVector() * 300.0f;  //射线结束位置

	//射线检测碰撞参数
	FCollisionQueryParams CollisonQueryParams(TEXT("QueryParams"), true, NULL);
	CollisonQueryParams.bTraceComplex = true;
	CollisonQueryParams.bReturnPhysicalMaterial = false;
	CollisonQueryParams.AddIgnoredActor(this);

	//可拾取物碰撞持续射线检测
	bIsHit = GetWorld()->LineTraceSingleByChannel(HitResult, BeginLoc, EndLoc, PickupChannel, CollisonQueryParams);  

	UKismetSystemLibrary::DrawDebugLine(GetWorld(), BeginLoc, HitResult.GetActor() ? HitResult.Location : EndLoc, FColor::Red, 0.1f, 1.0f);  //绘画射线

	

	if (!bIsHit)
	{
		//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("未命中"));
		//UKismetSystemLibrary::PrintString(GetWorld(), HitResult.GetActor()->GetName());  //显示射线检测物品名称
		
		//场景交互射线检测
		bIsHit = GetWorld()->LineTraceSingleByChannel(HitResult, BeginLoc, EndLoc, InteractChannel, CollisonQueryParams);  

		
	}
	return HitResult;
	
}


//E 键按下事件,  ***蓝图已经覆盖
void AFPSCharacter::E_ButtonPressed()
{
	//PickUpWeapon();

	isPickUp = true;
		//接口不为空时给接口Actor通信
	if (HitResult.GetActor())
	{
		if (Interface)
		{

			Interface->Execute_OnPickUpEvent(HitResult.GetActor());
		}
	}

}

//F 键按下事件  ***蓝图已经覆盖
void AFPSCharacter::F_ButtonPressed()
{
	//接口不为空时给接口Actor通信
	if (HitResult.GetActor())
	{
		if (Interface)
		{
			Interface->Execute_OnInteractEvent(HitResult.GetActor());
		}
	}
}

//Esc 按下  在FPS_HUD绑定按下时调用菜单界面UI
void AFPSCharacter::Esc_ButtonPressed()
{
	EscClickDelegate.Broadcast();
}

//血条
void AFPSCharacter::HPFunction(int ConsumeHP)
{
	HP -= ConsumeHP;

}
//体力条
void AFPSCharacter::EPFunction()
{
	
	if (EP>=MaxEP)
	{
		EP = MaxEP;
	}
	else
	{
		EP += EPRecover;
	}
	isEPFunctionEnd = true;
	//GetWorld()->TimeSeconds;
	isEPFunctionEnd = false;
}

//拾取武器
void AFPSCharacter::PickUpWeapon()
{
	if (IsValid(HitResult.GetActor()))
	{
		if (HitResult.GetActor()->GetClass() == WeaponClass)
		{
			////射线检测接口有效,则向Actor发送信息
			//IInteractInterface* ActorCheck = Cast<IInteractInterface>(HitResult.GetActor());
			//if (ActorCheck)
			//{
			//	ActorCheck->OnInteract();
			//}

			//生成检测碰撞的武器Actor
			//FActorSpawnParameters SpawnParams;
			//SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
			//Weapon = GetWorld()->SpawnActor<AWeaponClass>(WeaponClass, FVector(1.0), FRotator(1.0), SpawnParams);

			//Weapon->WeaponActorComp->Damage = Cast<AWeaponClass>(HitResult.GetActor()->GetClass())->WeaponActorComp->Damage;
			 
			Weapon = Cast<AWeaponClass>(HitResult.GetActor());
			//武器生成则附加到骨骼插槽上
			if (IsValid(Weapon))
			{
				isPickUpWeapon = true;  //已经获取武器

				Weapon->SetActorEnableCollision(false);   //关闭武器物理碰撞
				FAttachmentTransformRules AttachmentTransformRules = FAttachmentTransformRules::SnapToTargetIncludingScale;
				AttachmentTransformRules.bWeldSimulatedBodies = true;
				Weapon->AttachToComponent(CharacterHandMesh, AttachmentTransformRules, LeftSocketName);

				Weapon->WeaponActorComp->WeaponMesh = Weapon->WeaponMesh;   //把生成的武器骨骼网络体赋给武器行为组件骨骼网络体,以便在武器组件访问生成武器的骨骼网络体插槽,实现弹药,弹壳等生成位置
			}

		}
	}
}

