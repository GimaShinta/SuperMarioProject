#include "SquatState.h"
#include "DxLib.h"

#include "../../Player.h"
#include "../Enum/PlayerState.h"

#include "../../../../../Utility/InputManager.h"

SquatState::SquatState(Player* p) :
	PlayerStateBase(p)
{
}

SquatState::~SquatState()
{
}

//初期化処理
void SquatState::Initialize()
{
	//Boxサイズを設定
	player->box_size = Vector2D(32.0f);

	//速度を0にする
	player->velocity = 0.0f;
}

//更新処理
void SquatState::Update()
{
	//インスタンスの取得
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

	//地面に触れたら
	if (input->GetKeyUp(KEY_INPUT_DOWN))
	{
		//停止状態に遷移
		player->SetNextState(ePlayerState::IDLE);
	}
}

//描画処理
void SquatState::Draw() const
{
	//座標情報を整数値に変換
	int x = 0, y = 0;
	player->GetLocation().ToInt(&x, &y);

	//描画(しゃがみ分ｙの値を減らす)
	DrawBox(x - (int)(player->box_size.x), y - (int)(player->box_size.y - 24.0f),
		x + (int)(player->box_size.x), y + (int)(player->box_size.y), GetColor(255, 0, 0), FALSE);

	DrawString(200, 120, "プレイヤーしゃがみ中", GetColor(255, 255, 255), TRUE);
}

//終了時処理
void SquatState::Finalize()
{
}

//現在の見た目の状態を取得
ePlayerLooksState SquatState::GetLooksState() const
{
	return ePlayerLooksState();
}

//現在の動きの状態を取得
ePlayerState SquatState::GetState() const
{
	return ePlayerState();
}
