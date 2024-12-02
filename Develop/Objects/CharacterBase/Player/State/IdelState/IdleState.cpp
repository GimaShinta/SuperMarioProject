#include "IdleState.h"
#include "DxLib.h"

#include "../../Player.h"
#include "../Enum/PlayerState.h"

#include "../../../../../Utility/InputManager.h"
#include "../../../../../Utility/ResourceManager.h"

IdleState::IdleState(Player* p) :
	PlayerStateBase(p)
{
}

IdleState::~IdleState()
{
}

void IdleState::Initialize()
{
	//‘¬“x‚ğ0‚É‚·‚é
	player->velocity = 0.0f;

	//‰æ‘œ‚Ìİ’è
	ResourceManager* rm = Singleton<ResourceManager>::GetInstance();
	state_image = rm->GetImages("Resource/Images/Enemy/kuribo.png", 3, 3, 1, 32, 32)[0];
}

void IdleState::Update(float delta_second)
{
	InputManager* input = Singleton<InputManager>::GetInstance();

	//ˆÚ“®ó‘Ô‚É‘JˆÚ
	if (input->GetKey(KEY_INPUT_LEFT) || input->GetKey(KEY_INPUT_RIGHT))
	{
		player->SetNextState(ePlayerState::RUN);
	}

	//ƒWƒƒƒ“ƒvó‘Ô‚É‘JˆÚ
	if (input->GetKeyDown(KEY_INPUT_UP))
	{
		player->SetNextState(ePlayerState::JUMP);
	}

	//‚µ‚á‚ª‚İó‘Ô‚É‘JˆÚ
	if (input->GetKey(KEY_INPUT_DOWN))
	{
		player->SetNextState(ePlayerState::SQUAT);
	}
}

void IdleState::Draw() const
{
	//À•Wî•ñ‚ğ®”’l‚É•ÏŠ·
	int x = 0, y = 0;
	player->GetLocation().ToInt(&x, &y);

	//•`‰æ
	DrawBox(x - (int)(player->box_size.x), y - (int)(player->box_size.y), 
		x + (int)(player->box_size.x), y + (int)(player->box_size.y), GetColor(255, 0, 0), FALSE);

	DrawString(200, 120, "ƒvƒŒƒCƒ„[’â~’†", GetColor(255, 255, 255), TRUE);

	DrawRotaGraphF(player->GetLocation().x, player->GetLocation().y, 1.5, 0.0, state_image, TRUE);

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
	return ePlayerState::IDLE;
}
