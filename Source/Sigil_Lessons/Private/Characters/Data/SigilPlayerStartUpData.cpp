// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Data/SigilPlayerStartUpData.h"

#include "AbilitySystem/SigilAbilitySystemComponent.h"

void USigilPlayerStartUpData::GiveAbilitiesToComponent(USigilAbilitySystemComponent* InSigilAbilityComp, int32 InLevel)
{
	Super::GiveAbilitiesToComponent(InSigilAbilityComp, InLevel);
	
	for(const FInputAbilitySet AbilitySet: PlayerStartUpAbilities)
	{
		if (!AbilitySet.IsValid())
			continue;
		
		FGameplayAbilitySpec AbilitySpec(AbilitySet.Ability, InLevel, INDEX_NONE, InSigilAbilityComp->GetOwner());
		AbilitySpec.GetDynamicSpecSourceTags().AddTag(AbilitySet.InputTag);
		InSigilAbilityComp->GiveAbility(AbilitySpec);
	}
}
