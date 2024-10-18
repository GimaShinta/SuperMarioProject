#pragma once

#include "../CharacterBase.h"

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

private:
	ePlayerLooksState old_state;

private:
	int nomalmario_num[];
	int s_nomalmario_num[];
	int growthmario_num[];
	int dekamario_num[];
	int s_dekamario_num[];
	int firemario_num[];

public:
	int GetZanki();
	bool GetPowerUp()const;
	void SetPowerDown();
	bool GetDestroy()const;
	void AnimationControl(float delta_second);
};

