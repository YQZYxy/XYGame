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
	/** 属性复制 */
	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UFUNCTION(BlueprintCallable, Category = "Health")
	float TakeDamage(float DamageTaken, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
	float m_MaxHealth;

	UPROPERTY(ReplicatedUsing = OnRep_CurrentHealth)
	float m_CurrentHealth;

	/** RepNotify*/
	UFUNCTION()
	void OnRep_CurrentHealth();

	/** 修改后，立即在服务器上调用，并在客户端上调用以响应RepNotify*/
	void OnHealthUpdate();

public:

	UFUNCTION(BlueprintPure, Category = "Health")
	FORCEINLINE float GetMaxHealth() const { return m_MaxHealth; }

	UFUNCTION(BlueprintPure, Category = "Health")
	FORCEINLINE float GetCurrentHealth() const { return m_CurrentHealth; }

	/**仅在服务器上调用。*/
	UFUNCTION(BlueprintCallable, Category = "Health")
	void SetCurrentHealth(float healthValue);


protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay|Projectile")
	TSubclassOf<class AProjectileAct> ProjectileClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay")
	float m_FireRate;

	bool m_bIsFiringWeapon;

	/** 应仅可由本地触发。*/
	UFUNCTION(BlueprintCallable, Category = "Gameplay")
	void StartFire();

	UFUNCTION(BlueprintCallable, Category = "Gameplay")
	void StopFire();

	/** 服务器函数。*/
	UFUNCTION(Server, Reliable)
	void HandleFire();

	/** 定时器句柄。*/
	FTimerHandle m_FiringTimer;
};
