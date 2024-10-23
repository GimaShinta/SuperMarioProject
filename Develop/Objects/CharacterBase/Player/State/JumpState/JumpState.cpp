#include "../../Player.h"

#include "JumpState.h"
#include "../Enum/PlayerState.h"

JumpState::JumpState(Player* p) :
	PlayerStateBase(p)
{
}

JumpState::~JumpState()
{
}

void JumpState::Initialize()
{
}

void JumpState::Update()
{
}

void JumpState::Draw() const
{
}

void JumpState::Finalize()
{
}

ePlayerLooksState JumpState::GetLooksState() const
{
	return ePlayerLooksState();
}

ePlayerState JumpState::GetState() const
{
	return ePlayerState();
}
