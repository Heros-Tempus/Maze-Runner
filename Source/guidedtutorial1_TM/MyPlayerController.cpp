// Fill out your copyright notice in the Description page of Project Settings.

#include "MyPlayerController.h"
#include "Blueprint/UserWidget.h"

void AMyPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (wHUD)//check if the asset is assigned in the blueprint
	{
		//create the widget and store it
		MyHUD = CreateWidget<UUserWidget>(this, wHUD);

		//extra check to make sure the pointer holds the widget
		if (MyHUD)
		{
			//add it to the viewport
			MyHUD->AddToViewport();
		}

		//show the cursor
		bShowMouseCursor = true;
	}
}
