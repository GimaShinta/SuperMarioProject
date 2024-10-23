#pragma once

#include "../PlayerStateBase.h"

class RunState : public PlayerStateBase
{
public:
	RunState(class Player* p);
	~RunState();

public:
	void Initialize() override;
	void Update() override;
	void Draw() const override;
	void Finalize() override;

public:
	ePlayerLooksState GetLooksState() const override;
	ePlayerState GetState() const override;
};

