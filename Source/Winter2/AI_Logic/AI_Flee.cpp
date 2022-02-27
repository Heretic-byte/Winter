

#include "AI_Flee.h"

#include "NavigationSystem.h"
#include "Navigation/PathFollowingComponent.h"
#include "Winter2/MyLib.h"
#include "Winter2/Winter2.h"
#include "Winter2/Actor/Pawn/Character/Animal.h"
#include "Winter2/Actor/Pawn/Character/BaseCharacter.h"

void UAI_Flee::Init(AAnimal* pawnUnit)
{
	Super::Init(pawnUnit);

	m_fIdleTimer = -1.f;

	m_fFleeTimer = -1.f;

	m_CurrentState = EFSM::Idle;

	m_fAttackRange = pawnUnit->GetAttackRange();

	m_fAttackRangeSqr = m_fAttackRange * m_fAttackRange;
	//
	m_AryStateFunction[static_cast<int>(EFSM::Idle)] = &UAI_Flee::OnIdle;

	m_AryStateFunction[static_cast<int>(EFSM::Flee)] = &UAI_Flee::OnFlee;

	ResetStartPosition(m_Owner->GetActorLocation());
}

void UAI_Flee::Tick(float deltaTime)
{
	m_fDeltaTime = deltaTime;

	CheckSetState();

	(this->*m_AryStateFunction[static_cast<int>(m_CurrentState)])();

	PRINT3DF(m_Owner->GetActorLocation(),"%s",*CurrentState());
}

void UAI_Flee::SetIdle()
{
	if (m_CurrentState == EFSM::Idle)
	{
		return;
	}
	m_CurrentState = EFSM::Idle;

	m_Owner->SetFocusedTarget(nullptr);
		
	//m_Owner->StopMove();
}

void UAI_Flee::CheckSetState()
{
	if (!m_Owner->GetFocusedTarget())
	{
		SetIdle();
	}
	else
	{
		ABaseCharacter* TargetNPC =  Cast<ABaseCharacter>(m_Owner->GetFocusedTarget());

		if (!TargetNPC->IsAlive())
		{
			SetIdle();

			return;
		}

		if ( m_CurrentState == EFSM::Flee && !CheckTargetRange(m_fAttackRangeSqr))
		{
			SetIdle();
		}
		else
		{
			m_CurrentState = EFSM::Flee;
		}
	}
}

FString UAI_Flee::CurrentState()
{
	switch (m_CurrentState)
	{
	case Idle: return TEXT("Idle");
		break;
	case Flee: return TEXT("Flee");
		break;
	}
	return TEXT("None");
}

void UAI_Flee::OnIdle()
{
	EPathFollowingStatus::Type Status = m_Owner->GetPfComp()->GetStatus();

	if (m_fIdleTimer > 0.f)
	{
		m_fIdleTimer -= m_fDeltaTime;

		return;
	}

	int RandIndex = FMath::RandRange(0,4);

	if(RandIndex == 0  && m_Owner->PlayRandIdleMotion())
	{
		m_Owner->PlayRandIdleMotion();
		m_fIdleTimer = FMath::FRandRange(3.f, 7.f);
		return;
	}

	FNavLocation Result;

	if (EPathFollowingStatus::Idle == Status)
	{
		if (!UMyLib::GetNavSys()->GetRandomPointInNavigableRadius(m_StartPoint, 1400.f, Result))
		{
			return;
		}

		m_Owner->MoveToLocation(Result);

		m_fIdleTimer = FMath::FRandRange(3.f, 7.f);
	}
}

void UAI_Flee::OnFlee()
{
	if (m_fFleeTimer > 0.f)
	{
		m_fFleeTimer -= m_fDeltaTime;

		return;
	}
	FVector RunDir = (m_Owner->GetActorLocation() - m_Owner->GetFocusedTarget()->GetActorLocation()).GetSafeNormal2D();

	float RandDistLen = FMath::RandRange(1500,3000);

	float RandRad = FMath::RandRange(1700,2400);

	RunDir *= RandDistLen;

	FNavLocation Result;

	if (!UMyLib::GetNavSys()->GetRandomPointInNavigableRadius(m_Owner->GetActorLocation() + RunDir, RandRad, Result))
	{
		return;
	}
	
	m_fFleeTimer = FMath::FRandRange(1.f, 2.f);
	
	m_Owner->MoveToLocation(Result);
}

void UAI_Flee::ResetStartPosition(FVector loc)
{
	m_StartPoint = loc;
}
