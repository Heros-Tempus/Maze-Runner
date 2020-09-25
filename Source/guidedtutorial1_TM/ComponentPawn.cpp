// Fill out your copyright notice in the Description page of Project Settings.

#include "ComponentPawn.h"
#include "Components/InputComponent.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "ConstructorHelpers.h"
#include "MyPawnMovementComponent.h"

/*
To control pawn movement through components, first a movement component is created
then the movement component is attached to the pawn
once the component is attached, inputs are bound like they would be on a player

~~in the movement component~~
during each tick of the tick component on the movement component, first the movement component checks if everything is valid and that movement is allowed
then it gets and clears the movement
then it tries to move if the input is not near 0
if the movement is blocked, then it tries to slide along the blocking surface
*/

// Sets default values
AComponentPawn::AComponentPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//creates the sphere component to serve as the root component
	USphereComponent* SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("RootComponent"));
	RootComponent = SphereComponent;
	SphereComponent->InitSphereRadius(40.0f);
	SphereComponent->SetCollisionProfileName(TEXT("Pawn"));

	//creates a sphere static mesh and attatches it to the root component so that the pawn can be seen
	UStaticMeshComponent* SphereMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Visual"));
	SphereMesh->SetupAttachment(RootComponent);
	static ConstructorHelpers::FObjectFinder<UStaticMesh>SphereMeshlComponent(TEXT("/Game/StarterContent/Shapes/Shape_Sphere.Shape_Sphere"));
	if (SphereMeshlComponent.Succeeded())
	{
		SphereMesh->SetStaticMesh(SphereMeshlComponent.Object);
		SphereMesh->SetRelativeLocation(FVector(0.0f, 0.0f, -40.0f));
		SphereMesh->SetWorldScale3D(FVector(0.8f));
	}

	//Set the pawn to be possesed by the player at index 0 (aka player one)
	AutoPossessPlayer = EAutoReceiveInput::Player0;

	//Attaches a custom movement component so that the pawn can move
	PlayerCharacterMovementComponent = CreateDefaultSubobject<UMyPawnMovementComponent>(TEXT("CustomMovements"));
	PlayerCharacterMovementComponent->UpdatedComponent = RootComponent;
}

// Called when the game starts or when spawned
void AComponentPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AComponentPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AComponentPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//Binds the input axis 'Lateral' to the function of the same name
	InputComponent->BindAxis("Lateral", this, &AComponentPawn::Lateral);

	//Binds the input axis 'SidetoSide' to the function of the same name
	InputComponent->BindAxis("SidetoSide", this, &AComponentPawn::SidetoSide);
}

//Called to move the pawn forward or backward
void AComponentPawn::Lateral(float Value)
{
	if (PlayerCharacterMovementComponent && (PlayerCharacterMovementComponent->UpdatedComponent == RootComponent))
	{
		PlayerCharacterMovementComponent->AddInputVector(GetActorForwardVector() * Value);
	}
}

//Called to move the pawn side to side
void AComponentPawn::SidetoSide(float Value)
{
	if (PlayerCharacterMovementComponent && (PlayerCharacterMovementComponent->UpdatedComponent == RootComponent))
	{
		PlayerCharacterMovementComponent->AddInputVector(GetActorRightVector() * -(Value));
	}
}

//Returns the movement component this pawn is using
UPawnMovementComponent* AComponentPawn::GetMovementComponent() const
{
	return PlayerCharacterMovementComponent;
}
