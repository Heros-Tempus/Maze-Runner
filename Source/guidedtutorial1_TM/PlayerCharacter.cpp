// Fill out your copyright notice in the Description page of Project Settings.

/*
*/

#include "PlayerCharacter.h"
#include "GameFramework/Pawn.h"
#include "Components/InputComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "Components/SkeletalMeshComponent.h"
#include "Kismet/GameplayStatics.h" 
#include "GameFramework/CharacterMovementComponent.h"
#include "InteractionActor.h"
#include "Engine.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//get a reference to the player capsule component
	PlayerCapsule = GetCapsuleComponent();
	//binds capsule overlap to OnOverlapBegin
	PlayerCapsule->OnComponentBeginOverlap.AddDynamic(this, &APlayerCharacter::OnOverlapBegin);
	//binds capsule overlap to OnOverlapEnd
	PlayerCapsule->OnComponentEndOverlap.AddDynamic(this, &APlayerCharacter::OnOverlapEnd);
	
	CurrentInteractable = NULL;
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	//hides the head so that it does not obstruct the first person camera
	//GetMesh()->HideBoneByName(FName("Head"), EPhysBodyOp::PBO_None);

}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//if endurance is 0 then set exhausted to true
	if (Endurance <= 0 && !Exhausted)
	{
		IsSprinting = false;
		Exhausted = true;
	}
	//if endurance is less than max then recover endurance
	if (Endurance < MaxEndurance)
	{
		if (Exhausted)
		{
			Endurance += DeltaTime * 3;
			Endurance = FMath::Clamp<float>(Endurance, 0, MaxEndurance);
		}
		else
		{
			Endurance += DeltaTime * 7.5;
			Endurance = FMath::Clamp<float>(Endurance, 0, MaxEndurance);
		}
	}
	//if endurance is greater than half then set exhausted to false
	if (Endurance >= MaxEndurance / 2.0f)
	{
		Exhausted = false;
	}
}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//Binds the functionality of the function 'Lateral' to the axis named 'Lateral'
	PlayerInputComponent->BindAxis("Lateral", this, &APlayerCharacter::Lateral);

	//Binds the functionality of the function 'SidetoSide' to the axis named 'SidetoSide'
	PlayerInputComponent->BindAxis("SidetoSide", this, &APlayerCharacter::SidetoSide);

	//Binds the functionality of the function 'SprintToggle' to the input event 'pressed' on the action named 'Sprint'
	PlayerInputComponent->BindAction("Sprint", IE_Pressed, this, &APlayerCharacter::SprintOn);
	PlayerInputComponent->BindAction("Sprint", IE_Released, this, &APlayerCharacter::SprintOff);

	//Binds the functionality of the AddControllerYawInput to the axis named Turn
	PlayerInputComponent->BindAxis("Turn", this, &APlayerCharacter::AddControllerYawInput);

	//Binds the functionality of the AddControllerPitchInput to the axis named UpDown
	PlayerInputComponent->BindAxis("UpDown", this, &APlayerCharacter::AddControllerPitchInput);

	PlayerInputComponent->BindAction("Interact", IE_Pressed, this, &APlayerCharacter::Interact);
}

//Called to add movement to forward vector
void APlayerCharacter::Lateral(float Value)
{
	if (Playing)
	{
		if (Controller && Value)
			if (IsSprinting)
			{
				TrySprint();
				Value *= 3;
			}

		AddMovementInput(GetActorForwardVector(), Value / 3);
	}

}

//Called to add movement to right vector
void APlayerCharacter::SidetoSide(float Value)
{
	if (Playing)
	{
		if (Controller && Value)
			if (IsSprinting)
			{
				TrySprint();
				Value *= 3;
			}

		AddMovementInput(GetActorRightVector(), Value / 3);
	}
}

//Called to toggle IsSprinting
void APlayerCharacter::SprintOn()
{
	if (Playing)
	{
		if (!Exhausted && Endurance > 0)
			IsSprinting = true;
	}
}
void APlayerCharacter::SprintOff()
{
	if (Playing)
	{
		if (IsSprinting)
			IsSprinting = false;
	}
}

//called to drain sprint if sprinting, or to trigger exhaustion if endurance reaches 0
void APlayerCharacter::TrySprint()
{
	if (!Exhausted)
	{
		Endurance -= 0.2f;
		Endurance = FMath::Clamp<float>(Endurance, 0, MaxEndurance);
	}
}

//called to interact
void APlayerCharacter::Interact()
{//checks if there is a valid interaction target
	if (CurrentInteractable)
		CurrentInteractable->Interact();
}

//called to set the interaction target
void APlayerCharacter::OnOverlapBegin(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if(OtherActor && (OtherActor != this) && OtherComp && OtherActor->GetClass()->IsChildOf(AInteractionActor::StaticClass()))
	{
		CurrentInteractable = Cast<AInteractionActor>(OtherActor);
	}
}

//called to clear the interaction target
void APlayerCharacter::OnOverlapEnd(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor && (OtherActor != this) && OtherComp)
	{
		CurrentInteractable = NULL;
	}
}

//returns exhausted state for use in HUD
bool APlayerCharacter::GetExhausted()
{
	return Exhausted;
}

//returns endurance value for use in HUD
float APlayerCharacter::GetCurrentStamina()
{
	return Endurance;
}

//returns win value for use in HUD's game end message
bool APlayerCharacter::GetWinState()
{
	return Win;
}

//sets the win value to true, only called by Pickup if the player collects it
void APlayerCharacter::SetWin()
{
	Win = true;
}

//returns the value of Playing
bool APlayerCharacter::GetPlaying()
{
	return Playing;
}

//sets the value of Playing
void APlayerCharacter::SetPlaying(bool PlayState)
{
	Playing = PlayState;
}

