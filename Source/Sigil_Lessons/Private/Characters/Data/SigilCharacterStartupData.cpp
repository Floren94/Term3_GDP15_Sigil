// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Data/SigilCharacterStartupData.h"

#include "AbilitySystem/SigilAbilitySystemComponent.h"
#include "Items/Component/SigilItemAbilityComp.h"

void USigilCharacterStartupData::GiveAbilitiesToComponent(USigilAbilitySystemComponent* InSigilAbilityComp,
                                                          int32 InLevel)
{
	check(InSigilAbilityComp)
	GiveAbilities(StartUpAbilities, InSigilAbilityComp, InLevel);
}

void USigilCharacterStartupData::GiveStartingItems(USigilItemAbilityComp* InSigilItemComp)
{
	check(InSigilItemComp)
	CreateItemInstances(StartingItems, InSigilItemComp);
}

void USigilCharacterStartupData::GiveAbilities(TArray<TSubclassOf<USigilGameplayAbility>>& AbilitiesToGive,
                                               USigilAbilitySystemComponent* InSigilAbilityComponent, int32 ApplyLevel)
{
	if (AbilitiesToGive.IsEmpty())
		return;
	
	for (const TSubclassOf<USigilGameplayAbility>& Ability : AbilitiesToGive)
	{
		if (!IsValid(Ability))
			continue;
		
		InSigilAbilityComponent->GiveAbility(FGameplayAbilitySpec(Ability, ApplyLevel, INDEX_NONE, InSigilAbilityComponent->GetOwner()));
	}
}

void USigilCharacterStartupData::CreateItemInstances(TArray<TObjectPtr<USigilItemSpecBase>>& InStartingItems,
	USigilItemAbilityComp* InSigilItemAbilityComp)
{
	if (InStartingItems.IsEmpty()) return;
	
	for (const TObjectPtr<USigilItemSpecBase>& Item : InStartingItems)
	{
		InSigilItemAbilityComp->CreateItemInstance(Item);
	}
}
