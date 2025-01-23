#pragma once

#include "../PlayerStateBase.h"

// プレイヤーの停止状態クラス
class IdleState : public PlayerStateBase
{
public:
	IdleState(class Player* p);
	~IdleState();

public:
	// 初期化処理
	void Initialize() override;
	// 更新処理
	void Update(float delta_second) override;
	// 描画処理
	void Draw() const override;
	// 終了時処理
	void Finalize() override;

public:
	// 現在の見た目状態を取得
	ePlayerLooksState GetLooksState() const override;
	// 現在の移動状態を取得
	ePlayerState GetState() const override;
};