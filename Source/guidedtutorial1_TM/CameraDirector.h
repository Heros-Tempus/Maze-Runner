// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CameraDirector.generated.h"

UCLASS()
class GUIDEDTUTORIAL1_TM_API ACameraDirector : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACameraDirector();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//A player controller to be used CameraDirector
	APlayerController* OurPlayerController;

	//Called to swap the view target to CameraOne
	//void SwapToCameraOne();

	//Called to swap the view target to CameraTwo
	//void SwapToCameraTwo();

	//adds a property to the CameraDirector class to specify CameraOne
	//This value is set in the UE Editor
	//UPROPERTY(EditAnywhere)
	//	AActor* CameraOne;

	//adds a property to the CameraDirector class to specify CameraOne
	//This value is set in the UE Editor
	//UPROPERTY(EditAnywhere)
	//	AActor* CameraTwo;

	//Used in the code in the tick function which automatically swaps between cameras [currently commented out]
	//float CameraSwitchTime;
};
