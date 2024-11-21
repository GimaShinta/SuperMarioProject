#pragma once

#include "../PlayerStateBase.h"

class JumpState : public PlayerStateBase
{
public:
	JumpState(class Player* p);
	~JumpState();

public:
	void Initialize() override;
	void Update(float delta_second) override;
	void Draw() const override;
	void Finalize() override;

public:
	ePlayerLooksState GetLooksState() const override;
	ePlayerState GetState() const override;
};