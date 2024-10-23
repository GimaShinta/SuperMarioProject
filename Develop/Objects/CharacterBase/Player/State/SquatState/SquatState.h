#pragma once

#include "../PlayerStateBase.h"

class SquatState : public PlayerStateBase
{
public:
	SquatState(class Player* p);
	~SquatState();

public:
	void Initialize() override;
	void Update() override;
	void Draw() const override;
	void Finalize() override;

public:
	ePlayerLooksState GetLooksState() const override;
	ePlayerState GetState() const override;
};

