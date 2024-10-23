#pragma once

#include "../../../../../Singleton.h"

#include "../PlayerStateBase.h"
#include "../Enum/PlayerState.h"

class PlayerStateFactory : public Singleton<class T>
{
private:
	//クラス型変数
	class IdleState* idle;
	class RunState* run;
	class JumpState* jump;
	class SquatState* squat;

private:
	//初期化処理
	void Initialize(class Player& player);

public:
	//状態クラス管理処理
	static PlayerStateBase* Get(class Player& player, ePlayerState state);
	
	//終了処理
	void Finalize();
};

