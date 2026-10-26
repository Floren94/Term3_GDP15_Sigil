// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/SigilPlayerCharacter.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "AbilitySystem/SigilAbilitySystemComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameplayTags/SigilGameplayTagsInput.h"
#include "Input/SigilInputComponent.h"
#include "Input/SigilInputConfig.h"


// Sets default values
ASigilPlayerCharacter::ASigilPlayerCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 300.0f;
	CameraBoom->bUsePawnControlRotation = true;
	
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom);
}

// Called to bind functionality to input
void ASigilPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	check(InputConfig);
	
	const ULocalPlayer* LocalPlayer = GetController<APlayerController>()->GetLocalPlayer();
	check(LocalPlayer);
	
	UEnhancedInputLocalPlayerSubsystem* Subsystem = LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();
	check(Subsystem);
	
	Subsystem->ClearAllMappings();
	Subsystem->AddMappingContext(InputConfig->DefaultMappingContext, 0);
	
	if (USigilInputComponent* SigilInputComponent = CastChecked<USigilInputComponent>(PlayerInputComponent))
	{
		SigilInputComponent->BindNativeAction(InputConfig, SigilGameplayTags::InputTag_Move, ETriggerEvent::Triggered, this, &ThisClass::Move);
		SigilInputComponent->BindNativeAction(InputConfig, SigilGameplayTags::InputTag_Look, ETriggerEvent::Triggered, this, &ThisClass::Look);
		SigilInputComponent->BindAbilityAction(InputConfig, this, &ThisClass::AbilityInputPressed, &ThisClass::AbilityInputReleased);
	}
}

void ASigilPlayerCharacter::Move(const FInputActionValue& Value)
{
	const FVector2d InputValue = Value.Get<FVector2d>();
	
	FRotator ControlRotation = GetControlRotation();
	
	const FVector RightVector = FRotationMatrix(ControlRotation).GetScaledAxis(EAxis::Y);
	
	AddMovementInput(ControlRotation.Vector(), InputValue.Y);
	AddMovementInput(RightVector, InputValue.X);
	
}

void ASigilPlayerCharacter::Look(const FInputActionValue& Value)
{
	const FVector2d InputValue = Value.Get<FVector2d>();
	
	AddControllerYawInput(InputValue.X);
	AddControllerPitchInput(InputValue.Y);
	
}

void ASigilPlayerCharacter::AbilityInputPressed(const FGameplayTag InputTag)
{
	SigilAbilitySystemComponent->AbilityTagPressed(InputTag);
}

void ASigilPlayerCharacter::AbilityInputReleased(const FGameplayTag InputTag)
{
	SigilAbilitySystemComponent->AbilityTagReleased(InputTag);
}
