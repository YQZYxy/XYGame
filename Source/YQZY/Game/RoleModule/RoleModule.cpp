// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/RoleModule/RoleModule.h"
#include "YQZYLog.h"
#include "Components/CapsuleComponent.h"

ARoleModule::ARoleModule()
{
	UCapsuleComponent* CapsuleComp = GetCapsuleComponent();
	check(CapsuleComp);
	CapsuleComp->OnComponentBeginOverlap.AddDynamic(this, &ARoleModule::BeginOverlap);

}

void ARoleModule::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepHitResult)
{
	if (OtherActor)
	{
		YQZYWarning("%s", *OtherActor->GetName());
	}
}
