#include "JumpState.h"
#include "DxLib.h"

#include "../../Player.h"
#include "../Enum/PlayerState.h"

#include "../../../../../Utility/InputManager.h"
#include "../../../../../Utility/ResourceManager.h"

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
	this->player->velocity.y -= 800.0f;         //ジャンプ力
	old_location = 0.0f;

	// インスタンスの取得
	ResourceManager* rm = Singleton<ResourceManager>::GetInstance();
	// ジャンプ音の読み込み
	jump_sound = rm->GetSounds("Resource/Sounds/SE_MiniJump.wav");

	// ジャンプ音再生
	PlaySoundMem(jump_sound, DX_PLAYTYPE_BACK);
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

	if (player->is_destroy == true)
	{
		player->SetNextState(ePlayerState::DESTROY);
	}

	// 前回座標の更新
	old_location = player->GetLocation();
}

// 描画処理
void JumpState::Draw() const
{
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
