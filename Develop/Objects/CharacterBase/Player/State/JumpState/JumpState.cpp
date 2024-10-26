#include "JumpState.h"
#include "DxLib.h"

#include "../../Player.h"
#include "../Enum/PlayerState.h"

#include "../../../../../Utility/InputManager.h"

JumpState::JumpState(Player* p) :
	PlayerStateBase(p)
{
}

JumpState::~JumpState()
{
}

void JumpState::Initialize()
{
	//Boxサイズを設定
	player->box_size = Vector2D(32.0f);

	//移動処理
	this->player->velocity.y -= 15.0f;         //ジャンプ力
	old_location = 0.0f;
}

void JumpState::Update()
{
	//インスタンスの取得
	InputManager* input = Singleton<InputManager>::GetInstance();

	//移動状態に遷移
	if (input->GetKey(KEY_INPUT_LEFT) || input->GetKey(KEY_INPUT_RIGHT))
	{
		player->SetNextState(ePlayerState::RUN);
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

void JumpState::Draw() const
{
	//座標情報を整数値に変換
	int x = 0, y = 0;
	player->GetLocation().ToInt(&x, &y);

	//描画
	DrawBox(x - (int)(player->box_size.x), y - (int)(player->box_size.y),
		x + (int)(player->box_size.x), y + (int)(player->box_size.y), GetColor(255, 0, 0), FALSE);

	DrawString(200, 120, "プレイヤージャンプ中", GetColor(255, 255, 255), TRUE);
}

void JumpState::Finalize()
{
}

ePlayerLooksState JumpState::GetLooksState() const
{
	return ePlayerLooksState();
}

ePlayerState JumpState::GetState() const
{
	return ePlayerState::JUMP;
}
