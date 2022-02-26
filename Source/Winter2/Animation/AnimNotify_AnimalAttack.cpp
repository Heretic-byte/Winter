#include "AnimNotify_AnimalAttack.h"

#include "Winter2/Actor/Pawn/Character/Animal.h"


void UAnimNotify_AnimalAttack::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);

	AAnimal* AnimalOwner = Cast<AAnimal>( MeshComp->GetOwner());

	if(!AnimalOwner)
	{
		return;
	}

	AnimalOwner->DealDamage();
}
