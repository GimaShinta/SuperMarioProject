#include "RunState.h"
#include "DxLib.h"

#include "../../Player.h"
#include "../Enum/PlayerState.h"

#include "../../../../../Utility/InputManager.h"

RunState::RunState(Player* p) :
	PlayerStateBase(p)
{
}

RunState::~RunState()
{
}

void RunState::Initialize()
{
	//Boxサイズを設定
	player->box_size = Vector2D(32.0f);
}

void RunState::Update()
{
	InputManager* input = Singleton<InputManager>::GetInstance();

	if (input->GetKey(KEY_INPUT_LEFT))
	{
		this->player->velocity.x -= 0.5f;         //ジャンプ力
		old_location = 0.0f;
	}
	else if (input->GetKey(KEY_INPUT_RIGHT))
	{
		this->player->velocity.x += 0.5f;         //ジャンプ力
		old_location = 0.0f;
	}

	//ジャンプ状態に遷移
	if (input->GetKeyDown(KEY_INPUT_UP))
	{
		player->SetNextState(ePlayerState::JUMP);
	}

	//しゃがみ状態に遷移
	if (input->GetKey(KEY_INPUT_DOWN))
	{
		player->SetNextState(ePlayerState::SQUAT);
	}

	//地面に触れたら
	if (old_location.y == player->GetLocation().y)
	{
		//停止状態に遷移
		player->SetNextState(ePlayerState::IDLE);
	}

	//前回座標の更新
	old_location = player->GetLocation();
}

void RunState::Draw() const
{
	//座標情報を整数値に変換
	int x = 0, y = 0;
	player->GetLocation().ToInt(&x, &y);

	//描画
	DrawBox(x - (int)(player->box_size.x), y - (int)(player->box_size.y),
		x + (int)(player->box_size.x), y + (int)(player->box_size.y), GetColor(255, 0, 0), FALSE);

	DrawString(0, 150, "プレイヤー移動中", GetColor(255, 255, 255), TRUE);
}

void RunState::Finalize()
{
}

ePlayerLooksState RunState::GetLooksState() const
{
	return ePlayerLooksState();
}

ePlayerState RunState::GetState() const
{
	return ePlayerState::RUN;
}
