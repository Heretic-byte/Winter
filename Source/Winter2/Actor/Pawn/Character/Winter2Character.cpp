// Copyright Epic Games, Inc. All Rights Reserved.

#include "Winter2Character.h"
#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/InputSettings.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"
#include "Winter2/Interactable.h"
#include "Winter2/Actor/Winter2Projectile.h"
#include "Winter2/Managers/MyGameInstance.h"

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
	FP_Bow->SetRelativeRotation(FRotator(0, -1.5, 0));
	FP_Bow->SetRelativeLocation(FVector(79.5, 45.6, -5.7));//(X=79.500000,Y=45.599998,Z=-5.700012)
	FP_Bow->SetChildActorClass(ABow::StaticClass());
	
	m_InterTarget = nullptr;

	static ConstructorHelpers::FObjectFinder<UParticleSystem> FoundEffect(TEXT("ParticleSystem'/Game/Effects/Fx_Snow/ParticleSystems/P_cameraParentedSnowBox.P_cameraParentedSnowBox'"));
	
	m_SnowEffect = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("m_SnowEffect"));
	m_SnowEffect->SetupAttachment(RootComponent);
	m_SnowEffect->SetTemplate(FoundEffect.Object);
}//ParticleSystem'/Game/Effects/Fx_Snow/ParticleSystems/P_cameraParentedSnowBox.P_cameraParentedSnowBox'

void AWinter2Character::BeginPlay()
{
	Super::BeginPlay();
	//InitBow(5);
}

void AWinter2Character::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	CheckTraceInteractable();
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
	PlayerInputComponent->BindAction("TryInteract", IE_Pressed, this, &AWinter2Character::TryInteract);
	PlayerInputComponent->BindAction("Charge", IE_Pressed, this, &AWinter2Character::OnBeginCharge);
	PlayerInputComponent->BindAction("Charge", IE_Released, this, &AWinter2Character::OnEndCharge);

	PlayerInputComponent->BindAxis("MoveForward", this, &AWinter2Character::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AWinter2Character::MoveRight);
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &AWinter2Character::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &AWinter2Character::LookUpAtRate);
}

float AWinter2Character::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator,
	AActor* DamageCauser)
{
	if(UMyGameInstance::Get->IsPlayerWin())
	{
		return 0;
	}
	return Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
}

void AWinter2Character::CheckTraceInteractable()
{
	FVector ViewPoint = FirstPersonCameraComponent->GetComponentLocation();

	FCollisionQueryParams CollisionParms(SCENE_QUERY_STAT(LineOfSight), false, this);
	
	CollisionParms.AddIgnoredActor(this);
	
	FVector TargetLocation = (FirstPersonCameraComponent->GetForwardVector() * 400) + ViewPoint;

	FHitResult Hits;
	
	if(!GetWorld()->LineTraceSingleByChannel(Hits,ViewPoint, TargetLocation, ECC_Visibility, CollisionParms))
	{
		m_InterTarget = nullptr;
		return;
	}
	
	IInteractable* Inter = Cast<IInteractable>(Hits.Actor);

	if(!Inter)
	{
		m_InterTarget = nullptr;
		return;
	}
	
	m_InterTarget = Inter;
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

int AWinter2Character::GetArrowCrnCount() const
{
	return m_Bow->GetCrnArrowCount();
}

int AWinter2Character::GetArrowMaxCount() const
{
	return m_Bow->GetMaxArrowCount();
}

void AWinter2Character::RecoverArrowCount() const
{
	m_Bow->RecoverArrow();
}

void AWinter2Character::SetArrowMaxCount(int max)
{
	m_Bow->SetMaxArrow(max);
}

void AWinter2Character::InitBow(int initMax)
{
	m_Bow =  Cast<ABow>(FP_Bow->GetChildActor());

	SetArrowMaxCount(initMax);
}

bool AWinter2Character::HasTarget()
{
	return m_InterTarget != nullptr;
}

void AWinter2Character::TryInteract()
{
	if(!m_InterTarget)
	{
		return;
	}

	m_InterTarget->OnInteract();
	m_InterTarget = nullptr;
}
