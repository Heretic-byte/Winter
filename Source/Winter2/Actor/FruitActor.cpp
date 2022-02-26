#include "FruitActor.h"

#include "Pawn/Character/Winter2Character.h"
#include "Winter2/MyLib.h"
#include "Winter2/Winter2.h"

// Sets default values
AFruitActor::AFruitActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	m_fFoddExp = 1;
}

// Called when the game starts or when spawned
void AFruitActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFruitActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AFruitActor::OnInteract()
{
	PRINTF("AFruitActor::OnInteract()");

	UMyLib::GetPlayer()->m_OnTakeExp.Broadcast(m_fFoddExp);
}