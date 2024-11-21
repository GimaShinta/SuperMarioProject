#pragma once

#include "../PlayerStateBase.h"

//しゃがみ状態クラス
class SquatState : public PlayerStateBase
{
public:
	SquatState(class Player* p);
	~SquatState();

public:
	//初期化処理
	void Initialize() override;
	//更新処理
	void Update(float delta_second) override;
	//描画処理
	void Draw() const override;
	//終了時処理
	void Finalize() override;

public:
	//現在の見た目の状態を取得
	ePlayerLooksState GetLooksState() const override;
	//現在のの動きの状態を取得
	ePlayerState GetState() const override;
};

