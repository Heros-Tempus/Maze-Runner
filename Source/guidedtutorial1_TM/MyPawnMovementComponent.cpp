// Fill out your copyright notice in the Description page of Project Settings.

#include "MyPawnMovementComponent.h"


void UMyPawnMovementComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	//Checks if everything is still valid and allowed to move
	if (!PawnOwner || !UpdatedComponent || ShouldSkipUpdate(DeltaTime))
	{
		return;
	}

	//Get and then clear the movement vector
	FVector DesiredMovmentThisFrame = ConsumeInputVector().GetClampedToMaxSize(1.0f) * DeltaTime * 150.0f;

	//if movement input is not near 0 then move
	if (!DesiredMovmentThisFrame.IsNearlyZero())
	{
		FHitResult Hit;
		SafeMoveUpdatedComponent(DesiredMovmentThisFrame, UpdatedComponent->GetComponentRotation(), true, Hit);

		//if blocked, try to slide along blocking surface
		if (Hit.IsValidBlockingHit())
		{
			SlideAlongSurface(DesiredMovmentThisFrame, 1.0f - Hit.Time, Hit.Normal, Hit);
		}
	}
}