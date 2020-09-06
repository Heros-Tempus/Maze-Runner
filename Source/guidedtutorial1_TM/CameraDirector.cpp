// Fill out your copyright notice in the Description page of Project Settings.

#include "CameraDirector.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"

/*
Currently only sets the default rotation of the player's camera on begin play
all other functions have been commented out
*/

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

	//sets OurPlayerController equal to the player controller from the first player controller
	OurPlayerController = GetWorld()->GetFirstPlayerController();

	//enables input in OurPlayerController
	EnableInput(OurPlayerController);

	//sets the default rotation of the player camera to a direction conducive to navigating the level
	//the player is still free to rotate the camera afterwards
	APlayerController* OurPlayerController = UGameplayStatics::GetPlayerController(this, 0);
	OurPlayerController->SetControlRotation(FRotator(-80, 180, 0));
	//appends OurPlayerController with two bindings for the actions 'CameraOne - Pressed' and 'CameraTwo - Pressed'
	//which call the functions SwapToCameraOne and SwapToCameraTwo respectively
	//InputComponent->BindAction("CameraOne", IE_Pressed, this, &ACameraDirector::SwapToCameraOne);
	//InputComponent->BindAction("CameraTwo", IE_Pressed, this, &ACameraDirector::SwapToCameraTwo);
}

// Called every frame
void ACameraDirector::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	/*
	Every tick CameraSwitchTime is decreased by DeltaTime
	when CameraSwitchTime hits 0 it is reset to the default value held by TimeBewteenCameraChanges
	then the current view target is checked
	the camera which is not the view target is then set to be the view target
	
	const float TimeBetweenCameraChanges = 5.0f;
	const float SmoothBlendTime = 0.75f;
	CameraSwitchTime -= DeltaTime;
	if (CameraSwitchTime <= 0.0f)
	{
		CameraSwitchTime += TimeBetweenCameraChanges;

		APlayerController* OurPlayerController = UGameplayStatics::GetPlayerController(this, 0);
		if (OurPlayerController)
		{
			if ((OurPlayerController->GetViewTarget() != CameraOne) && (CameraOne != nullptr))
			{
				OurPlayerController->SetViewTarget(CameraOne);
			}
			else if ((OurPlayerController->GetViewTarget() != CameraTwo) && (CameraTwo != nullptr))
			{
				OurPlayerController->SetViewTargetWithBlend(CameraTwo, SmoothBlendTime);
			}
		}
	}*/

}

//Called to swap the view target to CameraOne
/*void ACameraDirector::SwapToCameraOne()
{
	APlayerController* OurPlayerController = UGameplayStatics::GetPlayerController(this, 0);
	OurPlayerController->SetViewTarget(CameraOne);
}

//Called to swap the view target to CameraTwo
void ACameraDirector::SwapToCameraTwo()
{
	APlayerController* OurPlayerController = UGameplayStatics::GetPlayerController(this, 0);
	OurPlayerController->SetViewTarget(CameraTwo);
}
*/
