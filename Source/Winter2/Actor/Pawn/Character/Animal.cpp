#include "Animal.h"

#include "AIController.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PawnMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Winter2/Winter2.h"
#include "Winter2/Managers/MyGameInstance.h"

AAnimal::AAnimal()
{
	bUseControllerRotationYaw = false;

	GetCharacterMovement()->bUseControllerDesiredRotation = true;
	GetCharacterMovement()->RotationRate = FRotator(0,0,240);

	m_SoundComp = CreateDefaultSubobject<UAudioComponent>(TEXT("m_SoundComp"));
	m_SoundComp->SetupAttachment(RootComponent);
	m_SoundComp->SetAutoActivate(false);
}

void AAnimal::BeginPlay()
{
	Super::BeginPlay();

	UMyGameInstance::Get->m_SpawnManager->RegisterActor(this);

	check(m_ClassAI);

	m_AiInst = NewObject<UAI_Base>(this,m_ClassAI);

	m_AiInst->Init(this);

	m_Sensor = NewObject<USensor_Base>(this);

	m_Sensor->Init(this, m_fVisionRange,m_fVisionAngle);

	GetCharacterMovement()->MaxWalkSpeed = m_fMoveSpeed;
	
}

void AAnimal::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	m_AiInst->Tick(DeltaSeconds);
}

void AAnimal::SetFocusedTarget(ABaseCharacter* pawn)
{
	m_Target = pawn;
}

ABaseCharacter* AAnimal::GetFocusedTarget()
{
	return m_Target.Get();
}

float AAnimal::GetAttackRange()
{
	return m_fAtkRange;
}

UPathFollowingComponent* AAnimal::GetPfComp()
{
	AAIController* AAi = Cast<AAIController>(GetController());
	
	return AAi->GetPathFollowingComponent();
}

EPathFollowingRequestResult::Type AAnimal::MoveToLocation(FVector loc)
{
	AAIController* AAi = Cast<AAIController>(GetController());

	return AAi->MoveToLocation(loc);
}

EPathFollowingRequestResult::Type AAnimal::MoveToActor(AActor* target)
{
	AAIController* AAi = Cast<AAIController>(GetController());

	return AAi->MoveToActor(target,80);
}

void AAnimal::HomingRotateToTarget()
{
	FRotator NewRot = GetActorRotation();

	NewRot.Yaw = UKismetMathLibrary::RInterpTo(
		NewRot, UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), Cast<AActor>(GetFocusedTarget())->GetActorLocation()),
		GetWorld()->GetDeltaSeconds(), 5.5f).Yaw;

	SetActorRotation(NewRot);
}

void AAnimal::TryAttack()
{
	PRINTF("AAnimal::TryAttack()");
}

void AAnimal::StopMove()
{
	GetMovementComponent()->StopMovementImmediately();

	GetPfComp()->AbortMove(*this, FPathFollowingResultFlags::ForcedScript | FPathFollowingResultFlags::NewRequest,FAIRequestID::CurrentRequest, EPathFollowingVelocityMode::Keep);
}

void AAnimal::OnHpZero()
{
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	GetMovementComponent()->SetComponentTickEnabled(false);
	
	if(m_DeathMontage)
	{
		PlayAnimMontage(m_DeathMontage);

		float AnimLength = m_DeathMontage->GetPlayLength() - 0.4f;

		GetWorldTimerManager().SetTimer(m_DeathAnimTimer, this, &AAnimal::OnDeathAnimEnd, AnimLength, false);
	}
	else
	{
		OnDeathAnimEnd();
	}
}

void AAnimal::OnDeathAnimEnd()
{
	SetFocusedTarget(nullptr);
	
	GetMesh()->bPauseAnims = true;
	
	GetMesh()->SetSimulatePhysics(true);

	PRINTF("AAnimal::OnDeathAnimEnd()");
}

void AAnimal::TakeDmg(float dmg)
{
	Super::TakeDmg(dmg);

	m_SoundComp->Play();
	
	if(IsAlive())
	{
		
	}
	//PlaySound
}
