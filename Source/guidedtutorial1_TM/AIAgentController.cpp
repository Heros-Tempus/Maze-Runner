// Fill out your copyright notice in the Description page of Project Settings.

#include "AIAgentController.h"
#include "Agent.h"
#include "Engine.h"

/*
The minimum requirement for this AI to patrol the level is for target points to be placed
The AI will find the set of all target points and randomly wander between them

The AI can then be given basic direction by setting its Target Tags UPROPERTY in the editor, and giving the target points a matching Actor tag
The AI will find the set of all target points corresponding to their Target Tag and cycle between them
This creates a set of target points specific to the instance of the AI

The AI can also be given more complex direction by adding additional tags on the target points in the level.
Any target point with actor tags equal to Path1, Path2, or Path3 will be added to three different TArrays
The AI will then start patrolling on the first of these subsets which is valid
When the AI has visited a number of points equal to the path length it will generate a random value to decide if it should swap to the next valid subset
Target points can belong to multiple subsets if they have valid tags set
This creates up to three sets of target points that the AI will randomly swap between
The AI does not need a set of target points specifically assigned to it for the subsets to work

Also, every time it rolls for the next path it also rolls for move to goal, and if there is a goal set then the AI will proceed directly to the goal when the roll succeeds
for a goal to be set, some actor must have the tag Goal
*/

void AAIAgentController::BeginPlay()
{
	Super::BeginPlay();

	//Gets the controlled pawn
	AAgent* Pawn = Cast<AAgent>(GetPawn());
	if (Pawn != nullptr)
	{//if cast succeeds, then populate Waypoints with all target points with a tag matching the Pawn's target tag
		UGameplayStatics::GetAllActorsWithTag(GetWorld(), Pawn->TargetTags, Waypoints);
	}

	if (Waypoints.Num() <= 0) 
	{//if no actors with tag was found, then populate Waypoints with all target point actors instead
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATargetPoint::StaticClass(), Waypoints);
	}

	//Populate three TArrays with subsets of the actors in Waypoints based on their tags
	for (AActor* Point : Waypoints)
	{
		if (Point->ActorHasTag(FName(TEXT("Goal"))))
		{//if point is the goal, then it cannot be added to any path
			Waypoints.Remove(Point);
			continue;
		}
		if (Point->ActorHasTag(FName(TEXT("Path1"))))
		{//if point actor has tag Path1, then it is added to PathOne
			PathOne.Add(Point);
		}
		if (Point->ActorHasTag(FName(TEXT("Path2"))))
		{//if point actor has tag Path2, then it is added to PathTwo
			PathTwo.Add(Point);
		}
		if (Point->ActorHasTag(FName(TEXT("Path3"))))
		{//if point actor has tag Path3, then it is added to PathThree
			PathThree.Add(Point);
		}
	}

	WaypointIndexCount = Waypoints.Num();

	//These values will be 0 if their respective subset is empty
	Path1Length = PathOne.Num();
	Path2Length = PathTwo.Num();
	Path3Length = PathThree.Num();

	//Check for a valid path to start on
	if (Path1Length > 0)
	{//Start on Path1 if available
		PathToUse = Path1;
	}
	else if (Path2Length > 0)
	{//Start on Path2 if available and Path1 is not
		PathToUse = Path2;
	}
	else if (Path3Length > 0)
	{//Start on Path3 if available and Path1 and Path3 are not
		PathToUse = Path3;
	}
	else
	{//Use no subset of Waypoints
		PathToUse = None;
	}

	//set up the goal seperate from the lists of Waypoints and Paths
	UGameplayStatics::GetAllActorsWithTag(GetWorld(), FName(TEXT("Goal")), GoalPoint);
	if (GoalPoint.Num() > 0)
	{
		HasGoal = true;
		//if (GEngine)
			//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("Has Goal")));
	}
	else
	{
		HasGoal = false;
		//if (GEngine)
		//	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("Does not have goal")));
	}
}

void AAIAgentController::OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult & Result)
{

	Super::OnMoveCompleted(RequestID, Result);

	GetWorldTimerManager().SetTimer(TimerHandle, this, &AAIAgentController::ChooseNextWaypoint, 3.0f, false);
}

