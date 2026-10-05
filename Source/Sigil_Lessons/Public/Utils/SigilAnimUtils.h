// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "SigilAnimUtils.generated.h"

UENUM(BlueprintType)
enum class ECardinalDirection : uint8
{
	Forward,
	Backward,
	Left,
	Right
};

UCLASS()
class SIGIL_LESSONS_API USigilAnimUtils : public UObject
{
	GENERATED_BODY()
	
public:
	static float CalculateDirectionAngle(const FVector& Velocity, const FRotator& BaseRotation);
};
