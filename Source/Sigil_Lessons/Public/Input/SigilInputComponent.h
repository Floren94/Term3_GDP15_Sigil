// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnhancedInputComponent.h"
#include "SigilInputConfig.h"
#include "SigilInputComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class SIGIL_LESSONS_API USigilInputComponent : public UEnhancedInputComponent
{
	GENERATED_BODY()

public:
	template<class UserObject, typename FuncType>
	void BindNativeAction(const USigilInputConfig* InInputConfig, const FGameplayTag& InInputTag, ETriggerEvent TriggerEvent, UserObject* Object, FuncType Func);
	
	template<class UserObject, typename FuncType>
	void BindAbilityAction(const USigilInputConfig* InInputConfig, ETriggerEvent TriggerEvent, UserObject* Object, FuncType Pressed, FuncType Released);
};

template<class UserObject, typename FuncType>
void USigilInputComponent::BindNativeAction(const USigilInputConfig* InInputConfig, const FGameplayTag& InInputTag, 
	ETriggerEvent TriggerEvent, UserObject* Object, FuncType Func)
{
	check(InInputConfig)
	if (const UInputAction* Action = InInputConfig->GetInputActionByTag(InInputTag))
	{
		BindAction(Action, TriggerEvent, Object, Func);
	}
}

template<class UserObject, typename FuncType>
void USigilInputComponent::BindAbilityAction(const USigilInputConfig* InInputConfig, ETriggerEvent TriggerEvent, 
	UserObject* Object, FuncType Pressed, FuncType Released)
{
	check(InInputConfig)
	for (const FSigilInputActionConfig& ActionConfig : InInputConfig->SigilInputActions )
	{
		if (ActionConfig.InputAction && ActionConfig.InputTag.IsValid())
		{
			if (Pressed)
				BindAction(ActionConfig.InputAction, ActionConfig.TriggerEvent, Object, Pressed, ActionConfig.InputTag);
			if (Released)
				BindAction(ActionConfig.InputAction, ActionConfig.TriggerEvent, Object, Released, ActionConfig.InputTag);
		}
	}
}

