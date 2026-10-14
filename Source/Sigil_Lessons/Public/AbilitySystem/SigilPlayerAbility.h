// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SigilGameplayAbility.h"
#include "SigilPlayerAbility.generated.h"

class ASigilPlayerController;
class ASigilPlayerCharacter;
/**
 * 
 */
UCLASS()
class SIGIL_LESSONS_API USigilPlayerAbility : public USigilGameplayAbility
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintPure, Category="Sigil|AbilitySystem")
	ASigilPlayerCharacter* GetPlayerCharacterFromInfo();
	
	UFUNCTION(BlueprintPure, Category="Sigil|AbilitySystem")
	ASigilPlayerController* GetPlayerControllerFromInfo();
	
private:
	TWeakObjectPtr<ASigilPlayerCharacter> PlayerCharacterWeak;
	TWeakObjectPtr<ASigilPlayerController> PlayerControllerWeak;
};
