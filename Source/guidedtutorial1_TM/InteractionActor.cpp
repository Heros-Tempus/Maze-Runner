// Fill out your copyright notice in the Description page of Project Settings.

#include "InteractionActor.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Engine.h"

// Sets default values
AInteractionActor::AInteractionActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Create root component
	InteractRoot = CreateDefaultSubobject<USceneComponent>(TEXT("PickupRoot"));
	RootComponent = InteractRoot;

	//Create static mesh component
	InteractMesh = CreateDefaultSubobject <UStaticMeshComponent>(TEXT("InteractMesh"));
	//attach mesh to root component
	InteractMesh->AttachToComponent(InteractRoot, FAttachmentTransformRules::SnapToTargetNotIncludingScale);

	//Create box component
	InteractBox = CreateDefaultSubobject<UBoxComponent>(TEXT("InteractBoxComponent"));
	//Set default box scale
	InteractBox->SetWorldScale3D(FVector(1.0f, 1.0f, 1.0f));
	//attach PickupBox to PickupRoot
	InteractBox->AttachToComponent(InteractRoot, FAttachmentTransformRules::SnapToTargetNotIncludingScale);

	//default values for rotation
	PitchValue = 0.0f;
	YawValue = 0.0f;
	RollValue = 0.0f;
}

// Called when the game starts or when spawned
void AInteractionActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AInteractionActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//rotate based on the variables PitchValue, YawValue, RollValue
	FRotator NewRotation = FRotator(PitchValue, YawValue, RollValue);
	FQuat QuatRotation = FQuat(NewRotation);
	AddActorLocalRotation(QuatRotation, false, 0, ETeleportType::None);

	//slow down over time
	if (PitchValue > 0.0f)
		PitchValue -= DeltaTime;
	if (YawValue > 0.0f)
		YawValue -= DeltaTime;
	if (RollValue > 0.0f)
		RollValue -= DeltaTime;

	if (PitchValue < 0.0f)
		PitchValue = 0.0f;
	if (YawValue < 0.0f)
		YawValue = 0.0f;
	if (RollValue < 0.0f)
		RollValue = 0.0f;
}

//called by the PlayerCharacter
void AInteractionActor::Interact()
{
	if (GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("Interact")));

	YawValue += 1;
}

