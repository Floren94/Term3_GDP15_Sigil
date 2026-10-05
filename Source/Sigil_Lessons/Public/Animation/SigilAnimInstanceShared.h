// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SigilAnimInstanceBase.h"
#include "SigilAnimInstanceShared.generated.h"

enum class ECardinalDirection : uint8;
class UCharacterMovementComponent;
class ASigilCharacterBase;
/**
 * 
 */
UCLASS()
class SIGIL_LESSONS_API USigilAnimInstanceShared : public USigilAnimInstanceBase
{
	GENERATED_BODY()
public:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeThreadSafeUpdateAnimation(float DeltaSeconds) override;
	
protected:
	UPROPERTY(Transient)
	TObjectPtr<ASigilCharacterBase> OwningPlayer;
	
	UPROPERTY(Transient)
	TObjectPtr<UCharacterMovementComponent> MovementComponent;
	
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category="Sigil|Data|Locomotion")
	FRotator WorldRotation;
	
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category="Sigil|Data|Locomotion")
	FVector WorldVelocity;
	
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category="Sigil|Data|Locomotion")
	FVector WorldVelocity2D;
	
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category="Sigil|Data|Locomotion")
	float VelocityRotationAngle;
	
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category="Sigil|Data|Locomotion")
	bool bIsFalling;
	
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category="Sigil|Data|Locomotion")
	bool bShouldMove;
	
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category="Sigil|Data|Locomotion")
	ECardinalDirection VelocityDirection;
	
	UFUNCTION()
	ECardinalDirection CalculateDirectionFromAngle() const;
};
