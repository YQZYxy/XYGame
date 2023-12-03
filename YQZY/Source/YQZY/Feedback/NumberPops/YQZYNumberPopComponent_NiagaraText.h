// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "YQZYNumberPopComponent.h"

#include "YQZYNumberPopComponent_NiagaraText.generated.h"

class UYQZYDamagePopStyleNiagara;
class UNiagaraComponent;
class UObject;

UCLASS(Blueprintable)
class UYQZYNumberPopComponent_NiagaraText : public UYQZYNumberPopComponent
{
	GENERATED_BODY()

public:

	UYQZYNumberPopComponent_NiagaraText(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	//~UYQZYNumberPopComponent interface
	virtual void AddNumberPop(const FYQZYNumberPopRequest& NewRequest) override;
	//~End of UYQZYNumberPopComponent interface

protected:
	
	TArray<int32> DamageNumberArray;

	/** Style patterns to attempt to apply to the incoming number pops */
	UPROPERTY(EditDefaultsOnly, Category = "Number Pop|Style")
	TObjectPtr<UYQZYDamagePopStyleNiagara> Style;

	//Niagara Component used to display the damage
	UPROPERTY(EditDefaultsOnly, Category = "Number Pop|Style")
	TObjectPtr<UNiagaraComponent> NiagaraComp;
};
