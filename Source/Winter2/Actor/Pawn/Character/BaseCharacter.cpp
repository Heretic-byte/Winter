// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseCharacter.h"

#include "GameFramework/PawnMovementComponent.h"

// Sets default values
ABaseCharacter::ABaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	GetMesh()->SetRelativeLocation(FVector(0, 0, -88));
	GetMesh()->SetRelativeRotation(FRotator(0, -90.f, 0.f));

	m_fHealth = 100;
	m_fMoveSpeed = 600;
}

// Called when the game starts or when spawned
void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

bool ABaseCharacter::IsAlive()
{
	return true;
}

bool ABaseCharacter::LineOfSightTo(const AActor* pawn)
{
	if (!pawn)
	{
		return false;
	}

	FVector ViewPoint = GetActorLocation();

	FCollisionQueryParams CollisionParms(SCENE_QUERY_STAT(LineOfSight), false, pawn);
	
	CollisionParms.AddIgnoredActor(this);
	
	FVector TargetLocation = pawn->GetActorLocation();
	
	bool bHit = GetWorld()->LineTraceTestByChannel(ViewPoint, TargetLocation, ECC_Visibility, CollisionParms);
	
	return !bHit;
}

void ABaseCharacter::SetActive(bool isActive)
{
	SetHidden(!isActive);

	SetActorTickEnabled(isActive);
	
	for(auto Comp : GetComponents())
	{
		Comp->Activate(isActive);
		Comp->SetComponentTickEnabled(isActive);
	}
}

float ABaseCharacter::GetSpeedPercentOne()
{
	float MaxSqr = GetMovementComponent()->GetMaxSpeed() * GetMovementComponent()->GetMaxSpeed();

	float VelSqr = GetMovementComponent()->Velocity.SizeSquared(); 
	
	return  VelSqr / MaxSqr;
}
