#pragma once

#include "../../../../../Singleton.h"

#include "../PlayerStateBase.h"
#include "../Enum/PlayerState.h"

// プレイヤーの移動状態管理クラス
class PlayerStateFactory : public Singleton<class T>
{
private:
	// クラス型変数
	class IdleState* idle;
	class RunState* run;
	class JumpState* jump;
	class SquatState* squat;
	class DestroyState* destroy;

public:
	// インスタンスの削除
	static void DeleteInstance();

private:
	// 初期化処理
	void Initialize(class Player& player);

public:
	// 状態クラス管理処理
	static PlayerStateBase* Get(class Player& player, ePlayerState state);
	
	// 終了処理
	void Finalize();
};

