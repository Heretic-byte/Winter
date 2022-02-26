
#include "AI_FleeJumper.h"

#include "Winter2/Actor/Pawn/Character/Animal.h"


void UAI_FleeJumper::OnFlee()
{
	Super::OnFlee();

	Jump();
}

void UAI_FleeJumper::Jump()
{
	if (m_fJumpTimer > 0.f)
	{
		m_fJumpTimer -= m_fDeltaTime;

		return;
	}

	m_Owner->Jump();

	m_fJumpTimer = FMath::FRandRange(3.f, 7.f);
}

