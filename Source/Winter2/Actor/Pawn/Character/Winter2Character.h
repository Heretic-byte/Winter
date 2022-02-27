// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BaseCharacter.h"
#include "GameFramework/Character.h"
#include "Winter2/Interactable.h"
#include "Winter2/Actor/Bow.h"
#include "Winter2Character.generated.h"

class UInteractable;
class UInputComponent;
class USkeletalMeshComponent;
class USceneComponent;
class UCameraComponent;
class UMotionControllerComponent;
class UAnimMontage;
class USoundBase;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnTakeExp,float,amount);
UCLASS(config=Game)
class AWinter2Character : public ABaseCharacter
{
	GENERATED_BODY()

public:
	AWinter2Character();

public:
	UPROPERTY(BlueprintAssignable,BlueprintCallable,VisibleAnywhere,Category = "APawn Stats")
	FOnTakeExp m_OnTakeExp;
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseTurnRate;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseLookUpRate;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Gameplay)
	USoundBase* FireSound;
	UPROPERTY(VisibleAnywhere,BlueprintReadWrite, Category = Gameplay)
	UParticleSystemComponent* m_SnowEffect;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FirstPersonCameraComponent;
	UPROPERTY()
	ABow* m_Bow;

	IInteractable* m_InterTarget;
protected:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;

	void OnBeginCharge();

	void OnEndCharge();
	
	void MoveForward(float Val);

	void MoveRight(float Val);

	void TurnAtRate(float Rate);

	void LookUpAtRate(float Rate);

	virtual void SetupPlayerInputComponent(UInputComponent* InputComponent) override;

	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	void CheckTraceInteractable();

public:
	UCameraComponent* GetFirstPersonCameraComponent() const { return FirstPersonCameraComponent; }

	UFUNCTION(BlueprintCallable)
	int GetArrowCrnCount() const;

	UFUNCTION(BlueprintCallable)
	int GetArrowMaxCount() const;

	UFUNCTION(BlueprintCallable)
	void RecoverArrowCount() const;

	UFUNCTION(BlueprintCallable)
	void SetArrowMaxCount(int max);
	
	UFUNCTION(BlueprintCallable)
	void InitBow(int initMax);

	virtual bool HasTarget() override;

	void TryInteract();
};


