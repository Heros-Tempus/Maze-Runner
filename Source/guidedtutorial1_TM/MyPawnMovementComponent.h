// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PawnMovementComponent.h"
#include "MyPawnMovementComponent.generated.h"

UCLASS()
class GUIDEDTUTORIAL1_TM_API UMyPawnMovementComponent : public UPawnMovementComponent
{
	GENERATED_BODY()

		//Called every frame
		virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;
};
