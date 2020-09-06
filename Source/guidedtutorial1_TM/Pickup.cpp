// Fill out your copyright notice in the Description page of Project Settings.


#include "Pickup.h"
#include "PlayerCharacter.h"
#include "Agent.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Engine.h"

// Sets default values
APickup::APickup()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//default values for rotation
	PitchValue = 0.0f;
	YawValue = 0.0f;
	RollValue = 0.0f;

	//Create root component
	PickupRoot = CreateDefaultSubobject<USceneComponent>(TEXT("PickupRoot"));
	RootComponent = PickupRoot;

	//Create static mesh component
	PickupMesh = CreateDefaultSubobject <UStaticMeshComponent>(TEXT("PickupMesh"));
	//attach mesh to root component
	PickupMesh->AttachToComponent(PickupRoot, FAttachmentTransformRules::SnapToTargetNotIncludingScale);

	//Make the PickupBox
	PickupBox = CreateDefaultSubobject<UBoxComponent>(TEXT("PickupBox"));
	//set the PickupBox scale
	PickupBox->SetWorldScale3D(FVector(1.0f, 1.0f, 1.0f));
	//turn on overlap events for the pickup box
	PickupBox->SetGenerateOverlapEvents(true);
	//call OnPlayerEnterPickupBox when player overlaps PickupBox
	PickupBox->OnComponentBeginOverlap.AddDynamic(this, &APickup::OnPlayerEnterPickupBox);
	//attach PickupBox to PickupRoot
	PickupBox->AttachToComponent(PickupRoot, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
}
// Called when the game starts or when spawned
void APickup::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APickup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//rotate based on the variables PitchValue, YawValue, RollValue
	FRotator NewRotation = FRotator(PitchValue, YawValue, RollValue);
	FQuat QuatRotation = FQuat(NewRotation);
	AddActorLocalRotation(QuatRotation, false, 0, ETeleportType::None);
}

void APickup::OnPlayerEnterPickupBox(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	//assumes other actor is player
		APlayerCharacter* Player = Cast<APlayerCharacter>(OtherActor);

		//checks if assumption was accurate
		if (Player != nullptr)
		{
			//add script for pickup behavior
			//or call function on Player
			//if (GEngine)
				//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("Player Wins")));
			//declares the player the winner
			Player->SetWin();
			//Destroy after collected
			Destroy();
		}
		else
		{
			AAgent* Agent = Cast<AAgent>(OtherActor);
			if (Agent != nullptr)
			{
				//add script for pickup behavior
				//or call function on Agent
				//if (GEngine)
					//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("AI Wins")));
				//Destroy after collected
				Destroy();
			}
		}
}

