#include "../../Player.h"

#include "IdleState.h"
#include "../Enum/PlayerState.h"

IdleState::IdleState(Player* p) :
	PlayerStateBase(p)
{
}

IdleState::~IdleState()
{
}

void IdleState::Initialize()
{
}

void IdleState::Update()
{
}

void IdleState::Draw() const
{
}

void IdleState::Finalize()
{
}

ePlayerLooksState IdleState::GetLooksState() const
{
	return ePlayerLooksState();
}

ePlayerState IdleState::GetState() const
{
	return ePlayerState();
}
