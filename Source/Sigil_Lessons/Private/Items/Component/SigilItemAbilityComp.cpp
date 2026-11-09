// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/Component/SigilItemAbilityComp.h"

#include "EnhancedInputSubsystems.h"
#include "AbilitySystem/SigilAbilitySystemComponent.h"
#include "Characters/SigilCharacterBase.h"
#include "Items/InstanceObjects/SigilItemInstanceBase.h"
#include "Items/InstanceObjects/SigilSpawnedItemInstance.h"
#include "Items/Spec/SigilItemSpecBase.h"
#include "Items/Spec/SigilSpawnedItemSpec.h"


USigilItemAbilityComp::USigilItemAbilityComp()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void USigilItemAbilityComp::CreateItemInstance(USigilItemSpecBase* InItemSpec)
{
	if (!InItemSpec || !SigilAbilitySystemComponent) return;
	
	USigilItemInstanceBase* Instance = InItemSpec->CreateItemInstance(this);
	Instance->Initialize(InItemSpec, SigilAbilitySystemComponent);
	
	if (USigilSpawnedItemInstance* SpawnedItemInstance = Cast<USigilSpawnedItemInstance>(Instance))
	{
		SpawnedItemInstance->SpawnAndAttachItem(GetOwner());
	}
	
	Instance->GrantAbilities();
	CurrentItemMap.Add(InItemSpec->ItemTag, Instance);
}

void USigilItemAbilityComp::EquipItem(const FGameplayTag InItemTag)
{
	if (IsValid(CurrentActiveItem))
		UnequipItem();
	
	USigilSpawnedItemInstance* ItemToEquip = Cast<USigilSpawnedItemInstance>(CurrentItemMap.Find(InItemTag)->Get());
	ItemToEquip->SpawnedItemActor->AttachToComponent(OwnerSkeletalMesh, FAttachmentTransformRules::SnapToTargetNotIncludingScale, 
		ItemToEquip->SpawnedItemSpec->ActiveSocket);
	CurrentActiveItem = ItemToEquip;
	CurrentActiveItem->GrantEquipAbility();
	InputSubsystem->AddMappingContext(CurrentActiveItem->SpawnedItemSpec->InputMappingContext, 1);
	SigilAbilitySystemComponent->AddLooseGameplayTag(CurrentActiveItem->SpawnedItemSpec->ItemTag);
}

void USigilItemAbilityComp::UnequipItem()
{
	if (!IsValid(CurrentActiveItem)) return;
	
	CurrentActiveItem->SpawnedItemActor->AttachToComponent(OwnerSkeletalMesh, FAttachmentTransformRules::SnapToTargetNotIncludingScale, 
		CurrentActiveItem->SpawnedItemSpec->PassiveSocket);
	CurrentActiveItem->RemoveEquipAbility();
	InputSubsystem->RemoveMappingContext(CurrentActiveItem->SpawnedItemSpec->InputMappingContext);
	SigilAbilitySystemComponent->RemoveLooseGameplayTag(CurrentActiveItem->SpawnedItemSpec->ItemTag);
	CurrentActiveItem = nullptr;
}

USigilItemInstanceBase* USigilItemAbilityComp::GetItemInstance(const FGameplayTag InItemTag) const
{
	if (USigilItemInstanceBase* FoundInstance = CurrentItemMap.Find(InItemTag)->Get())
	{
		return FoundInstance;
	}
	return nullptr;
}

void USigilItemAbilityComp::BeginPlay()
{
	Super::BeginPlay();

	if (AActor* Owner = GetOwner())
	{
		if (ASigilCharacterBase* SigilCharacter = Cast<ASigilCharacterBase>(Owner))
		{
			OwnerSkeletalMesh = SigilCharacter->GetMesh();
			SigilAbilitySystemComponent = Cast<USigilAbilitySystemComponent>(SigilCharacter->GetAbilitySystemComponent());
		}
		
		if (APlayerController* PC = Cast<APlayerController>(Owner->GetInstigatorController()))
		{
			if (ULocalPlayer* LP = PC->GetLocalPlayer())
			{
				InputSubsystem = LP->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();
			}
		}
	}
}




