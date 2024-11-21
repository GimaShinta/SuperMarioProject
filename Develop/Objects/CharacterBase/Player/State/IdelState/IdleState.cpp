#include "IdleState.h"
#include "DxLib.h"

#include "../../Player.h"
#include "../Enum/PlayerState.h"

#include "../../../../../Utility/InputManager.h"

IdleState::IdleState(Player* p) :
	PlayerStateBase(p)
{
}

IdleState::~IdleState()
{
}

void IdleState::Initialize()
{
	//ë¨ìxÇ0Ç…Ç∑ÇÈ
	player->velocity = 0.0f;
}

void IdleState::Update(float delta_second)
{
	InputManager* input = Singleton<InputManager>::GetInstance();

	//à⁄ìÆèÛë‘Ç…ëJà⁄
	if (input->GetKey(KEY_INPUT_LEFT) || input->GetKey(KEY_INPUT_RIGHT))
	{
		player->SetNextState(ePlayerState::RUN);
	}

	//ÉWÉÉÉìÉvèÛë‘Ç…ëJà⁄
	if (input->GetKeyDown(KEY_INPUT_UP))
	{
		player->SetNextState(ePlayerState::JUMP);
	}

	//ÇµÇ·Ç™Ç›èÛë‘Ç…ëJà⁄
	if (input->GetKey(KEY_INPUT_DOWN))
	{
		player->SetNextState(ePlayerState::SQUAT);
	}
}

void IdleState::Draw() const
{
	//ç¿ïWèÓïÒÇêÆêîílÇ…ïœä∑
	int x = 0, y = 0;
	player->GetLocation().ToInt(&x, &y);

	//ï`âÊ
	DrawBox(x - (int)(player->box_size.x), y - (int)(player->box_size.y), 
		x + (int)(player->box_size.x), y + (int)(player->box_size.y), GetColor(255, 0, 0), FALSE);

	DrawString(200, 120, "ÉvÉåÉCÉÑÅ[í‚é~íÜ", GetColor(255, 255, 255), TRUE);
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
