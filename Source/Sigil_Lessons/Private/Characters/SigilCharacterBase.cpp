#include "Characters/SigilCharacterBase.h"

#include "AbilitySystem/SigilAbilitySystemComponent.h"


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

void ASigilCharacterBase::GiveDefaultAbilities() const
{
	check(SigilAbilitySystemComponent);
	for (TSubclassOf<UGameplayAbility> Ability : DefaultAbilities)
	{
		const FGameplayAbilitySpec AbilitySpec(Ability,1);
		SigilAbilitySystemComponent->GiveAbility(AbilitySpec);
	}
}

