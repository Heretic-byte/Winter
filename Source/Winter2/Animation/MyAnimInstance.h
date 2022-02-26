// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "Animation/AnimInstanceProxy.h"
#include "MyAnimInstance.generated.h"


class ABaseCharacter;
class UMyAnimInstance;

USTRUCT(BlueprintType)
struct FMyAnimInstanceProxy : public FAnimInstanceProxy
{
	GENERATED_BODY()
	
public:
	virtual void InitializeObjects(UAnimInstance* InAnimInstance) override;

	virtual void Update(float DeltaSeconds) override ;

	UPROPERTY(Transient)
	UMyAnimInstance* m_MyAnim = nullptr;
};

UCLASS()
class WINTER2_API UMyAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	UPROPERTY(Transient, BlueprintReadOnly,meta = (AllowPrivateAccess = "true"))
	FMyAnimInstanceProxy m_Proxy;
	UPROPERTY()
	ABaseCharacter* m_Owner;
	UPROPERTY(Transient,VisibleAnywhere,BlueprintReadWrite)
	float m_fSpeedPercent;
public:
	virtual void NativeBeginPlay() override;

	virtual void NativeInitializeAnimation() override;
	
	virtual FAnimInstanceProxy* CreateAnimInstanceProxy() override
	{
		return &m_Proxy;
	}
	
	virtual void DestroyAnimInstanceProxy(FAnimInstanceProxy* InProxy) override {}

	virtual void UpdateFlags();
};
