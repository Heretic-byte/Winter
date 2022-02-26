// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Winter2/Actor/Pawn/Character/BaseCharacter.h"
#include "Sensor_Base.generated.h"

class AAnimal;
/**
 * 
 */
UCLASS()
class WINTER2_API USensor_Base : public UObject
{
	GENERATED_BODY()
	
protected:
	UPROPERTY()
	AAnimal* m_Owner;

	float m_SensingInterval;

	float m_fSightRadius;

	float m_fSightRadiusSqr;

	float m_fSightAngle;
public:
	DECLARE_DELEGATE_OneParam(FSeePawnDelegate, APawn*);
	DECLARE_DELEGATE_ThreeParams(FHearNoiseDelegate, APawn*, const FVector&, float);

public:
	USensor_Base();
	
	virtual void Init(AAnimal* owner, float range, float angle);
	//
    
	FTimerHandle TimerHandle_OnTimer;
	
protected:
	void OnTimer();

	void SetTimer(const float TimeDelay);

	virtual void UpdateAISensing();

	virtual bool CheckDistAndAngle(const ABaseCharacter* Other);

	ABaseCharacter* GetSensedPawn();

public:
	void SetSensingInterval(const float NewSensingInterval);

	void SetSensingUpdatesEnabled(const bool bEnabled);

	bool IsSensorActor(const AActor* Actor) const;

	bool CheckIsHidden(const APawn* Pawn) const;

	bool HasLineOfSightTo(const AActor* Other) const;

	FVector GetSensorLocation() const;

	FRotator GetSensorRotation() const;

	AActor* GetSensorActor() const; // Get the actor used as the actual sensor location is derived from this actor.
};
