// Fill out your copyright notice in the Description page of Project Settings.


#include "Input/SigilInputConfig.h"

TObjectPtr<UInputAction> USigilInputConfig::GetInputActionByTag(const FGameplayTag& InInputTag) const
{
	for (const FSigilInputActionConfig& InputConfig : AbilityInputActions)
	{
		if (InputConfig.InputTag == InInputTag && IsValid(InputConfig.InputAction))
		{
			return InputConfig.InputAction;
		}
	}
	return nullptr;
}
