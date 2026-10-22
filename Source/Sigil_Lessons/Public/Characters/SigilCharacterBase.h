// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "Abilities/GameplayAbility.h"
#include "GameFramework/Character.h"
#include "SigilCharacterBase.generated.h"

class USigilCharacterStartupData;
class USigilAbilitySystemComponent;

UCLASS()
class SIGIL_LESSONS_API ASigilCharacterBase : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ASigilCharacterBase();
	
	virtual void BeginPlay() override;
	
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	
protected:
	UPROPERTY(VisibleAnywhere, Category="Sigil|Character|AbilitySystem")
	TObjectPtr<USigilAbilitySystemComponent> SigilAbilitySystemComponent;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly,Category="Sigil|StartUpData")
	TSoftObjectPtr<USigilCharacterStartupData> StartUpData;
	
	void GiveStartingAbilities() const;
};
