// Fill out your copyright notice in the Description page of Project Settings.


#include "Sensor_Base.h"

#include "TimerManager.h"
#include "Engine/Engine.h"

#include "Perception/AISense_Hearing.h"
#include "Perception/AISense_Team.h"
#include "Perception/PawnSensingComponent.h"
#include "Winter2/MyLib.h"
#include "Winter2/Actor/Pawn/Character/Animal.h"
#include "Winter2/Actor/Pawn/Character/Winter2Character.h"


USensor_Base::USensor_Base()
{
	m_SensingInterval = 0.3f;
}

void USensor_Base::Init(AAnimal* owner, float range, float angle)
{
	m_Owner=owner;
	
	SetSensingUpdatesEnabled(true);

	m_fSightAngle = angle;

	m_fSightRadius = range;

	m_fSightRadiusSqr = m_fSightRadius * m_fSightRadius; 
}

void USensor_Base::SetSensingUpdatesEnabled(const bool bEnabled)
{
	if (bEnabled && m_SensingInterval > 0.f)
	{
		const float InitialDelay = (m_SensingInterval * FMath::SRand()) + KINDA_SMALL_NUMBER;
		SetTimer(InitialDelay);
	}
	else
	{
		SetTimer(0.f);
	}
}


void USensor_Base::SetTimer(const float TimeInterval)
{
	if (m_Owner && GEngine->GetNetMode(GetWorld()) < NM_Client)
	{
		m_Owner->GetWorldTimerManager().SetTimer(TimerHandle_OnTimer, this, &USensor_Base::OnTimer,
		                                         TimeInterval,
		                                         false);
	}
}


void USensor_Base::SetSensingInterval(const float NewSensingInterval)
{
	if (m_SensingInterval != NewSensingInterval)
	{
		m_SensingInterval = NewSensingInterval;

		if (m_Owner)
		{
			if (m_SensingInterval <= 0.f)
			{
				SetTimer(0.f);
			}
			else
			{
				float CurrentElapsed = m_Owner->GetWorldTimerManager().GetTimerElapsed(TimerHandle_OnTimer);

				CurrentElapsed = FMath::Max(0.f, CurrentElapsed);

				if (CurrentElapsed < m_SensingInterval)
				{
					SetTimer(m_SensingInterval - CurrentElapsed);
				}
				else if (CurrentElapsed > m_SensingInterval)
				{
					SetTimer(KINDA_SMALL_NUMBER);
				}
			}
		}
	}
}


void USensor_Base::OnTimer()
{
	if (!m_Owner || !m_Owner->GetWorld())
	{
		return;
	}

	UpdateAISensing();

	SetTimer(m_SensingInterval);
};


bool USensor_Base::HasLineOfSightTo(const AActor* Other) const
{
	return m_Owner->LineOfSightTo(Other);
}

void USensor_Base::UpdateAISensing()
{
	if (m_Owner->GetFocusedTarget())
	{
		return;
	}
	ABaseCharacter* Pawn = GetSensedPawn();

	if (Pawn)
	{
		if (m_Owner->GetFocusedTarget() == Pawn)
		{
			return;
		}

		if(!CheckDistAndAngle(Pawn))
		{
			return;
		}

		m_Owner->SetFocusedTarget(Pawn);
	}
	else //안보일땐 이게되야함
		{
		if (m_Owner->GetFocusedTarget())
		{
			{
				m_Owner->SetFocusedTarget(nullptr); //FSM에서 OnFOcusLike,OnFOcusHate	
			}
		}
		}
}

FVector USensor_Base::GetSensorLocation() const
{
	FVector SensorLocation(FVector::ZeroVector);
	const AActor* SensorActor = GetSensorActor();

	if (SensorActor)
	{
		FRotator ViewRotation;
		SensorActor->GetActorEyesViewPoint(SensorLocation, ViewRotation);
	}

	return SensorLocation;
}

FRotator USensor_Base::GetSensorRotation() const
{
	FRotator SensorRotation(FRotator::ZeroRotator);

	const AActor* SensorActor = GetSensorActor();

	if (SensorActor)
	{
		SensorRotation = SensorActor->GetActorRotation();
	}

	return SensorRotation;
}


bool USensor_Base::CheckIsHidden(const APawn* Pawn) const
{
	return Pawn->IsHidden();
}

AActor* USensor_Base::GetSensorActor() const
{
	return m_Owner;
}

bool USensor_Base::IsSensorActor(const AActor* Actor) const
{
	return (Actor == GetSensorActor());
}

bool USensor_Base::CheckDistAndAngle(const ABaseCharacter* Other)
{
	if (!Other)
	{
		return false;
	}

	if(!HasLineOfSightTo(Other))
	{
		return false;
	}

	if(!UMyLib::CheckRange(m_Owner,Other,m_fSightRadiusSqr))
	{
		return false;
	}
	
	return UMyLib::CheckAngle(m_Owner,Other,m_fSightAngle);;
}

ABaseCharacter* USensor_Base::GetSensedPawn()
{
	AWinter2Character* Player = UMyLib::GetPlayer();
	
	if (Player&&CheckIsHidden(Player))
	{
		return nullptr;
	}
	
	return Player;
}
