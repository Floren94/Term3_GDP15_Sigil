// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SigilItemSpecBase.h"
#include "SigilSpawnedItemSpec.generated.h"

class ASigilItemBase;

UCLASS()
class SIGIL_LESSONS_API USigilSpawnedItemSpec : public USigilItemSpecBase
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "ObjectClass")
	TSoftClassPtr<ASigilItemBase> ItemClass;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Equip")
	FInputAbilitySet EquipAbility;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Equip")
	FName PassiveSocket;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Equip")
	FName ActiveSocket;
	
	virtual USigilItemInstanceBase* CreateItemInstance(UObject* Object) const override;
};
