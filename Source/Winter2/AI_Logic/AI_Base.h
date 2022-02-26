	// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "AI_Base.generated.h"

	class AAnimal;
/**
 * 
 */
UCLASS()
class WINTER2_API UAI_Base : public UObject
{
	GENERATED_BODY()

protected:
	UPROPERTY()
	AAnimal* m_Owner;

	FVector m_StartPos;

public:
	virtual void Init(AAnimal* owner);

	virtual void Tick(float delta);

	bool CheckTargetRange(float rangeSqr);

	bool CheckAngle(float angleEuler);
};
