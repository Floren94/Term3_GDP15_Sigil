// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SigilCharacterStartupData.h"
#include "AbilitySystem/Data/SigilInputAbilityData.h"
#include "SigilPlayerStartUpData.generated.h"

/**
 * 
 */
UCLASS()
class SIGIL_LESSONS_API USigilPlayerStartUpData : public USigilCharacterStartupData
{
	GENERATED_BODY()
	virtual void GiveAbilitiesToComponent(USigilAbilitySystemComponent* InSigilAbilityComp, int32 InLevel=1) override;
	
private:
	UPROPERTY(EditDefaultsOnly, Category = "Sigil|StartUpData|PlayerAbilities")
	TArray<FInputAbilitySet> PlayerStartUpAbilities;
};
