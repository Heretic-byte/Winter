// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/CapsuleComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Actor.h"
#include "Winter2/Interactable.h"
#include "FruitActor.generated.h"

UCLASS()
class WINTER2_API AFruitActor : public AActor, public IInteractable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFruitActor();

protected:
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float m_fFoddExp;
	UPROPERTY(VisibleAnywhere,BlueprintReadWrite)
	UCapsuleComponent* m_Coll;
	UPROPERTY(VisibleAnywhere,BlueprintReadWrite)
	UStaticMeshComponent* m_Mesh;
	
public:	
	virtual void OnInteract() override;
};


