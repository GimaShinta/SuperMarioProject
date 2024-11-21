#pragma once

#include "../PlayerStateBase.h"

class IdleState : public PlayerStateBase
{
public:
	IdleState(class Player* p);
	~IdleState();

public:
	void Initialize() override;
	void Update(float delta_second) override;
	void Draw() const override;
	void Finalize() override;

public:
	ePlayerLooksState GetLooksState() const override;
	ePlayerState GetState() const override;
};