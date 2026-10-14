// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/SigilPlayerAbility.h"

#include "Characters/SigilPlayerCharacter.h"
#include "Controllers/SigilPlayerController.h"

ASigilPlayerCharacter* USigilPlayerAbility::GetPlayerCharacterFromInfo()
{
	if (!PlayerCharacterWeak.IsValid())
	{
		PlayerCharacterWeak = Cast<ASigilPlayerCharacter>(CurrentActorInfo->OwnerActor);
	}
	
	return PlayerCharacterWeak.IsValid() ? PlayerCharacterWeak.Get() : nullptr;
}

ASigilPlayerController* USigilPlayerAbility::GetPlayerControllerFromInfo()
{
	if (!PlayerControllerWeak.IsValid())
	{
		PlayerControllerWeak = Cast<ASigilPlayerController>(CurrentActorInfo->OwnerActor);
	}
	
	return PlayerControllerWeak.IsValid() ? PlayerControllerWeak.Get() : nullptr;
}
