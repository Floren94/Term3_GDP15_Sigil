// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/SigilAnimInstanceShared.h"

#include "Characters/SigilCharacterBase.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Utils/SigilAnimUtils.h"

void USigilAnimInstanceShared::NativeInitializeAnimation()
{
	OwningPlayer = Cast<ASigilCharacterBase>(TryGetPawnOwner());
	if (IsValid(OwningPlayer))
	{
		MovementComponent = OwningPlayer->GetCharacterMovement();
	}
}

void USigilAnimInstanceShared::NativeThreadSafeUpdateAnimation(float DeltaSeconds)
{
	if (IsValid(OwningPlayer))
	{
		WorldRotation = OwningPlayer->GetActorRotation();
		WorldVelocity = OwningPlayer->GetVelocity();
		WorldVelocity2D = WorldVelocity * FVector(1.0f, 1.0f, 0.0f);
		
		VelocityRotationAngle = USigilAnimUtils::CalculateDirectionAngle(WorldVelocity2D, WorldRotation);
		VelocityDirection = CalculateDirectionFromAngle();
		
		bIsFalling = MovementComponent->IsFalling();
		bShouldMove = WorldVelocity2D.Length() > 20.0f;
	}
}

ECardinalDirection USigilAnimInstanceShared::CalculateDirectionFromAngle() const
{
	const float AbsAngle = FMath::Abs(VelocityRotationAngle);
	
	if (AbsAngle <= 45.0f) {return ECardinalDirection::Forward;}
	if (AbsAngle >= 135.0f) {return ECardinalDirection::Backward;}
	if (VelocityRotationAngle > 0.0f) {return ECardinalDirection::Right;}
	
	return ECardinalDirection::Left;
}
