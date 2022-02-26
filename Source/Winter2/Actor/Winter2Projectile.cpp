// Copyright Epic Games, Inc. All Rights Reserved.

#include "Winter2Projectile.h"

#include "Components/AudioComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"
#include "Pawn/Character/Animal.h"
#include "Pawn/Character/Winter2Character.h"
#include "Winter2/MyLib.h"

AWinter2Projectile::AWinter2Projectile() 
{
	CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	CollisionComp->InitSphereRadius(10.0f);
	CollisionComp->BodyInstance.SetCollisionProfileName("Projectile");
	CollisionComp->OnComponentHit.AddDynamic(this, &AWinter2Projectile::OnHit);		// set up a notification for when this component hits something blocking
	CollisionComp->SetWalkableSlopeOverride(FWalkableSlopeOverride(WalkableSlope_Unwalkable, 0.f));
	CollisionComp->CanCharacterStepUpOn = ECB_No;
	RootComponent = CollisionComp;
	
	static ConstructorHelpers::FObjectFinder<UStaticMesh> Found(TEXT("StaticMesh'/Game/JungHo_Works/Arrow.Arrow'"));

	m_Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("m_Mesh"));
	m_Mesh->SetupAttachment(RootComponent);
	m_Mesh->SetStaticMesh(Found.Object);
	m_Mesh->SetRelativeScale3D(FVector(1,5,5));
	m_Mesh->SetRelativeRotation(FRotator(0,0,0));
	m_Mesh->SetRelativeLocation(FVector(-70,0,0));
	m_Mesh->SetCollisionProfileName(TEXT("NoCollision"));
	//m_Mesh->SetCollisionProfileName(TEXT("Projectile"));
	//
	m_ProMove = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("m_ProMove"));
	m_ProMove->SetUpdatedComponent(RootComponent);
	m_ProMove->bRotationFollowsVelocity = true;
	m_ProMove->bSimulationEnabled = false;
	m_Mesh->OnComponentHit.AddDynamic(this, &AWinter2Projectile::OnHit);

	m_SoundComp = CreateDefaultSubobject<UAudioComponent>(TEXT("m_SoundComp"));
	m_SoundComp->SetupAttachment(RootComponent);
	m_SoundComp->SetAutoActivate(false);
}

void AWinter2Projectile::Fire(float powerMaxOne)
{
	FDetachmentTransformRules Rules(EDetachmentRule::KeepWorld,true);

	DetachFromActor(Rules);
	
	FVector Forward = GetActorForwardVector();

	float Lerp = FMath::Lerp(100,4000,powerMaxOne);

	m_ProMove->bSimulationEnabled = true;
	
	m_ProMove->Velocity = Forward * Lerp;
}

void AWinter2Projectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (Cast<AWinter2Character>(Hit.Actor))
	{
		return;
	}

	FAttachmentTransformRules Rules(EAttachmentRule::KeepWorld,EAttachmentRule::KeepWorld,EAttachmentRule::KeepWorld,true);
	
	AAnimal* Mob = Cast<AAnimal>(Hit.Actor);

	if(Mob)
	{
		FName BondName = Mob->GetMesh()->FindClosestBone(Hit.Location);
		
		AttachToComponent(Mob->GetMesh(),Rules,BondName);

		FDamageEvent Event;

		Mob->TakeDamage(1,Event,UMyLib::GetPlayerCon(),UMyLib::GetPlayer());
		
		m_SoundComp->Play();
	}
	else
	{
		AttachToComponent(OtherComp,Rules);	
	}

	OtherActor->OnDestroyed.AddDynamic(this, &AWinter2Projectile::OnAttachedActorDelete);

	CollisionComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void AWinter2Projectile::OnAttachedActorDelete(AActor* destroyedActor)
{
	Destroy();
}
