#pragma once

#include "../CharacterBase.h"
#include <vector>

#include "State/Enum/PlayerState.h"

enum ePlayerLooksState
{
	NOMALMARIO,
	STARNOMALMARIO,
	DEKAMARIO,
	STARDEKAMARIO,
	FIREMARIO,
	DESTROYMARIO
};

class Player : public CharacterBase
{
private:
	std::vector<int> nomalmario_animation;
	std::vector<int> s_nomalmario_animation;
	std::vector<int> growth_animation;
	std::vector<int> dekamario_animation;
	std::vector<int> s_dekamario_animation;
	std::vector<int> firemario_animation;

public:
	int zanki;
	int coin_count;
	bool is_star;
	bool is_destroy;
	Vector2D box_size = (0.0f);

private:
	class PlayerStateBase* state = nullptr;
	ePlayerState next_state = ePlayerState::NONE;
	ePlayerLooksState old_state;

private:
	//ëΩï™StateÇ≈èëÇ≠
	int nomalmario_num[3];
	int s_nomalmario_num[2];
	int growthmario_num[2];
	int dekamario_num[2];
	int s_dekamario_num[2];
	int firemario_num[2];

public:
	Player();
	~Player();

public:
	void Initialize() override;
	void Update(float delata_second) override;
	void Draw(const Vector2D& screen_offset)const override;
	void Finalize() override;

public:
	int GetZanki();
	bool GetPowerUp()const;
	void SetPowerDown();
	bool GetDestroy()const;
	void AnimationControl(float delta_second);
	void SetNextState(ePlayerState next_state);
};

