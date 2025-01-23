#include "PlayerStateFactory.h"

#include "../IdelState/IdleState.h"
#include "../JumpState/JumpState.h"
#include "../RunState/RunState.h"
#include "../SquatState/SquatState.h"
#include "../DestroyState/Destroy.h"

#include "../../Player.h"

PlayerStateFactory* factory = Singleton<PlayerStateFactory>::GetInstance();

// インスタンスの削除
void PlayerStateFactory::DeleteInstance()
{
	// 自クラスのポインタ（実体をアドレスの先で保有）
	static PlayerStateFactory* instance = nullptr;

	// インスタンスが存在している場合、削除する
	if (instance != nullptr)
	{
		delete instance;
		instance = nullptr;
	}
}

// 初期化処理
void PlayerStateFactory::Initialize(Player& player)
{
	idle = new IdleState(&player);
	jump = new JumpState(&player);
	run = new RunState(&player);
	squat = new SquatState(&player);
	destroy = new DestroyState(&player);
}

PlayerStateBase* PlayerStateFactory::Get(Player& player, ePlayerState state)
{
	factory->Initialize(player);

	PlayerStateBase* ret = nullptr;

	switch (state)
	{
		//停止状態
	case ePlayerState::IDLE:
		factory->idle->Initialize();
		ret = factory->idle;
		break;
		//ジャンプ状態
	case ePlayerState::JUMP:
		factory->jump->Initialize();
		ret = factory->jump;
		break;
		//移動状態
	case ePlayerState::RUN:
		factory->run->Initialize();
		ret = factory->run;
		break;
	case ePlayerState::SQUAT:
		factory->squat->Initialize();
		ret = factory->squat;
		break;
	case ePlayerState::DESTROY:
		factory->squat->Initialize();
		ret = factory->destroy;
		break;
	case ePlayerState::NONE:      //返すものなし
	default:
		break;
	}

	return ret;
}

// 終了時処理
void PlayerStateFactory::Finalize()
{
	//各状態クラスの終了処理
	factory->idle->Finalize();
	factory->jump->Finalize();
	factory->run->Finalize();
	factory->squat->Finalize();
	factory->destroy->Finalize();

	//各状態クラスのインスタンスを削除
	delete factory->idle;
	delete factory->jump;
	delete factory->run;
	delete factory->squat;
	delete factory->destroy;
}
