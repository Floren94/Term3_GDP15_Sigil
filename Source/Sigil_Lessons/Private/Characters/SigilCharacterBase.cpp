#include "Characters/SigilCharacterBase.h"

#include "AbilitySystem/SigilAbilitySystemComponent.h"
#include "AbilitySystem/Attributes/SigilHealthAttributeSet.h"
#include "Characters/Data/SigilCharacterStartupData.h"
#include "Items/Component/SigilItemAbilityComp.h"


// Sets default values
ASigilCharacterBase::ASigilCharacterBase()
{
	PrimaryActorTick.bCanEverTick = false;
	
	SigilAbilitySystemComponent =CreateDefaultSubobject<USigilAbilitySystemComponent>("SigilAbilitySystemComponent");
	SigilItemAbilityComp =CreateDefaultSubobject<USigilItemAbilityComp>("SigilItemAbilityComponent");
	
	HealthAttributeSet = CreateDefaultSubobject<USigilHealthAttributeSet>("HealthAttributeSet");
}

void ASigilCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
	SigilAbilitySystemComponent->InitAbilityActorInfo(this,this);
	GiveStartingAbilities();
}

UAbilitySystemComponent* ASigilCharacterBase::GetAbilitySystemComponent() const
{
	return SigilAbilitySystemComponent.Get();
}

void ASigilCharacterBase::GiveStartingAbilities() const
{
	if (StartUpData.IsNull())
	{
		return;
	}
	
	if (USigilCharacterStartupData* LoadedStartupData = StartUpData.LoadSynchronous())
	{
		LoadedStartupData->GiveAbilitiesToComponent(SigilAbilitySystemComponent);
		LoadedStartupData->GiveStartingItems(SigilItemAbilityComp);
	}
}