//Called to choose which waypoint to move to based on the current path
void AAIAgentController::ChooseNextWaypoint()
{

	switch (PathToUse)
	{
	case Path1://move to the next point in PathOne
	//	if (GEngine)
	//		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("Moving to next point on path 1")));
		GoToNextWaypoint(PathOne, Path1Length);
		//large chance to change paths if at end of path
		if (CurrentWaypointIndex >= Path1Length - 1)
		{
			RollNewPath(75);
			//tiny chance to move to goal
			RollForGoal(1);
		}
		break;
	case Path2://move to the next point in PathTwo
	//	if (GEngine)
	//		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("Moving to next point on path 2")));
		GoToNextWaypoint(PathTwo, Path2Length);
		//moderate chance to change paths if at end of path
		if (CurrentWaypointIndex >= Path2Length - 1)
		{
			RollNewPath(25);
			//small chance to move to goal
			RollForGoal(5);
		}
		break;
	case Path3://move to the next point in PathThree
	//	if (GEngine)
	//		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("Moving to next point on path 3")));
		GoToNextWaypoint(PathThree, Path3Length);
		//small chance to change paths if at end of path
		if (CurrentWaypointIndex >= Path3Length - 1)
		{
			RollNewPath(1);
			//enormous chance to move to goal
			RollForGoal(75);
		}
		break;
	case None://move to the next point in Waypoints
	//	if (GEngine)
	//		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("Moving to next point on path NULL")));
		if (WaypointIndexCount > 0)
		GoToNextWaypoint(Waypoints, WaypointIndexCount);

		//small chance to move to goal if at end of path
		if (CurrentWaypointIndex >= WaypointIndexCount -1)
		RollForGoal(5);

		break;
	case Goal://if the path has been set to goal, move to goal and do not roll for a new path - the AI is done patrolling once it has reached the goal
		MoveToActor(GoalPoint[0]);
		break;
	}
}

//Called to move to a random point in the current path, and to update the waypoint index
void AAIAgentController::GoToNextWaypoint(TArray<AActor*> PointArray, int PathLength)
{
	MoveToActor(PointArray[FMath::RandRange(0, PathLength-1)], 5.0f, false);
	int Cycle = CurrentWaypointIndex % PathLength;
	if (CurrentWaypointIndex >= PathLength - 1)
	{
		CurrentWaypointIndex = 0;
	}
	else
	{
		CurrentWaypointIndex++;
	}
}

//Called to change paths, if a random expression evaluates to true, another path is available, the current path is not None
void AAIAgentController::RollNewPath(int NewPathProb)
{
	if ((FMath::RandRange(1, 100) <= NewPathProb) && (PathToUse != None))
	{
		switch (PathToUse) {
		case Path1://if on path 1,
			if (Path2Length > 0)
			{//check if path 2 is valid, swap if it is
				CurrentWaypointIndex = 0;
				PathToUse = Path2;
			}
			else if (Path3Length > 0)
			{//if path 2 is not valid, check if path 3 is valid, swap if it is
				CurrentWaypointIndex = 0;
				PathToUse = Path3;
			}
			break;
		case Path2://if on path 2
			if (Path3Length > 0)
			{//check if path 3 is valid, swap if it is
				CurrentWaypointIndex = 0;
				PathToUse = Path3;
			}
			else if (Path1Length > 0)
			{//if path 3 is not valid, check if path 1 is valid, swap if it is
				CurrentWaypointIndex = 0;
				PathToUse = Path1;
			}
			break;
		case Path3://if on path 3
			if (Path1Length > 0)
			{//check if path 1 is valid, swap if it is
				CurrentWaypointIndex = 0;
				PathToUse = Path1;
			}
			else if (Path2Length > 0)
			{//if path 1 is not valid, check if path 3 is valid, swap if it is
				CurrentWaypointIndex = 0;
				PathToUse = Path2;
			}
			break;
		}
	}
}

//Called to set the next destination to Goal, if there is a goal
void AAIAgentController::RollForGoal(int GoalProb)
{
	if (FMath::RandRange(1, 100) <= GoalProb && HasGoal)
	{
	//	if (GEngine)
	//		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("Moving to goal instead")));
		PathToUse = Goal;
	}
}

//called to compel the AI to swap off of a given path, and to invalidate the given path if ClearPath is true
void AAIAgentController::SwapPath(int PathNum, bool ClearPath)
{
	//if (GEngine)
	//	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("Called ClearPath")));
	switch (PathNum)
	{
	case 1:
		if (Path2Length > 0)
		{
			PathToUse = Path2;
		}
		else if (Path3Length > 0)
		{
			PathToUse = Path3;
		}
		else
		{
			PathToUse = None;
		}
		if (ClearPath)
		{
			Path1Length = 0;
		}
		break;
	case 2:
		if (Path3Length > 0)
		{
			PathToUse = Path3;
		}
		else if (Path1Length > 0)
		{
			PathToUse = Path1;
		}
		else
		{
			PathToUse = None;
		}
		if (ClearPath)
		{
			Path2Length = 0;
		}
		break;
	case 3:
		if (Path1Length > 0)
		{
			PathToUse = Path1;
		}
		else if (Path2Length > 0)
		{
			PathToUse = Path2;
		}
		else
		{
			PathToUse = None;
		}
		if (ClearPath)
		{
			Path3Length = 0;
		}
		break;
	}
	CurrentWaypointIndex = 0;
}
