


#include "MazeCell.h"
#include "Components/StaticMeshComponent.h"
#include "Components/TextRenderComponent.h"

// Sets default values
AMazeCell::AMazeCell()
{
	RootScene = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = RootScene;

	Floor = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Floor"));
	Floor->SetupAttachment(RootComponent);

	Wall_0 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Wall_0"));
	Wall_0->SetupAttachment(RootComponent);

	Wall_1 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Wall_1"));
	Wall_1->SetupAttachment(RootComponent);

	Wall_2 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Wall_2"));
	Wall_2->SetupAttachment(RootComponent);

	Wall_3 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Wall_3"));
	Wall_3->SetupAttachment(RootComponent);

	DebugText = CreateDefaultSubobject<UTextRenderComponent>(TEXT("DebugText"));
	DebugText->SetupAttachment(RootComponent);
	DebugText->Text = FText::FromString("");

 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void AMazeCell::BeginPlay()
{
	Super::BeginPlay();
	
	NumberWallsUp = 4;
	bCreated = false;

	Floor->SetVisibility(false, true);
	Wall_0->SetVisibility(false, true);
	Wall_1->SetVisibility(false, true);
	Wall_2->SetVisibility(false, true);
	Wall_3->SetVisibility(false, true);
}

// Called every frame
void AMazeCell::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMazeCell::Initialize(int32 Row, int32 Column, int32 Index)
{
	bCreated = false;

	RowIndex = Row;
	ColumnIndex = Column;

	NumberWallsUp = 4;

	if (DebugText != nullptr)
	{
		FString Text = FString::FromInt(Index) + " = (" + FString::FromInt(RowIndex) + ", " + FString::FromInt(ColumnIndex) + ")";
		DebugText->SetText(FText::FromString(Text));
	}

}

void AMazeCell::HideFloor()
{
	Floor->SetVisibility(false, true);
}

void AMazeCell::ShowFloor()
{
	Floor->SetVisibility(true, true);
}

void AMazeCell::HideWall(int32 Index)
{
	switch (Index)
	{
	case 0:
		Wall_0->SetVisibility(false, true);
		break;
	case 1:
		Wall_1->SetVisibility(false, true);
		break;
	case 2:
		Wall_2->SetVisibility(false, true);
		break;
	case 3:
		Wall_3->SetVisibility(false, true);
		break;
	}
}
void AMazeCell::DestroyWall(int32 Index)
{
	switch (Index)
	{
	case 0:
		Wall_0->ConditionalBeginDestroy();
		break;
	case 1:
		Wall_1->ConditionalBeginDestroy();
		break;
	case 2:
		Wall_2->ConditionalBeginDestroy();
		break;
	case 3:
		Wall_3->ConditionalBeginDestroy();
		break;
	}
}

void AMazeCell::ShowWall(int32 Index)
{
	switch (Index)
	{
	case 0:
		Wall_0->SetVisibility(true, true);
		break;
	case 1:
		Wall_1->SetVisibility(true, true);
		break;
	case 2:
		Wall_2->SetVisibility(true, true);
		break;
	case 3:
		Wall_3->SetVisibility(true, true);
		break;
	}
}

void AMazeCell::CreatePassage(int32 WallIndex)
{
	switch (WallIndex)
	{
	case 0:
		Wall_0->ConditionalBeginDestroy();
		NumberWallsUp -= 1;
		break;
	case 1:
		Wall_1->ConditionalBeginDestroy();
		NumberWallsUp -= 1;
		break;
	case 2:
		Wall_2->ConditionalBeginDestroy();
		NumberWallsUp -= 1;
		break;
	case 3:
		Wall_3->ConditionalBeginDestroy();
		NumberWallsUp -= 1;
		break;
	}
}

