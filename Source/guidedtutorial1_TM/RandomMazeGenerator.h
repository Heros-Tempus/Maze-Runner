

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RandomMazeGenerator.generated.h"

UCLASS()
class GUIDEDTUTORIAL1_TM_API ARandomMazeGenerator : public AActor
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(EditDefaultsOnly, Category="Maze Settings")
		TSubclassOf<class AMazeCell> CellToSwapClass = nullptr;

	UPROPERTY(EditAnywhere)
		int32 ColumnNumber;
	UPROPERTY(EditAnywhere)
		int32 RowNumber = 9;

	UPROPERTY(EditAnywhere)
		int32 DistanceXBetweenCells = 300;
	UPROPERTY(EditAnywhere)
		int32 DistanceYBetweenCells = 300;

	UPROPERTY(EditAnywhere)
		int32 EntranceSwitch;
private:
	TArray<AMazeCell*> CellList;
	TArray<int32> CellStack;
	int32 CurrentIndexCell;
	int32 VisitedCells;
	bool bRandomizeMaze;
	float CurrentDeltaTime;

	int32 GetAdjacentCellWithWalls(const int32& IndexCell);

public:	
	// Sets default values for this actor's properties
	ARandomMazeGenerator();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
