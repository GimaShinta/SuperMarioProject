#include "../../Player.h"

#include "RunState.h"
#include "../Enum/PlayerState.h"

RunState::RunState(Player* p) :
	PlayerStateBase(p)
{
}

RunState::~RunState()
{
}

void RunState::Initialize()
{
}

void RunState::Update()
{
}

void RunState::Draw() const
{
}

void RunState::Finalize()
{
}

ePlayerLooksState RunState::GetLooksState() const
{
	return ePlayerLooksState();
}

ePlayerState RunState::GetState() const
{
	return ePlayerState();
}
