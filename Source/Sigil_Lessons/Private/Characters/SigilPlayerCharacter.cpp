// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/SigilPlayerCharacter.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"


// Sets default values
ASigilPlayerCharacter::ASigilPlayerCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	ReceiveControllerChangedDelegate.AddDynamic(this, &ThisClass::ASigilPlayerCharacter::HandleControllerChanged);
	
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 300.0f;
	CameraBoom->bUsePawnControlRotation = true;
	
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom);
}

void ASigilPlayerCharacter::HandleControllerChanged(APawn* Pawn, AController* OldController,
	AController* NewController)
{
	APlayerController* PlayerController = Cast<APlayerController>(NewController);
	if (PlayerController)
	{
		UEnhancedInputLocalPlayerSubsystem* Subsytem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());
		if (Subsytem)
		{
			Subsytem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
}

// Called to bind functionality to input
void ASigilPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ThisClass::Move);
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ThisClass::Look);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);
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