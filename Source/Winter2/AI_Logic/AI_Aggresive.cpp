// Fill out your copyright notice in the Description page of Project Settings.


#include "AI_Aggresive.h"



#include "AI_Flee.h"

#include "NavigationSystem.h"
#include "Navigation/PathFollowingComponent.h"
#include "Winter2/Winter2.h"
#include "Winter2/Actor/Pawn/Character/Animal.h"
#include "Winter2/Actor/Pawn/Character/BaseCharacter.h"

void UAI_Aggresive::Init(AAnimal* pawnUnit)
{
	Super::Init(pawnUnit);

	m_fIdleTimer = -1.f;

	m_fChaseFindTimer = -1.f;

	m_CurrentState = EFSM::Idle;

	m_fAttackRange = pawnUnit->GetAttackRange();

	m_fAttackRangeSqr = m_fAttackRange * m_fAttackRange;
	//
	m_AryStateFunction[static_cast<int>(EFSM::Idle)] = &UAI_Aggresive::OnIdle;

	m_AryStateFunction[static_cast<int>(EFSM::Chase)] = &UAI_Aggresive::OnChase;

	m_AryStateFunction[static_cast<int>(EFSM::Combat)] = &UAI_Aggresive::OnCombat;
	//
	ResetStartPosition(m_Owner->GetActorLocation());
}

void UAI_Aggresive::Tick(float deltaTime)
{
	m_fDeltaTime = deltaTime;

	CheckSetState();

	(this->*m_AryStateFunction[static_cast<int>(m_CurrentState)])();

	PRINT3DF(m_Owner->GetActorLocation(),"%s",*CurrentState());
}

void UAI_Aggresive::SetIdle()
{
	if (m_CurrentState == EFSM::Idle)
	{
		return;
	}
	m_CurrentState = EFSM::Idle;

	m_Owner->SetFocusedTarget(nullptr);
		
	m_Owner->StopMove();
}

void UAI_Aggresive::CheckSetState()
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

		if (!CheckTargetRange(m_fAttackRangeSqr))
		{
			m_CurrentState = EFSM::Chase;
			return;
		}	

		m_CurrentState = EFSM::Combat;
	}
}

FString UAI_Aggresive::CurrentState()
{
	switch (m_CurrentState)
	{
	case Idle: return TEXT("Idle");
		break;
	case Chase: return TEXT("Chase");
		break;
	case Combat: return TEXT("Combat");
		break;
	}

	return TEXT("None");
}

void UAI_Aggresive::OnIdle()
{
	EPathFollowingStatus::Type Status = m_Owner->GetPfComp()->GetStatus();

	if (m_fIdleTimer > 0.f)
	{
		m_fIdleTimer -= m_fDeltaTime;

		return;
	}

	int RandIndex = FMath::RandRange(0,4);

	if(RandIndex == 0)
	{
		m_Owner->PlayRandIdleMotion();
		m_fIdleTimer = FMath::FRandRange(3.f, 7.f);
		return;
	}

	FNavLocation Result;

	UNavigationSystemV1* NavSys = FNavigationSystem::GetCurrent<UNavigationSystemV1>(GetWorld());

	if (EPathFollowingStatus::Idle == Status)
	{
		if (!NavSys->GetRandomPointInNavigableRadius(m_StartPoint, 400.f, Result))
		{
			return;
		}

		m_Owner->MoveToLocation(Result);

		m_fIdleTimer = FMath::FRandRange(3.f, 7.f);
	}
}

void UAI_Aggresive::OnChase()
{
	EPathFollowingRequestResult::Type Result = EPathFollowingRequestResult::Failed;

	Result = m_Owner->MoveToActor(m_Owner->GetFocusedTarget());
}

void UAI_Aggresive::OnCombat()
{
	m_Owner->HomingRotateToTarget();

	if(CheckAngle(60))
	{
		m_Owner->TryAttack();
	}
}

void UAI_Aggresive::ResetStartPosition(FVector loc)
{
	m_StartPoint = loc;
}
