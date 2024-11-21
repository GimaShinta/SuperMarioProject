#pragma once

#include "../PlayerStateBase.h"

//歩く状態クラス
class RunState : public PlayerStateBase
{
public:
	RunState(class Player* p);
	~RunState();

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
	//現在の動きの状態を取得
	ePlayerState GetState() const override;
};

