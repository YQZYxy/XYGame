// Fill out your copyright notice in the Description page of Project Settings.


#include "CameraDirector.h"
#include "Kismet/GameplayStatics.h" 

// Sets default values
ACameraDirector::ACameraDirector()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACameraDirector::BeginPlay()
{
	Super::BeginPlay();

}

//// Called every frame  4.26
//void ACameraDirector::Tick(float DeltaTime)
//{
//	Super::Tick(DeltaTime);
//    const float TimeBetweenCameraChanges = 2.0f;
//    const float SmoothBlendTime = 0.75f;
//    TimeToNextCameraChange -= DeltaTime;
//    if (TimeToNextCameraChange <= 0.0f)
//    {
//        TimeToNextCameraChange += TimeBetweenCameraChanges;
//
//        // 
//        APlayerController* OurPlayerController = UGameplayStatics::GetPlayerController(this, 0);
//        if (OurPlayerController)
//        {
//            if ((OurPlayerController->GetViewTarget() != CameraOne) && (CameraOne != nullptr))
//            {
//                // 
//                OurPlayerController->SetViewTarget(CameraOne);
//            }
//            else if ((OurPlayerController->GetViewTarget() != CameraTwo) && (CameraTwo != nullptr))
//            {
//                //
//                OurPlayerController->SetViewTargetWithBlend(CameraTwo, SmoothBlendTime);
//            }
//        }
//    }
//
//}


// Called every frame 4.27
void ACameraDirector::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

	const float TimeBetweenCameraChanges = 2.0f;
	const float SmoothBlendTime = 0.75;
	TimeToNextCameraChange -= DeltaTime;
	if (TimeToNextCameraChange <= 0.0f)
	{
		TimeToNextCameraChange += TimeBetweenCameraChanges;

		APlayerController* OurPlayerController = UGameplayStatics::GetPlayerController(this, 0);

		if (OurPlayerController)
		{
			if (CameraTwo && (OurPlayerController->GetViewTarget() == CameraOne))
			{
				OurPlayerController->SetViewTargetWithBlend(CameraTwo, SmoothBlendTime);
			}
			else if (CameraOne)
			{
				OurPlayerController->SetViewTarget(CameraOne);
			}
		}

	}
}

