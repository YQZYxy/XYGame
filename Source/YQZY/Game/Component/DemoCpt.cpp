#include "DemoCpt.h"
#include "ProjectileAct.h"
#include "YQZYLog.h"

#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "Net/UnrealNetwork.h"
#include "Engine/Engine.h"



#include UE_INLINE_GENERATED_CPP_BY_NAME(DemoCpt)

ADemoCpt::ADemoCpt()
{
	m_MaxHealth = 100.0f;
	m_CurrentHealth = m_MaxHealth;

	ProjectileClass = AProjectileAct::StaticClass();
	m_FireRate = 0.25f;
	m_bIsFiringWeapon = false;
}



//////////////////////////////////////////////////////////////////////////
// 复制的属性

void ADemoCpt::GetLifetimeReplicatedProps(TArray <FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	//Replicate current health.
	DOREPLIFETIME(ADemoCpt, m_CurrentHealth);
}

void ADemoCpt::OnHealthUpdate()
{
	if (IsLocallyControlled())
	{
		FString healthMessage = FString::Printf(TEXT("You now have %f health remaining."), m_CurrentHealth);
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, healthMessage);

		if (m_CurrentHealth <= 0)
		{
			FString deathMessage = FString::Printf(TEXT("You have been killed."));
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, deathMessage);
			Destroy();
		}
	}

	if (GetLocalRole() == ROLE_Authority)
	{
		FString healthMessage = FString::Printf(TEXT("%s now has %f health remaining."), *GetFName().ToString(), m_CurrentHealth);
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, healthMessage);
	}

	//都执行。
	/*
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AttributeSetBase->GetHealthAttribute()).AddUObject(this, &AGDPlayerState::HealthChanged);
	virtual void HealthChanged(const FOnAttributeChangeData& Data);
		
	*/
}

void ADemoCpt::OnRep_CurrentHealth()
{
	OnHealthUpdate();
}

void ADemoCpt::SetCurrentHealth(float healthValue)
{
	if (GetLocalRole() == ROLE_Authority)
	{
		m_CurrentHealth = FMath::Clamp(healthValue, 0.f, m_MaxHealth);
		OnHealthUpdate();
	}
}

float ADemoCpt::TakeDamage(float DamageTaken, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float damageApplied = m_CurrentHealth - DamageTaken;
	SetCurrentHealth(damageApplied);
	return damageApplied;
}

void ADemoCpt::StartFire()
{
	if (!m_bIsFiringWeapon)
	{
		m_bIsFiringWeapon = true;
		UWorld* World = GetWorld();
		//World->GetTimerManager().SetTimer(m_FiringTimer, this, &ADemoCpt::StopFire, m_FireRate, false);
		SET_TIMER(m_FiringTimer,&ADemoCpt::StopFire,m_FireRate);
		HandleFire();

	}
}

void ADemoCpt::StopFire()
{
	m_bIsFiringWeapon = false;
}

void ADemoCpt::HandleFire_Implementation()
{
	FVector spawnLocation = GetActorLocation() + (GetActorRotation().Vector() * 100.0f) + (GetActorUpVector() * 50.0f);
	FRotator spawnRotation = GetActorRotation();

	FActorSpawnParameters spawnParameters;
	spawnParameters.Instigator = GetInstigator();
	spawnParameters.Owner = this;

	AProjectileAct* spawnedProjectile = GetWorld()->SpawnActor<AProjectileAct>(ProjectileClass, spawnLocation, spawnRotation, spawnParameters);
}