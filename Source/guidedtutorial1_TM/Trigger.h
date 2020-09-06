// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Trigger.generated.h"

UCLASS()
class GUIDEDTUTORIAL1_TM_API ATrigger : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATrigger();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY()
		TArray<AActor*> AIControllers;

	//Root Component
	UPROPERTY(EditAnywhere)
		USceneComponent* PickupRoot;

	//Box for detecting player overlap
	UPROPERTY(EditAnywhere)
		class UShapeComponent* PickupBox;

	UPROPERTY(EditAnywhere)
		int PathToSwapFrom;
	UPROPERTY(EditAnywhere)
		bool ClearPath;

	//On player overlap function
	UFUNCTION()
		void OnPlayerEnterPickupBox(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
