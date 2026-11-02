// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Components/ActorComponent.h"
#include "SigilItemAbilityComp.generated.h"


class USigilItemSpecBase;
class USigilItemInstanceBase;
class UEnhancedInputLocalPlayerSubsystem;
class USigilAbilitySystemComponent;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class SIGIL_LESSONS_API USigilItemAbilityComp : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	USigilItemAbilityComp();

	UFUNCTION(BlueprintCallable)
	void CreateItemInstance(USigilItemSpecBase* InItemSpec);
	
	UFUNCTION(BlueprintCallable)
	USigilItemInstanceBase* GetItemInstance(const FGameplayTag InItemTag) const;
	
	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	
	UPROPERTY()
	TObjectPtr<USigilAbilitySystemComponent> SigilAbilitySystemComponent;

	UPROPERTY()
	TObjectPtr<USkeletalMeshComponent> OwnerSkeletalMesh;
	
	UPROPERTY()
	TObjectPtr<UEnhancedInputLocalPlayerSubsystem> InputSubsystem;
	
	UPROPERTY()
	TMap<FGameplayTag, TObjectPtr<USigilItemInstanceBase>> CurrentItemMap;
};
