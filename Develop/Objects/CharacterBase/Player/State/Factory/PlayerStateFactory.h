#pragma once

#include "../../../../../Singleton.h"

#include "../PlayerStateBase.h"
#include "../Enum/PlayerState.h"

class PlayerStateFactory : public Singleton
{
private:
	class IdleState* idle;
	class RunState* run;
	class JumpState* jump;
	class SquatState* squat;

private:
	void Initialize(class Player&);

public:
	PlayerStateBase Get(class Player& player, ePlayerState state);
	void Finalize();
};

