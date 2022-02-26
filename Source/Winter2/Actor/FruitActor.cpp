#include "FruitActor.h"

#include "Pawn/Character/Winter2Character.h"
#include "Winter2/MyLib.h"
#include "Winter2/Winter2.h"

// Sets default values
AFruitActor::AFruitActor()
{
	PrimaryActorTick.bCanEverTick = false;

	m_fFoddExp = 1;

	m_Coll = CreateDefaultSubobject<UCapsuleComponent>(TEXT("m_Coll"));
	m_Coll->InitCapsuleSize(60,130);
	m_Coll->SetCollisionProfileName(TEXT("OverlapAll"));
	m_Coll->SetCollisionResponseToChannel(ECollisionChannel::ECC_Visibility,ECollisionResponse::ECR_Block);
	RootComponent = m_Coll;

	m_Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("m_Mesh"));
	m_Mesh->SetupAttachment(m_Coll);
	m_Mesh->SetCollisionProfileName(TEXT("NoCollision"));
}

void AFruitActor::OnInteract()
{
	PRINTF("AFruitActor::OnInteract()");

	UMyLib::GetPlayer()->m_OnTakeExp.Broadcast(m_fFoddExp);

	Destroy();
}