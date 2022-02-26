#include "MyAnimInstance.h"

#include "Winter2/Actor/Pawn/Character/BaseCharacter.h"

void FMyAnimInstanceProxy::InitializeObjects(UAnimInstance* InAnimInstance)
{
	Super::InitializeObjects(InAnimInstance);
    
	m_MyAnim = Cast<UMyAnimInstance>(InAnimInstance);
}

void FMyAnimInstanceProxy::Update(float DeltaSeconds)
{
	m_MyAnim->UpdateFlags();
}

void UMyAnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();

	m_Owner=Cast<ABaseCharacter>( TryGetPawnOwner());
}

void UMyAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	m_Owner=Cast<ABaseCharacter>( TryGetPawnOwner());
}

void UMyAnimInstance::UpdateFlags()
{
#if WITH_EDITOR
	if(!m_Owner)
	{
		return;
	}
#endif
	m_fSpeedPercent=m_Owner->GetSpeedPercentOne();
}
