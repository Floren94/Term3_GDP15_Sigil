// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/Component/SigilItemAbilityComp.h"

#include "EnhancedInputSubsystems.h"
#include "AbilitySystem/SigilAbilitySystemComponent.h"
#include "Characters/SigilCharacterBase.h"
#include "Items/InstanceObjects/SigilItemInstanceBase.h"
#include "Items/Spec/SigilItemSpecBase.h"


USigilItemAbilityComp::USigilItemAbilityComp()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void USigilItemAbilityComp::CreateItemInstance(USigilItemSpecBase* InItemSpec)
{
	if (!InItemSpec || !SigilAbilitySystemComponent) return;
	
	USigilItemInstanceBase* Instance = InItemSpec->CreateItemInstance(this);
	Instance->Initialize(InItemSpec, SigilAbilitySystemComponent);
	Instance->GrantAbilities();
	CurrentItemMap.Add(InItemSpec->ItemTag, Instance);
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




