// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "UObject/Object.h"
#include "AbilitySystem/SigilGameplayAbility.h"
#include "SigilInputAbilityData.generated.h"

USTRUCT(BlueprintType)
struct FInputAbilitySet
{
	GENERATED_BODY()
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FGameplayTag InputTag;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<USigilGameplayAbility> Ability;
	
	bool IsValid() const;
	
};
