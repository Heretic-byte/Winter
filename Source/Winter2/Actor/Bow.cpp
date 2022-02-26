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
	m_BowMesh->SetRelativeScale3D(FVector(0.2));
	//(X=0.650000,Y=0.650000,Z=0.650000)

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> BowMesh(TEXT("SkeletalMesh'/Game/NeetKing_Works/Model/SM_Bow/SM_Bow.SM_Bow'"));
	static ConstructorHelpers::FClassFinder<UAnimInstance> BowAnim(TEXT("AnimBlueprint'/Game/NeetKing_Works/Model/SM_Bow/ABP_NewBowAnim.ABP_NewBowAnim_C'"));

	m_ClassAnim = BowAnim.Class;
	
	m_BowMesh->SetSkeletalMesh(BowMesh.Object);

	m_Bullet = nullptr;

	m_ClassBullet = AWinter2Projectile::StaticClass();

	m_BowMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	//SkeletalMesh'/Game/JungHo_Works/Bow.Bow'
	m_fCharge = 0;
	m_bIsCharging=false;
	m_nArrowMaxCount = 5;

	m_SoundComp = CreateDefaultSubobject<UAudioComponent>(TEXT("m_SoundComp"));
	m_SoundComp->SetupAttachment(RootComponent);
	m_SoundComp->SetAutoActivate(false);

	static ConstructorHelpers::FObjectFinder<USoundBase> Sound01(TEXT("SoundWave'/Game/Audio/Audio_Arrow_Stand.Audio_Arrow_Stand'"));
	static ConstructorHelpers::FObjectFinder<USoundBase> Sound02(TEXT("SoundWave'/Game/Audio/Audio_Arrow_Shot.Audio_Arrow_Shot'"));

	m_ChargingSound = Sound01.Object;

	m_ShootingSound = Sound02.Object;
}

// Called when the game starts or when spawned
void ABow::BeginPlay()
{
	Super::BeginPlay();

	m_BowMesh->SetAnimationMode(EAnimationMode::AnimationBlueprint);
	m_BowMesh->SetAnimClass(m_ClassAnim);

	RecoverArrow();
}

// Called every frame
void ABow::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(m_bIsCharging && m_fCharge < 1.f)
	{
		m_fCharge+=DeltaTime;
	}
}

void ABow::BeginCharge()
{
	if(m_Bullet == nullptr)
	{
		return;
	}
	m_fCharge = 0;

	m_bIsCharging=true;

	PlayChargeSound();
}

void ABow::EndCharge()
{
	if(m_fCharge<0.15f)
	{
		PRINTF("Cancel Charge");
		StopCharge();
		return;
	}
	m_Bullet->Fire(m_fCharge);
	m_Bullet = nullptr;
	PlayShootSound();
	
	StopCharge();

	m_nArrowCount--;
	
	FTimerHandle Timer;

	GetWorldTimerManager().SetTimer(Timer, this, &ABow::Reload, 0.75, false);
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
	if (m_nArrowCount < 1 || m_Bullet != nullptr)
	{
		return;
	}
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

void ABow::SetMaxArrow(int maxArrow)
{
	m_nArrowMaxCount = maxArrow;
	PRINTF("ABow::SetMaxArrow:%d",m_nArrowMaxCount);
}

void ABow::SetCrnArrow(int crnArrow)
{
	m_nArrowCount = crnArrow;
	PRINTF("ABow::RecoverArrow:%d",m_nArrowCount);

	if(m_nArrowCount > 0 && m_Bullet == nullptr)
	{
		Reload();
	}
}

void ABow::RecoverArrow()
{
	SetCrnArrow(m_nArrowMaxCount);
}

int ABow::GetCrnArrowCount()
{
	return m_nArrowCount;
}

int ABow::GetMaxArrowCount()
{
	return m_nArrowMaxCount;
}

void ABow::PlayChargeSound()
{
	m_SoundComp->SetSound(m_ChargingSound);
	m_SoundComp->Play();
}

void ABow::PlayShootSound()
{
	m_SoundComp->SetSound(m_ShootingSound);
	m_SoundComp->Play();
}

