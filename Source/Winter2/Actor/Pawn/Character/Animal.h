// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseCharacter.h"
#include "Navigation/PathFollowingComponent.h"
#include "Winter2/Interactable.h"
#include "Winter2/AI_Logic/AI_Base.h"
#include "Winter2/AI_Logic/AI_Flee.h"
#include "Winter2/AI_Logic/Sensor_Base.h"
#include "Animal.generated.h"

/**
 * 
 */
UCLASS()
class WINTER2_API AAnimal : public ABaseCharacter,public IInteractable
{
	GENERATED_BODY()

public:
	AAnimal();

protected:
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "APawn Animal Stats")
	TSubclassOf<UAI_Base> m_ClassAI;
	UPROPERTY()
	UAI_Base* m_AiInst;
	UPROPERTY()
	USensor_Base* m_Sensor;

	TWeakObjectPtr<ABaseCharacter> m_Target;

	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "APawn Animal Stats")
	float m_fAtkRange;
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "APawn Animal Stats")
	float m_fAtkDmg;
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "APawn Animal Stats")
	float m_fVisionRange;
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "APawn Animal Stats")
	float m_fVisionAngle;
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "APawn Animal Stats")
	float m_fFoodExp;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UAudioComponent* m_SoundComp;
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "APawn Animal Stats")
	UAnimMontage* m_TakeHitMontage;
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "APawn Animal Stats")
	UAnimMontage* m_DeathMontage;
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "APawn Animal Stats")
	UAnimMontage* m_AttackMontage;

	FTimerHandle m_DeathAnimTimer;

	float m_fAttackTimer;

	float m_fDeltaTime;
	
protected:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;

public:
	void SetFocusedTarget(ABaseCharacter* pawn);

	ABaseCharacter* GetFocusedTarget();
	
	float GetAttackRange();

	UPathFollowingComponent* GetPfComp();
	
	EPathFollowingRequestResult::Type MoveToLocation(FVector loc);
	
	EPathFollowingRequestResult::Type MoveToActor(AActor* target);
	
	void HomingRotateToTarget();
	
	void TryAttack();

	void DealDamage();
	
	void StopMove();

	virtual void OnHpZero() override;

	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	void OnDeathAnimEnd();

	virtual bool HasTarget() override;

	virtual void OnInteract() override;
};



