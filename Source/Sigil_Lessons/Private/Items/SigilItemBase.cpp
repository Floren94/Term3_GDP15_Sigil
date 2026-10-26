// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/SigilItemBase.h"
#include "Components/BoxComponent.h"


// Sets default values
ASigilItemBase::ASigilItemBase()
{
	PrimaryActorTick.bCanEverTick = false;
	
	ItemMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ItemMesh"));
	RootComponent = ItemMesh;
	
	ItemCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("ItemCollider"));
	ItemCollider->SetupAttachment(ItemMesh);
	ItemCollider->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	ItemCollider->SetBoxExtent(FVector(15.0f,15.0f,15.0f));
}

