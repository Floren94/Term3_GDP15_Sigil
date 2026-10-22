// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Data/SigilCharacterStartupData.h"

#include "AbilitySystem/SigilAbilitySystemComponent.h"

void USigilCharacterStartupData::GiveAbilitiesToComponent(USigilAbilitySystemComponent* InSigilAbilityComp,
                                                          int32 InLevel)
{
	check(InSigilAbilityComp)
	GiveAbilities(StartUpAbilities, InSigilAbilityComp, InLevel);
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
