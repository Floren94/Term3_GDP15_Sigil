// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "SigilGameplayAbility.generated.h"


class USigilAbilitySystemComponent;

UCLASS()
class SIGIL_LESSONS_API USigilGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()
	
protected:
	virtual void OnGiveAbility(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec) override;
	
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Sigil|AbilitySystem")
	bool bActivateOnGranted = false;
	
	UFUNCTION(BlueprintPure, Category="Sigil|AbilitySystem")
	USigilAbilitySystemComponent* GetOwnerAbilitySystemComponent();
	
};
