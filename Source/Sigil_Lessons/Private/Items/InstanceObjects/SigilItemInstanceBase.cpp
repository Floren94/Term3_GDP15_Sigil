// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/InstanceObjects/SigilItemInstanceBase.h"

#include "GameplayAbilitySpec.h"
#include "AbilitySystem/SigilAbilitySystemComponent.h"
#include "AbilitySystem/Data/SigilInputAbilityData.h"
#include "Items/Spec/SigilItemSpecBase.h"

void USigilItemInstanceBase::Initialize(USigilItemSpecBase* InItemSpec, USigilAbilitySystemComponent* SigilASC)
{
	ItemSpec = InItemSpec;
	OwningASC = SigilASC;
}

void USigilItemInstanceBase::GrantAbilities()
{
	if (!OwningASC) return;
	
	for (const FInputAbilitySet AbilitySet: ItemSpec->ItemAbilities)
	{
		if (!AbilitySet.IsValid()) continue;
		
		FGameplayAbilitySpec Spec(AbilitySet.Ability, 1, INDEX_NONE, OwningASC->GetOwner());
		Spec.GetDynamicSpecSourceTags().AddTag(AbilitySet.InputTag);
		ItemAbilitySpecHandles.Add(OwningASC->GiveAbility(Spec));
	}
}

void USigilItemInstanceBase::RemoveAbilities()
{
	if (!OwningASC) return;
	
	for (const FGameplayAbilitySpecHandle& ItemAbilityHandle: ItemAbilitySpecHandles)
	{
		if (ItemAbilityHandle.IsValid())
			OwningASC->ClearAbility(ItemAbilityHandle);
	}
	ItemAbilitySpecHandles.Empty();
}
