// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/SigilGameplayAbility.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystem/SigilAbilitySystemComponent.h"

void USigilGameplayAbility::OnGiveAbility(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec)
{
	Super::OnGiveAbility(ActorInfo, Spec);
	
	if (!ActorInfo)
		return;
	
	AActor* RawOwner = ActorInfo->OwnerActor.Get();
	if (!IsValid(RawOwner))
		return;
	
	if (bActivateOnGranted && ActorInfo->AbilitySystemComponent.IsValid())
		ActorInfo->AbilitySystemComponent->TryActivateAbility(Spec.Handle, false);
}

USigilAbilitySystemComponent* USigilGameplayAbility::GetOwnerAbilitySystemComponent()
{
	return Cast<USigilAbilitySystemComponent>(CurrentActorInfo->AbilitySystemComponent);
}
