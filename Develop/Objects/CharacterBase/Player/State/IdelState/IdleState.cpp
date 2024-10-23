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
	//Boxサイズを設定
	player->box_size = Vector2D(32.0f);

	//速度を0にする
	player->velocity = 0.0f;
}

void IdleState::Update()
{
	InputManager* input = Singleton<InputManager>::GetInstance();

	//移動状態に遷移
	if (input->GetKey(KEY_INPUT_LEFT) || input->GetKey(KEY_INPUT_RIGHT))
	{
		player->SetNextState(ePlayerState::RUN);
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
}

void IdleState::Draw() const
{
	//座標情報を整数値に変換
	int x = 0, y = 0;
	player->GetLocation().ToInt(&x, &y);

	//描画
	DrawBox(x - (int)(player->box_size.x), y - (int)(player->box_size.y), 
		x + (int)(player->box_size.x), y + (int)(player->box_size.y), GetColor(255, 0, 0), FALSE);

	DrawString(0, 150, "プレイヤー停止中", GetColor(255, 255, 255), TRUE);
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
