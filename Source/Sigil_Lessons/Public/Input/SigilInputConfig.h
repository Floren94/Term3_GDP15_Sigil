// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnhancedInputComponent.h"
#include "GameplayTagContainer.h"
#include "Engine/DataAsset.h"
#include "SigilInputConfig.generated.h"

class UInputAction;
class UInputMappingContext;

USTRUCT(BlueprintType)
struct FSigilInputActionConfig
{
	GENERATED_BODY()
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UInputAction> InputAction;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	ETriggerEvent TriggerEvent;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FGameplayTag InputTag;
};


UCLASS()
class SIGIL_LESSONS_API USigilInputConfig : public UDataAsset
{
	GENERATED_BODY()
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UInputMappingContext> DefaultMappingContext;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<FSigilInputActionConfig> AbilityInputActions;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<FSigilInputActionConfig> SigilNativeActions;
	
	TObjectPtr<UInputAction> GetInputActionByTag(const FGameplayTag& InInputTag) const;
};
