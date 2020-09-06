// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "ComponentPawn.generated.h"

UCLASS()
class GUIDEDTUTORIAL1_TM_API AComponentPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AComponentPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//creates a movement component so the pawn can move
	class UMyPawnMovementComponent *PlayerCharacterMovementComponent;

	//Returns the movement component this pawn is using
	virtual UPawnMovementComponent *GetMovementComponent() const override;

	//called to move the pawn
	void Lateral(float Value);
	void SidetoSide(float Value);

};
