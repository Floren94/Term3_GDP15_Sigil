// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/SigilGameplayAbility.h"
#include "Engine/DataAsset.h"
#include "Items/Spec/SigilItemSpecBase.h"
#include "SigilCharacterStartupData.generated.h"

class USigilItemAbilityComp;

UCLASS()
class SIGIL_LESSONS_API USigilCharacterStartupData : public UDataAsset
{
	GENERATED_BODY()
	
public:
	virtual void GiveAbilitiesToComponent(USigilAbilitySystemComponent* InSigilAbilityComp, int32 InLevel=1);
	virtual void GiveStartingItems(USigilItemAbilityComp* InSigilItemComp);
	
protected:
	UPROPERTY(EditDefaultsOnly, Category = "Sigil|StartUpData|Abilities")
	TArray<TSubclassOf<USigilGameplayAbility>> StartUpAbilities;
	
	UPROPERTY(EditDefaultsOnly, Category = "Sigil|StartUpData|Items")
	TArray<TObjectPtr<USigilItemSpecBase>> StartingItems;
	
	void GiveAbilities(TArray<TSubclassOf<USigilGameplayAbility>>& AbilitiesToGive, USigilAbilitySystemComponent* InSigilAbilityComponent, int32 ApplyLevel=1);
	void CreateItemInstances(TArray<TObjectPtr<USigilItemSpecBase>>& InStartingItems, USigilItemAbilityComp* InSigilItemAbilityComp);
};
