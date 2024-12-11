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

// 初期化処理
void JumpState::Initialize()
{
	//移動処理
	this->player->velocity.y -= 400.0f;         //ジャンプ力
	old_location = 0.0f;
}

// 更新処理
void JumpState::Update(float delta_second)
{
	//インスタンスの取得
	InputManager* input = Singleton<InputManager>::GetInstance();

	// ジャンプ状態のまま移動
	if (input->GetKey(KEY_INPUT_LEFT))
	{
		this->player->velocity.x -= 1.0f;
	}
	else if (input->GetKey(KEY_INPUT_RIGHT))
	{
		this->player->velocity.x += 1.0f;
	}

	// しゃがみ状態に遷移
	if (input->GetKey(KEY_INPUT_DOWN))
	{
		player->SetNextState(ePlayerState::SQUAT);
	}

	// 地面に触れたら
	if (old_location.y == player->GetLocation().y)
	{
		// 停止状態に遷移
		player->SetNextState(ePlayerState::IDLE);
	}

	// 前回座標の更新
	old_location = player->GetLocation();
}

// 描画処理
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

// 終了時処理
void JumpState::Finalize()
{
}

// 現在の見た目状態の取得
ePlayerLooksState JumpState::GetLooksState() const
{
	return ePlayerLooksState();
}

// 現在の移動状態の取得
ePlayerState JumpState::GetState() const
{
	return ePlayerState::JUMP;
}
