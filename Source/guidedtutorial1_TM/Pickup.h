// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Pickup.generated.h"

UCLASS()
class GUIDEDTUTORIAL1_TM_API APickup : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APickup();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//Root Component
	UPROPERTY(EditAnywhere)
		USceneComponent* PickupRoot;

	//Static mesh
	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* PickupMesh;

	//Box for detecting player overlap
	UPROPERTY(EditAnywhere)
	 class UShapeComponent* PickupBox;

	//Rotation values
	UPROPERTY(EditAnywhere, Category = "Movement")
		float PitchValue;
	UPROPERTY(EditAnywhere, Category = "Movement")
		float YawValue;
	UPROPERTY(EditAnywhere, Category = "Movement")
		float RollValue;

	//On player overlap function
	UFUNCTION()
		void OnPlayerEnterPickupBox(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
