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

// 初期化処理
void RunState::Initialize()
{
}

// 更新処理
void RunState::Update(float delta_second)
{
	// インスタンスの取得
	InputManager* input = Singleton<InputManager>::GetInstance();

	// 移動処理と反転
	if (input->GetKey(KEY_INPUT_LEFT))
	{
		this->player->velocity.x -= 2.0f;
		this->player->flip_flag = TRUE;
		old_location = 0.0f;
	}
	else if (input->GetKey(KEY_INPUT_RIGHT))
	{
		this->player->velocity.x += 2.0f;
		this->player->flip_flag = FALSE;
		old_location = 0.0f;
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

	// 地面に触れたら
	if (old_location.y == player->GetLocation().y)
	{
		// 停止状態に遷移
		player->SetNextState(ePlayerState::IDLE);
	}

	if (player->is_destroy == true)
	{
		player->SetNextState(ePlayerState::DESTROY);
	}

	// 前回座標の更新
	old_location = player->GetLocation();
}

// 描画処理
void RunState::Draw() const
{
}

// 終了時処理
void RunState::Finalize()
{
}

// 現在の見た目の状態を取得
ePlayerLooksState RunState::GetLooksState() const
{
	return ePlayerLooksState();
}

// 現在の動きの状態を取得
ePlayerState RunState::GetState() const
{
	return ePlayerState::RUN;
}
