// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/InstanceObjects/SigilSpawnedItemInstance.h"

#include "AbilitySystem/SigilAbilitySystemComponent.h"
#include "Engine/AssetManager.h"
#include "Engine/StreamableManager.h"
#include "GameFramework/Character.h"
#include "Items/SigilItemBase.h"
#include "Items/Spec/SigilSpawnedItemSpec.h"

void USigilSpawnedItemInstance::Initialize(USigilItemSpecBase* InItemSpec, USigilAbilitySystemComponent* SigilASC)
{
	Super::Initialize(InItemSpec, SigilASC);
	SpawnedItemSpec = Cast<USigilSpawnedItemSpec>(InItemSpec);
}

void USigilSpawnedItemInstance::GrantEquipAbility()
{
	if (!OwningASC || !SpawnedItemSpec) return;
	
	for (const FInputAbilitySet AbilitySet: SpawnedItemSpec->EquipAbilities)
	{
		if (AbilitySet.IsValid())
		{
			FGameplayAbilitySpec Spec(AbilitySet.Ability, 1, INDEX_NONE, OwningASC->GetOwner());
			Spec.GetDynamicSpecSourceTags().AddTag(AbilitySet.InputTag);
			EquipItemAbilitySpecHandles.Add(OwningASC->GiveAbility(Spec));
		}
	}
}

void USigilSpawnedItemInstance::RemoveEquipAbility()
{
	if (!OwningASC) return;
	
	for (const FGameplayAbilitySpecHandle& ItemAbilityHandle: ItemAbilitySpecHandles)
	{
		if (ItemAbilityHandle.IsValid())
			OwningASC->ClearAbility(ItemAbilityHandle);
	}
	ItemAbilitySpecHandles.Empty();
}

void USigilSpawnedItemInstance::SpawnAndAttachItem(AActor* InOwner)
{
	FStreamableManager& StreamableManager = UAssetManager::GetStreamableManager();
	StreamableManager.RequestAsyncLoad(SpawnedItemSpec->ItemClass.ToSoftObjectPath(),
		FStreamableDelegate::CreateWeakLambda(this,[this,InOwner]()
		{
			if (!IsValid(InOwner)) return;
			
			UClass* LoadedItemClass = SpawnedItemSpec->ItemClass.Get();
			if (!LoadedItemClass) return;
			
			FActorSpawnParameters SpawnParams;
			SpawnParams.Owner = InOwner;
			SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
			SpawnedItemActor = InOwner->GetWorld()->SpawnActor<ASigilItemBase>(LoadedItemClass, SpawnParams);
			
			if (ACharacter* Character = Cast<ACharacter>(InOwner))
			{
				if (USkeletalMeshComponent* SkelMesh = Character->GetMesh())
				{
					SpawnedItemActor->AttachToComponent(SkelMesh, FAttachmentTransformRules::SnapToTargetNotIncludingScale, SpawnedItemSpec->PassiveSocket);
				}
			}
		})
	);
}
