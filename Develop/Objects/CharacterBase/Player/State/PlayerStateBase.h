#pragma once

#include "../../../../Utility/Vector2D.h"

#include "../Player.h"
#include "Enum/PlayerState.h"

/// <summary>
/// プレイヤー状態管理用のベースクラス
/// </summary>
class PlayerStateBase
{
protected:
	// プレイヤー情報
	class Player* player;
	Vector2D old_location;
	int state_image;
	float animation_time;
	int animation_count;

public:
	PlayerStateBase(class Player* p) 
		: player(p)
		, state_image(NULL)
		, animation_time(0)
		, animation_count(0)
	{
	}

	virtual ~PlayerStateBase() = default;

public:
	// 初期化処理
	virtual void Initialize() = 0;
	// 終了時処理
	virtual void Finalize() = 0;
	// 更新処理
	virtual void Update(float delta_second) = 0;
	// 描画処理
	virtual void Draw() const = 0;

public:
	// 現在の見た目の状態を取得
	virtual ePlayerLooksState GetLooksState() const = 0;
	// 現在の動きの状態を取得
	virtual ePlayerState GetState() const = 0;
};