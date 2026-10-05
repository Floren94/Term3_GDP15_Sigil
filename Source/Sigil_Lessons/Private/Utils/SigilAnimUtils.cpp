// Fill out your copyright notice in the Description page of Project Settings.


#include "Utils/SigilAnimUtils.h"

float USigilAnimUtils::CalculateDirectionAngle(const FVector& Velocity, const FRotator& BaseRotation)
{
	if (!Velocity.IsNearlyZero())
	{
		const FVector Forward = BaseRotation.Vector();
		const FVector Right = FRotationMatrix(BaseRotation).GetScaledAxis(EAxis::Y);
		const FVector NormalizedVelocity = Velocity.GetSafeNormal2D();
		
		float ForwardDegrees = FMath::RadiansToDegrees(FMath::Acos(FVector::DotProduct(Forward, NormalizedVelocity)));
		
		if (FVector::DotProduct(Right, NormalizedVelocity) < .0f)
		{
			ForwardDegrees *= -1.0f;
		}
		
		return ForwardDegrees;
	}
	return .0f;
}
