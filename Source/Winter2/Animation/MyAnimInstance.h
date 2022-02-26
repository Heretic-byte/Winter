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
	UPROPERTY(Transient,VisibleAnywhere,BlueprintReadWrite)
	bool m_bHasTarget;
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
//

class UBowAnimInstance;
class ABow;

USTRUCT(BlueprintType)
struct FBowAnimInstanceProxy : public FAnimInstanceProxy
{
	GENERATED_BODY()
	
public:
	virtual void InitializeObjects(UAnimInstance* InAnimInstance) override;

	virtual void Update(float DeltaSeconds) override ;

	UPROPERTY(Transient)
	UBowAnimInstance* m_MyAnim = nullptr;
	
};

UCLASS()
class WINTER2_API UBowAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	UPROPERTY(Transient, BlueprintReadOnly,meta = (AllowPrivateAccess = "true"))
	FBowAnimInstanceProxy m_Proxy;
	UPROPERTY()
	ABow* m_Owner;
	UPROPERTY(Transient,VisibleAnywhere,BlueprintReadWrite)
	float m_fChargePercent;
	
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
