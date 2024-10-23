#include "../../Player.h"

#include "SquatState.h"
#include "../Enum/PlayerState.h"

SquatState::SquatState(Player* p) :
	PlayerStateBase(p)
{
}

SquatState::~SquatState()
{
}

void SquatState::Initialize()
{
}

void SquatState::Update()
{
}

void SquatState::Draw() const
{
}

void SquatState::Finalize()
{
}

ePlayerLooksState SquatState::GetLooksState() const
{
	return ePlayerLooksState();
}

ePlayerState SquatState::GetState() const
{
	return ePlayerState();
}
