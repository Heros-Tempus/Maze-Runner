


#include "RandomMazeGenerator.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "MazeCell.h"

// Sets default values
ARandomMazeGenerator::ARandomMazeGenerator()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ARandomMazeGenerator::BeginPlay()
{
	Super::BeginPlay();

	FVector SpawnPosition = GetActorLocation();
	
	for (int iRow = 0; iRow < RowNumber; ++iRow)
	{
		SpawnPosition.X = GetActorLocation().X;

		for (int iCol = 0; iCol < ColumnNumber; ++iCol)
		{

			FActorSpawnParameters SpawnParameters;
			SpawnParameters.Owner = this;
			SpawnParameters.Instigator = Instigator;

			AMazeCell* SpawnedCell = GetWorld()->SpawnActor<AMazeCell>(CellToSwapClass, SpawnPosition, FRotator::ZeroRotator, SpawnParameters);

			if (SpawnedCell != nullptr)
			{
				SpawnedCell->AttachToActor(this, FAttachmentTransformRules::KeepWorldTransform);

				int32 CellIndex = iRow * ColumnNumber + iCol;

				SpawnedCell->Initialize(iRow, iCol, CellIndex);

				CellList.Add(SpawnedCell);
			}

			SpawnPosition.X += DistanceXBetweenCells;
		}

		SpawnPosition.Y += DistanceYBetweenCells;
	}

		int32 RandomRow = FMath::RandRange(0, RowNumber - 1);
		int32 RandomCol = FMath::RandRange(0, ColumnNumber - 1);

		CurrentIndexCell = RandomRow * ColumnNumber + RandomCol;

		CellList[CurrentIndexCell]->SetIsCreated(true);
		CellList[CurrentIndexCell]->ShowFloor();
		CellList[CurrentIndexCell]->ShowWall(0);
		CellList[CurrentIndexCell]->ShowWall(1);
		CellList[CurrentIndexCell]->ShowWall(2);
		CellList[CurrentIndexCell]->ShowWall(3);

		CellStack.Push(CurrentIndexCell);
		VisitedCells = 1;

		while (VisitedCells != 169)
		{
			CurrentDeltaTime = 0.0f;

			if (VisitedCells < CellList.Num())
			{
				UE_LOG(LogTemp, Warning, TEXT("Adding Cell: %d / %d "), CellStack.Num(), CellList.Num());

				int32 NextIndexCell = GetAdjacentCellWithWalls(CurrentIndexCell);

				if (NextIndexCell > -1)
				{
					CellStack.Push(CurrentIndexCell);
					CurrentIndexCell = NextIndexCell;
					VisitedCells++;
				}
				else
				{
					if (CellStack.Num() > 0)
					{
						CurrentIndexCell = CellStack.Pop();
					}
					else
					{
						VisitedCells = CellList.Num();
						UE_LOG(LogTemp, Warning, TEXT("Random Maze generation completed"));
						bRandomizeMaze = false;
					}
				}
			}
		}
		CellList[0]->DestroyWall(2);
		CellList[RowNumber * ColumnNumber - 1]->DestroyWall(3);
}

// Called every frame
void ARandomMazeGenerator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	/*
	if (bRandomizeMaze)
	{
		CurrentDeltaTime += DeltaTime;
		if (CurrentDeltaTime > WaitTimeBetweenCreateCells)
		{
			CurrentDeltaTime = 0.0f; 

			if (VisitedCells < CellList.Num())
			{
				UE_LOG(LogTemp, Warning, TEXT("Adding Cell: %d / %d "), CellStack.Num(), CellList.Num());

				int32 NextIndexCell = GetAdjacentCellWithWalls(CurrentIndexCell);

				if (NextIndexCell > -1)
				{
					CellStack.Push(CurrentIndexCell);
					CurrentIndexCell = NextIndexCell;
					VisitedCells++;
				}
				else
				{
					if (CellStack.Num() > 0)
					{
						CurrentIndexCell = CellStack.Pop();
					}
					else
					{
						VisitedCells = CellList.Num();
						UE_LOG(LogTemp, Warning, TEXT("Random Maze generation completed"));
						bRandomizeMaze = false;
					}
				}
			}
		}
	}
	CellList[0]->DestroyWall(2);
	CellList[RowNumber * ColumnNumber - 1]->DestroyWall(3);*/
}

int32 ARandomMazeGenerator::GetAdjacentCellWithWalls(const int32& IndexCell)
{
	TArray<int32> NeighbourCells;
	TArray<int32> Directions;

	int32 Col = CellList[IndexCell]->GetCoords().X;
	int32 Row = CellList[IndexCell]->GetCoords().Y;

	if ((Row - 1) >= 0)
	{
		int32 Next = (Row - 1) * ColumnNumber + Col;
		if (CellList[Next]->AllWallsIntact())
		{
			Directions.Add(0);
			NeighbourCells.Add(Next);
		}
	}

	if ((Row + 1) < RowNumber)
	{
		int32 Next = (Row + 1) * ColumnNumber + Col;
		if (CellList[Next]->AllWallsIntact())
		{
			Directions.Add(1);
			NeighbourCells.Add(Next);
		}

	}
	if ((Col - 1) >= 0)
	{
		int32 Next = Row * ColumnNumber + (Col - 1);
		if (CellList[Next]->AllWallsIntact())
		{
			Directions.Add(2);
			NeighbourCells.Add(Next);
		}

	}
	if ((Col + 1) < ColumnNumber)
	{
		int32 Next = Row * ColumnNumber + (Col + 1);
		if (CellList[Next]->AllWallsIntact())
		{
			Directions.Add(3);
			NeighbourCells.Add(Next);
		}

	}

	int32 NextCellIndex = -1;

	if (NeighbourCells.Num() > 0)
	{
		int32 RandomDirection = FMath::RandRange(0, Directions.Num() - 1);

		NextCellIndex = NeighbourCells[RandomDirection];

		if(!CellList[NextCellIndex]->GetIsCreated())
		{
			CellList[NextCellIndex]->SetIsCreated(true);
			CellList[NextCellIndex]->ShowFloor();
			CellList[NextCellIndex]->ShowWall(0);
			CellList[NextCellIndex]->ShowWall(1);
			CellList[NextCellIndex]->ShowWall(2);
			CellList[NextCellIndex]->ShowWall(3);
		}

		switch (Directions[RandomDirection])
		{
		case 0:
			CellList[NextCellIndex]->CreatePassage(1);
			CellList[IndexCell]->CreatePassage(0);
			break;
		case 1:
			CellList[NextCellIndex]->CreatePassage(0);
			CellList[IndexCell]->CreatePassage(1);
			break;
		case 2:
			CellList[NextCellIndex]->CreatePassage(3);
			CellList[IndexCell]->CreatePassage(2);
			break;
		case 3:
			CellList[NextCellIndex]->CreatePassage(2);
			CellList[IndexCell]->CreatePassage(3);
			break;
		}
	}
	return NextCellIndex;
}