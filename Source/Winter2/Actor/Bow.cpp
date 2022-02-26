// Fill out your copyright notice in the Description page of Project Settings.


#include "Bow.h"

#include "Winter2Projectile.h"
#include "Winter2/Winter2.h"

// Sets default values
ABow::ABow()
{
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	
	m_BowMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("m_BowMesh"));
	m_BowMesh->SetupAttachment(RootComponent);
	m_BowMesh->bCastDynamicShadow = false;
	m_BowMesh->CastShadow = false;
	m_BowMesh->SetRelativeRotation(FRotator(0, -90.f, 0.f));

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> BowMesh(TEXT("SkeletalMesh'/Game/JungHo_Works/Bow.Bow'"));
	
	m_BowMesh->SetSkeletalMesh(BowMesh.Object);

	m_Bullet = nullptr;

	m_ClassBullet = AWinter2Projectile::StaticClass();

	m_BowMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	//SkeletalMesh'/Game/JungHo_Works/Bow.Bow'
}

// Called when the game starts or when spawned
void ABow::BeginPlay()
{
	Super::BeginPlay();

	Reload();
}

// Called every frame
void ABow::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABow::BeginCharge()
{
}

void ABow::EndCharge()
{
	Fire();
}

void ABow::StopCharge()
{
	
}

void ABow::Fire()
{
	PRINTF("ABow::Fire()");
	
	m_Bullet->Fire(0.7f);
}

FVector ABow::GetBulletStartPoint()
{
	return m_BowMesh->GetSocketLocation(TEXT("Start"));
}

void ABow::Reload()
{
	FVector SpawnLoc = GetBulletStartPoint();

	FRotator SpawnRot = FRotator::ZeroRotator;
	
	FActorSpawnParameters Param;

	Param.bNoFail = true;
	
	m_Bullet = GetWorld()->SpawnActor<AWinter2Projectile>(m_ClassBullet,SpawnLoc,SpawnRot,Param);

	FAttachmentTransformRules Rules(EAttachmentRule::SnapToTarget,EAttachmentRule::SnapToTarget,EAttachmentRule::KeepWorld,true);

	m_Bullet->AttachToComponent(m_BowMesh,Rules,TEXT("Start"));
}

