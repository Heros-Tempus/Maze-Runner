// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InteractionActor.generated.h"

UCLASS()
class GUIDEDTUTORIAL1_TM_API AInteractionActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AInteractionActor();
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//Rotation values
	UPROPERTY(EditAnywhere, Category = Movment)
		float PitchValue;
	UPROPERTY(EditAnywhere, Category = Movment)
		float YawValue;
	UPROPERTY(EditAnywhere, Category = Movment)
		float RollValue;

	//Root Component
	UPROPERTY(EditAnywhere)
		USceneComponent* InteractRoot;
	//Static mesh
	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* InteractMesh;
	//Box component
	UPROPERTY(EditAnywhere)
		class UBoxComponent* InteractBox;

	//called by the PlayerCharacter
	UFUNCTION(BlueprintCallable, Category = "Button Press")
		void Interact();

};
