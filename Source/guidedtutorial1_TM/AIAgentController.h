// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Engine.h"
#include "Runtime/Engine/Classes/Engine/TargetPoint.h"
#include "Runtime/Core/Public/Math/UnrealMathUtility.h"
#include "Kismet/GameplayStatics.h"
#include "AIAgentController.generated.h"

/**
 * 
 */
UCLASS()
class GUIDEDTUTORIAL1_TM_API AAIAgentController : public AAIController
{
	GENERATED_BODY()

public:
	void BeginPlay() override;

	void OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result) override;

	//called to compel the AI to swap off of a given path, and to invalidate the given path if ClearPath is true
	void SwapPath(int PathNum, bool ClearPath);

private:
	UPROPERTY()
		TArray<AActor*> Waypoints;

	FTimerHandle TimerHandle;

		//Called to choose which waypoint to move to based on the current path
	UFUNCTION(BlueprintCallable, Category = "Play Start")
		void ChooseNextWaypoint();
	//Called to move to next waypoint in the current path, and to update the waypoint index
	void GoToNextWaypoint(TArray<AActor*> PointArray, int PathLength);
	//Called to change paths, if a random expression evaluates to true, another path is available, the current path is not None
	void RollNewPath(int NewPathProb);
	//Called to set the next destination to Goal, if there is a goal and a random expression evaluates to true
	void RollForGoal(int GoalProb);

	int CurrentWaypointIndex = 0;
	int WaypointIndexCount = 0;

	TArray<AActor*> PathOne;
	int Path1Length;
	TArray<AActor*> PathTwo;
	int Path2Length;
	TArray<AActor*> PathThree;
	int Path3Length;

	TArray<AActor*> GoalPoint;
	bool HasGoal;

	enum Paths {Path1, Path2, Path3, None, Goal};
	Paths PathToUse = None;
};
