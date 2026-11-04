// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/Spec/SigilSpawnedItemSpec.h"

#include "Items/InstanceObjects/SigilSpawnedItemInstance.h"

USigilItemInstanceBase* USigilSpawnedItemSpec::CreateItemInstance(UObject* Object) const
{
	return NewObject<USigilSpawnedItemInstance>(Object);
}
