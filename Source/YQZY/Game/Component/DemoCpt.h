#pragma once

#include "CoreMinimal.h"
#include "Character/YQZYCharacter.h"
#include "DemoCpt.generated.h"

UCLASS(config = Game)
class YQZY_API ADemoCpt : public AYQZYCharacter
{
	GENERATED_BODY()

public:
	// 设置此 empty 属性的默认值
	ADemoCpt();

protected:

public:

	/** 属性复制 */
	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

protected:

	/** 玩家的最大生命值。这是玩家的最高生命值，也是出生时的生命值。*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
	float m_MaxHealth;

	/** 玩家的当前生命值。降到0就表示死亡。*/
	UPROPERTY(ReplicatedUsing = OnRep_CurrentHealth)
	float m_CurrentHealth;

	/** RepNotify，用于同步对当前生命值所做的更改。*/
	UFUNCTION()
	void OnRep_CurrentHealth();

	/** 响应要更新的生命值。修改后，立即在服务器上调用，并在客户端上调用以响应RepNotify*/
	void OnHealthUpdate();

public:

	/** 最大生命值的取值函数。*/
	UFUNCTION(BlueprintPure, Category = "Health")
	FORCEINLINE float GetMaxHealth() const { return m_MaxHealth; }

	/** 当前生命值的取值函数。*/
	UFUNCTION(BlueprintPure, Category = "Health")
	FORCEINLINE float GetCurrentHealth() const { return m_CurrentHealth; }

	/** 当前生命值的存值函数。将此值的范围限定在0到MaxHealth之间，并调用OnHealthUpdate。仅在服务器上调用。*/
	UFUNCTION(BlueprintCallable, Category = "Health")
	void SetCurrentHealth(float healthValue);

	/** 承受伤害的事件。从APawn重载。*/
	UFUNCTION(BlueprintCallable, Category = "Health")
	float TakeDamage(float DamageTaken, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay|Projectile")
	TSubclassOf<class AProjectileAct> ProjectileClass;

	/** 射击之间的延迟，单位为秒。用于控制测试发射物的射击速度，还可防止服务器函数的溢出导致将SpawnProjectile直接绑定至输入。*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay")
	float m_FireRate;

	/** 若为true，此武器正在发射过程中。*/
	bool m_bIsFiringWeapon;

	/** 用于启动武器发射的函数。应仅可由本地玩家触发。*/
	UFUNCTION(BlueprintCallable, Category = "Gameplay")
	void StartFire();

	/** 用于结束武器射击的函数。一旦调用这段代码，玩家可再次使用StartFire。*/
	UFUNCTION(BlueprintCallable, Category = "Gameplay")
	void StopFire();

	/** 用于生成投射物的服务器函数。*/
	UFUNCTION(Server, Reliable)
	void HandleFire();

	/** 定时器句柄，用于提供生成间隔时间内的射速延迟。*/
	FTimerHandle m_FiringTimer;
};
