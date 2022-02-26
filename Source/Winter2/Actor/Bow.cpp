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
	static ConstructorHelpers::FClassFinder<UAnimInstance> BowAnim(TEXT("AnimBlueprint'/Game/JungHo_Works/ABP_BowAnim.ABP_BowAnim_C'"));

	m_ClassAnim = BowAnim.Class;
	//AnimBlueprint'/Game/JungHo_Works/ABP_BowAnim.ABP_BowAnim'
	
	m_BowMesh->SetSkeletalMesh(BowMesh.Object);

	m_Bullet = nullptr;

	m_ClassBullet = AWinter2Projectile::StaticClass();

	m_BowMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	//SkeletalMesh'/Game/JungHo_Works/Bow.Bow'
	m_fCharge = 0;
	m_bIsCharging=false;
}

// Called when the game starts or when spawned
void ABow::BeginPlay()
{
	Super::BeginPlay();

	m_BowMesh->SetAnimationMode(EAnimationMode::AnimationBlueprint);
	m_BowMesh->SetAnimClass(m_ClassAnim);

	Reload();
}

// Called every frame
void ABow::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(m_bIsCharging && m_fCharge < 1.f)
	{
		m_fCharge+=DeltaTime;
		PRINTF("Charge:%.1f",m_fCharge);
	}
}

void ABow::BeginCharge()
{
	m_fCharge = 0;

	m_bIsCharging=true;
}

void ABow::EndCharge()
{
	if(m_fCharge<0.15f)
	{
		PRINTF("Cancel Charge");
		StopCharge();
		return;
	}
	PRINTF("Fire:%.1f",m_fCharge);
	m_Bullet->Fire(m_fCharge);
	m_Bullet = nullptr;
	
	StopCharge();
	
	Reload();
}

void ABow::StopCharge()
{
	m_fCharge = 0;
	m_bIsCharging=false;
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

float ABow::GetCharge()
{
	return m_fCharge;
}

