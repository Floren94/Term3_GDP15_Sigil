// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SigilItemInstanceBase.h"
#include "SigilSpawnedItemInstance.generated.h"

class USigilSpawnedItemSpec;

UCLASS()
class SIGIL_LESSONS_API USigilSpawnedItemInstance : public USigilItemInstanceBase
{
	GENERATED_BODY()
public:
	UPROPERTY()
	TObjectPtr<USigilSpawnedItemSpec> SpawnedItemSpec;
	
	UPROPERTY()
	TArray<FGameplayAbilitySpecHandle> EquipItemAbilitySpecHandles;
	
	UPROPERTY()
	TObjectPtr<AActor> SpawnedItemActor = nullptr;
	
	virtual void Initialize(USigilItemSpecBase* InItemSpec, USigilAbilitySystemComponent* SigilASC) override;
	virtual void GrantEquipAbility();
	virtual void RemoveEquipAbility();
	virtual void SpawnAndAttachItem(AActor* InOwner);
};
