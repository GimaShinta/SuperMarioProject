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

// 初期化処理
void IdleState::Initialize()
{
	//速度を0にする
	player->velocity = 0.0f;

	//画像の設定
	ResourceManager* rm = Singleton<ResourceManager>::GetInstance();
	state_image = rm->GetImages("Resource/Images/Enemy/kuribo.png", 3, 3, 1, 32, 32)[0];
}

// 更新処理
void IdleState::Update(float delta_second)
{
	// インスタンスの取得
	InputManager* input = Singleton<InputManager>::GetInstance();

	// 移動状態に遷移
	if (input->GetKey(KEY_INPUT_LEFT) || input->GetKey(KEY_INPUT_RIGHT))
	{
		player->SetNextState(ePlayerState::RUN);
	}

	// ジャンプ状態に遷移
	if (input->GetKeyDown(KEY_INPUT_UP))
	{
		player->SetNextState(ePlayerState::JUMP);
	}

	// しゃがみ状態に遷移
	if (input->GetKey(KEY_INPUT_DOWN))
	{
		player->SetNextState(ePlayerState::SQUAT);
	}

	if (player->is_destroy == true)
	{
		player->SetNextState(ePlayerState::DESTROY);
	}
}

// 描画処理
void IdleState::Draw() const
{
	//座標情報を整数値に変換
	int x = 0, y = 0;
	player->GetLocation().ToInt(&x, &y);

	//描画
	//DrawBox(x - (int)(player->box_size.x), y - (int)(player->box_size.y), 
	//	x + (int)(player->box_size.x), y + (int)(player->box_size.y), GetColor(255, 0, 0), FALSE);

	DrawString(200, 120, "プレイヤー停止中", GetColor(255, 255, 255), TRUE);
}

// 終了時処理
void IdleState::Finalize()
{
}

// 現在の見た目状態の取得
ePlayerLooksState IdleState::GetLooksState() const
{
	return ePlayerLooksState();
}

// 現在の移動状態の取得
ePlayerState IdleState::GetState() const
{
	return ePlayerState::IDLE;
}
