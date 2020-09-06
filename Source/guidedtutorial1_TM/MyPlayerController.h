// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MyPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class GUIDEDTUTORIAL1_TM_API AMyPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:

	//reference UMG Asset in the editor
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widgets")
		TSubclassOf<class UUserWidget> wHUD;

	//variable to hold the widget after creating it
	UUserWidget* MyHUD;

	//Override BeginPlay()
	virtual void BeginPlay() override;
};
