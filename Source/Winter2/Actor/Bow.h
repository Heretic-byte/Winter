// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Bow.generated.h"

class AWinter2Projectile;
UCLASS()
class WINTER2_API ABow : public AActor
{
	GENERATED_BODY()
	
public:	
	ABow();

protected:
	UPROPERTY(VisibleAnywhere)
	USkeletalMeshComponent* m_BowMesh;
	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	TSubclassOf<AWinter2Projectile> m_ClassBullet;
	UPROPERTY()
	AWinter2Projectile* m_Bullet;
	UPROPERTY(EditAnywhere)
	TSubclassOf<UAnimInstance> m_ClassAnim;
	
	UPROPERTY()
	float m_fCharge;
	UPROPERTY()
	bool m_bIsCharging;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	FVector GetBulletStartPoint();

public:
	void BeginCharge();

	void EndCharge();

	void StopCharge();

	void Reload();

	float GetCharge();
};
