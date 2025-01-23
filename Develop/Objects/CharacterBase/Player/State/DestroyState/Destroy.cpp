#include "Destroy.h"
#include "DxLib.h"

DestroyState::DestroyState(Player* p) : 
	PlayerStateBase(p)
{
}

DestroyState::~DestroyState()
{
}

// 初期化処理
void DestroyState::Initialize()
{
	// 上に飛ばすアニメーション
	player->velocity.y -= 250.0f;
}

// 更新処理
void DestroyState::Update(float delta_second)
{
	// 当たり判定ない状態を保存
	eObjectType type = eObjectType::eNone;
	// 今の状態から変化先の状態に移行
	switch (player->now_looks_state)
	{
	case ePlayerLooksState::NOMALMARIO:
		// プレイヤーの当たり判定を削除
		player->SetObjectType(type);
		break;
	case ePlayerLooksState::DEKAMARIO:
		// 大きいマリオから小さいマリオに状態変化
		player->now_looks_state = ePlayerLooksState::NOMALMARIO;
		break;
	case ePlayerLooksState::FIREMARIO:
		// ファイアマリオから大きいマリオに状態変化
		player->now_looks_state = ePlayerLooksState::DEKAMARIO;
		break;
	case ePlayerLooksState::STARNOMALMARIO:
		// スターの小さいマリオから普通の小さいマリオに状態変化
		player->now_looks_state = ePlayerLooksState::NOMALMARIO;
		break;
	case ePlayerLooksState::STARDEKAMARIO:
		// スターの大きいマリオから普通の大きいマリオに状態変化
		player->now_looks_state = ePlayerLooksState::DEKAMARIO;
		break;
	}
}

// 描画処理
void DestroyState::Draw() const
{
	//座標情報を整数値に変換
	int x = 0, y = 0;
	player->GetLocation().ToInt(&x, &y);

	//描画
	//DrawBox(x - (int)(player->box_size.x), y - (int)(player->box_size.y),
	//	x + (int)(player->box_size.x), y + (int)(player->box_size.y), GetColor(255, 0, 0), FALSE);

	DrawString(200, 120, "プレイヤーヒット", GetColor(255, 255, 255), TRUE);
}

// 終了時処理
void DestroyState::Finalize()
{
}

// 現在の見た目状態を取得
ePlayerLooksState DestroyState::GetLooksState() const
{
	return ePlayerLooksState();
}

// 現在の移動状態を取得
ePlayerState DestroyState::GetState() const
{
	return ePlayerState();
}
