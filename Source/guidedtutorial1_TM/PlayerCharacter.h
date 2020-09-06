// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InteractionActor.h"
#include "PlayerCharacter.generated.h"

UCLASS()
class GUIDEDTUTORIAL1_TM_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//Called to add movement to forward vector
	void Lateral(float Value);

	//Called to add movement to right vector
	void SidetoSide(float Value);

	//Called to toggle IsSprinting
	void SprintOn();
	void SprintOff();

	//Used in the movement functions to determine whether the input value should be increased or decreased
	bool IsSprinting = false;

	//current endurance value
	float Endurance = 100.0f;

	//max endurance value
	float MaxEndurance = 100.0f;

	//whether the player is exhausted
	bool Exhausted = false;
	
	//whether the player has won
	bool Win = false;

	//called to check if player can sprint
	void TrySprint();

	//called to interact
	void Interact();

	//called to set/clear the interation terget
	UFUNCTION()
		void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
		void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	//CurrentInteractable is the target of the player's interaction
	class AInteractionActor* CurrentInteractable;
	//PlayerCapsule is a reference to the player's capsule component
	class UCapsuleComponent* PlayerCapsule;

	//Returns the player's exhaustion state
	UFUNCTION(BlueprintPure, Category = "Stamina")
		bool GetExhausted();
	//Returns the player's current stamina
	UFUNCTION(BlueprintPure, Category = "Stamina")
		float GetCurrentStamina();

	//returns win value for use in HUD's game end message
	UFUNCTION(BlueprintPure, Category = "Win State")
		bool GetWinState();

	//sets the win value to true, only called by Pickup if the player collects it
	UFUNCTION()
	void SetWin();

	//used to determine if the level start message should be open
	//the AI controller's ChooseNextWaypoint() function needs to be called at the same time this is set to true for the level to properly begin
	bool Playing = false;

	//returns the value of Playing
	UFUNCTION(BlueprintCallable, Category = "Play Start")
		bool GetPlaying();
	//sets the value of Playing
	UFUNCTION(BlueprintCallable, Category = "Play Start")
		void SetPlaying(bool PlayState);
};
