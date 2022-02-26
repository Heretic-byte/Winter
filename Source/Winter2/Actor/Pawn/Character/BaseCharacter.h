// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BaseCharacter.generated.h"

UCLASS()
class WINTER2_API ABaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABaseCharacter();

protected:
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "APawn Stats")
	float m_fHealth;
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "APawn Stats")
	float m_fMoveSpeed;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	bool IsAlive();
	
	bool LineOfSightTo(const AActor* pawn);
	
	void SetActive(bool isActive);
};
