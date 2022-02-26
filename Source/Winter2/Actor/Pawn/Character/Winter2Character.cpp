// Copyright Epic Games, Inc. All Rights Reserved.

#include "Winter2Character.h"
#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/InputSettings.h"
#include "Kismet/GameplayStatics.h"
#include "Winter2/Actor/Winter2Projectile.h"

DEFINE_LOG_CATEGORY_STATIC(LogFPChar, Warning, All);

//////////////////////////////////////////////////////////////////////////
// AWinter2Character

AWinter2Character::AWinter2Character()
{
	GetCapsuleComponent()->InitCapsuleSize(25.f, 96.0f);

	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	// Create a CameraComponent	
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->SetRelativeLocation(FVector(-39.56f, 1.75f, 64.f)); // Position the camera
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

	FP_Bow = CreateDefaultSubobject<UChildActorComponent>(TEXT("m_Bow"));
	FP_Bow->SetupAttachment(FirstPersonCameraComponent);
	FP_Bow->SetRelativeRotation(FRotator(0, 0, 0));
	FP_Bow->SetRelativeLocation(FVector(79.5, 45.6, -5.7));//(X=79.500000,Y=45.599998,Z=-5.700012)
	FP_Bow->SetChildActorClass(ABow::StaticClass());
	
	GunOffset = FVector(100.0f, 0.0f, 10.0f);
}

void AWinter2Character::BeginPlay()
{
	Super::BeginPlay();
	
	m_Bow =  Cast<ABow>(FP_Bow->GetChildActor());
}

//////////////////////////////////////////////////////////////////////////
// Input

void AWinter2Character::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// set up gameplay key bindings
	check(PlayerInputComponent);
	// Bind jump events
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	// Bind fire event
	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &AWinter2Character::OnFire);
	PlayerInputComponent->BindAction("Charge", IE_Pressed, this, &AWinter2Character::OnBeginCharge);
	PlayerInputComponent->BindAction("Charge", IE_Released, this, &AWinter2Character::OnEndCharge);

	PlayerInputComponent->BindAxis("MoveForward", this, &AWinter2Character::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AWinter2Character::MoveRight);
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &AWinter2Character::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &AWinter2Character::LookUpAtRate);
}

void AWinter2Character::OnFire()
{
	
}

void AWinter2Character::OnBeginCharge()
{
	m_Bow->BeginCharge();
}

void AWinter2Character::OnEndCharge()
{
	m_Bow->EndCharge();
}

void AWinter2Character::MoveForward(float Value)
{
	if (Value != 0.0f)
	{
		// add movement in that direction
		AddMovementInput(GetActorForwardVector(), Value);
	}
}

void AWinter2Character::MoveRight(float Value)
{
	if (Value != 0.0f)
	{
		// add movement in that direction
		AddMovementInput(GetActorRightVector(), Value);
	}
}

void AWinter2Character::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void AWinter2Character::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}