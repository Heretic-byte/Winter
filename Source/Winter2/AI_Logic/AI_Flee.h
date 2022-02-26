// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AI_Base.h"
#include "AI_Flee.generated.h"

/**
 * 
 */
UCLASS()
class WINTER2_API UAI_Flee : public UAI_Base
{
	GENERATED_BODY()

	
public:
	enum EFSM
	{
		Idle,
		Flee,
		Length
	};

protected:
	EFSM m_CurrentState;

	FVector m_StartPoint;

	float m_fIdleTimer;

	float m_fFleeTimer;

	float m_fAttackRange; //from startPos

	float m_fAttackRangeSqr; //from startPos

	typedef void (UAI_Flee::*FPtrState)(void);

	FPtrState m_AryStateFunction[static_cast<int>(EFSM::Length)];

	float m_fDeltaTime;

protected:
	FString CurrentState();
	
	void CheckSetState();
	
	void OnIdle();

	virtual void OnFlee();
	
public:
	virtual void Init(AAnimal* owner) override;
	
	virtual void Tick(float delta) override;
	
	void SetIdle();

	void ResetStartPosition(FVector loc);
};
