// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SigilCharacterBase.h"
#include "SigilPlayerCharacter.generated.h"

class USigilInputConfig;
struct FInputActionValue;
class UInputAction;
class UInputMappingContext;
class UCameraComponent;
class USpringArmComponent;

UCLASS()
class SIGIL_LESSONS_API ASigilPlayerCharacter : public ASigilCharacterBase
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ASigilPlayerCharacter();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Sigil|Character", meta=(AllowPrivateAccess="true"))
	TObjectPtr<USpringArmComponent> CameraBoom;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Sigil|Character", meta=(AllowPrivateAccess="true"))
	TObjectPtr<UCameraComponent> FollowCamera;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Sigil|Character|Input", meta=(AllowPrivateAccess="true"))
	TObjectPtr<USigilInputConfig> InputConfig;
	
public:
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	void AbilityInputPressed(const FGameplayTag InputTag);
	void AbilityInputReleased(const FGameplayTag InputTag);
};
