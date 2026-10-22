#include "Characters/SigilCharacterBase.h"

#include "AbilitySystem/SigilAbilitySystemComponent.h"
#include "Characters/Data/SigilCharacterStartupData.h"


// Sets default values
ASigilCharacterBase::ASigilCharacterBase()
{
	PrimaryActorTick.bCanEverTick = false;
	
	SigilAbilitySystemComponent =CreateDefaultSubobject<USigilAbilitySystemComponent>("SigilAbilitySystemComponent");
}

void ASigilCharacterBase::BeginPlay()
{
	Super::BeginPlay();
}

UAbilitySystemComponent* ASigilCharacterBase::GetAbilitySystemComponent() const
{
	return SigilAbilitySystemComponent.Get();
}

void ASigilCharacterBase::GiveStartingAbilities() const
{
	if (StartUpData.IsValid())
		return;
	
	if (USigilCharacterStartupData* LoadedStartupData = StartUpData.LoadSynchronous())
		LoadedStartupData->GiveAbilitiesToComponent(SigilAbilitySystemComponent);
}


