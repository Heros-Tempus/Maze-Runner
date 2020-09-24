

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MazeCell.generated.h"

UCLASS()
class GUIDEDTUTORIAL1_TM_API AMazeCell : public AActor
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "MazeCell")
		class USceneComponent* RootScene;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "MazeCell")
		class UStaticMeshComponent* Floor;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "MazeCell")
		class UStaticMeshComponent* Wall_0;//front wall

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "MazeCell")
		class UStaticMeshComponent* Wall_1;//right wall

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "MazeCell")
		class UStaticMeshComponent* Wall_2;//left wall

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "MazeCell")
		class UStaticMeshComponent* Wall_3;//back wall

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "MazeCell")
		class UTextRenderComponent* DebugText;

public:	
	// Sets default values for this actor's properties
	AMazeCell();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void Initialize(int32 Row, int32 Column, int32 Index);

	FORCEINLINE bool GetIsCreated() { return bCreated; };
	FORCEINLINE void SetIsCreated(bool Value) { bCreated = Value; };
	FORCEINLINE bool AllWallsIntact() { return (NumberWallsUp >= 4); };

	void HideFloor();
	void ShowFloor();

	void HideWall(int32 Index);
	void DestroyWall(int32 Index);
	void ShowWall(int32 Index);

	void CreatePassage(int32 WallIndex);

	FORCEINLINE FVector2D GetCoords() { return FVector2D(ColumnIndex, RowIndex); };

private:
	bool bCreated;
	int32 RowIndex;
	int32 ColumnIndex;
	int32 WallIndex;
	int32 NumberWallsUp;
};