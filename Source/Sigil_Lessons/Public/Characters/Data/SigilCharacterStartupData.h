// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/SigilGameplayAbility.h"
#include "Engine/DataAsset.h"
#include "SigilCharacterStartupData.generated.h"

UCLASS()
class SIGIL_LESSONS_API USigilCharacterStartupData : public UDataAsset
{
	GENERATED_BODY()
	
public:
	virtual void GiveAbilitiesToComponent(USigilAbilitySystemComponent* InSigilAbilityComp, int32 InLevel=1);
	
protected:
	UPROPERTY(EditDefaultsOnly, Category = "Sigil|StartUpData")
	TArray<TSubclassOf<USigilGameplayAbility>> StartUpAbilities;
	
	void GiveAbilities(TArray<TSubclassOf<USigilGameplayAbility>>& AbilitiesToGive, USigilAbilitySystemComponent* InSigilAbilityComponent, int32 ApplyLevel=1);
};
