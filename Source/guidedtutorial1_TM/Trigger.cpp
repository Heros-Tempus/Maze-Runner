// Fill out your copyright notice in the Description page of Project Settings.

#include "Trigger.h"
#include "PlayerCharacter.h"
#include "AIAgentController.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Engine.h"

/*trigger is object with no static mesh and an OnPlayerOverlap event
when the player overlaps this object, a function is called on AIAgentController named SwapPath()
for SwapPath() to work, a value needs to be set on the trigger for the variable PathToSwapFrom
if ClearPath is true then the path associated with the trigger will be flagged as invalid and the AI will not return to it
*/

// Sets default values
ATrigger::ATrigger()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Create root component
	PickupRoot = CreateDefaultSubobject<USceneComponent>(TEXT("PickupRoot"));
	RootComponent = PickupRoot;

	//Make the PickupBox
	PickupBox = CreateDefaultSubobject<UBoxComponent>(TEXT("PickupBox"));
	//set the PickupBox scale
	PickupBox->SetWorldScale3D(FVector(1.0f, 1.0f, 1.0f));
	//turn on overlap events for the pickup box
	PickupBox->SetGenerateOverlapEvents(true);
	//call OnPlayerEnterPickupBox when player overlaps PickupBox
	PickupBox->OnComponentBeginOverlap.AddDynamic(this, &ATrigger::OnPlayerEnterPickupBox);
	//attach PickupBox to PickupRoot
	PickupBox->AttachToComponent(PickupRoot, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
}

// Called when the game starts or when spawned
void ATrigger::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATrigger::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

//On player overlap function
void ATrigger::OnPlayerEnterPickupBox(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	//assumes other actor is player
	APlayerCharacter* Player = Cast<APlayerCharacter>(OtherActor);

	//checks if assumption was accurate
	if (Player != nullptr)
	{//gets all AIAgentControllers
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), AAIAgentController::StaticClass(), AIControllers);
		if (AIControllers.Num() > 0)
		{//if AIAgentControllers were found, then cast to the controller
			for (AActor* AgentController : AIControllers)
			{
				AAIAgentController* Agent = Cast<AAIAgentController>(AgentController);
				if (Agent != nullptr)
				{//if the cast succeeds then call the SwapPath function on AIAgentController
					Agent->SwapPath(PathToSwapFrom, ClearPath);
					//if (GEngine)
						//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("Called ClearPath")));
				}
			}
		}
		Destroy();
	}
}

