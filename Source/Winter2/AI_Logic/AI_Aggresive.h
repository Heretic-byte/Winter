// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AI_Base.h"
#include "AI_Aggresive.generated.h"

/**
 * 
 */
UCLASS()
class WINTER2_API UAI_Aggresive : public UAI_Base
{
	GENERATED_BODY()

public:
	enum EFSM
	{
		Idle,
		Chase,
		Combat,
		Length
	};

protected:
	EFSM m_CurrentState;

	FVector m_StartPoint;

	float m_fIdleTimer;

	float m_fChaseFindTimer;

	float m_fAttackRange; //from startPos

	float m_fAttackRangeSqr; //from startPos

	typedef void (UAI_Aggresive::*FPtrState)(void);

	FPtrState m_AryStateFunction[static_cast<int>(EFSM::Length)];

	float m_fDeltaTime;

protected:
	FString CurrentState();
	
	void CheckSetState();
	
	void OnIdle();

	void OnChase();
	
	void OnCombat();

public:
	virtual void Init(AAnimal* owner) override;
	
	virtual void Tick(float delta) override;
	
	void SetIdle();

	void ResetStartPosition(FVector loc);
};
