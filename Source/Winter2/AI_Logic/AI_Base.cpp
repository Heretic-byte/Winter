// Fill out your copyright notice in the Description page of Project Settings.


#include "AI_Base.h"

#include "Winter2/MyLib.h"
#include "Winter2/Winter2.h"
#include "Winter2/Actor/Pawn/Character/Animal.h"
#include "Winter2/Actor/Pawn/Character/BaseCharacter.h"


void UAI_Base::Init(AAnimal* owner)
{
	m_Owner = owner;

	m_StartPos = m_Owner->GetActorLocation();
}

void UAI_Base::Tick(float delta)
{
	
};

bool UAI_Base::CheckTargetRange(float rangeSqr)
{
	return UMyLib::CheckRange(m_Owner,m_Owner->GetFocusedTarget(),rangeSqr);
}

bool UAI_Base::CheckAngle(float angleEuler)
{
	return UMyLib::CheckAngle(m_Owner,m_Owner->GetFocusedTarget(),angleEuler);
}
