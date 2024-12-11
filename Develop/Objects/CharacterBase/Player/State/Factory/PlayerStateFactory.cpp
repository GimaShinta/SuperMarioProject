#include "PlayerStateFactory.h"

#include "../IdelState/IdleState.h"
#include "../JumpState/JumpState.h"
#include "../RunState/RunState.h"
#include "../SquatState/SquatState.h"

#include "../../Player.h"

PlayerStateFactory* factory = Singleton<PlayerStateFactory>::GetInstance();

void PlayerStateFactory::DeleteInstance()
{
	// ���N���X�̃|�C���^�i���̂��A�h���X�̐�ŕۗL�j
	static PlayerStateFactory* instance = nullptr;

	// �C���X�^���X�����݂��Ă���ꍇ�A�폜����
	if (instance != nullptr)
	{
		delete instance;
		instance = nullptr;
	}
}

void PlayerStateFactory::Initialize(Player& player)
{
	idle = new IdleState(&player);
	jump = new JumpState(&player);
	run = new RunState(&player);
	squat = new SquatState(&player);
}

PlayerStateBase* PlayerStateFactory::Get(Player& player, ePlayerState state)
{
	factory->Initialize(player);

	PlayerStateBase* ret = nullptr;

	switch (state)
	{
		//��~���
	case ePlayerState::IDLE:
		factory->idle->Initialize();
		ret = factory->idle;
		break;
		//�W�����v���
	case ePlayerState::JUMP:
		factory->jump->Initialize();
		ret = factory->jump;
		break;
		//�ړ����
	case ePlayerState::RUN:
		factory->run->Initialize();
		ret = factory->run;
		break;
	case ePlayerState::SQUAT:
		factory->squat->Initialize();
		ret = factory->squat;
		break;
	case ePlayerState::NONE:      //�Ԃ����̂Ȃ�
	default:
		break;
	}

	return ret;
}

void PlayerStateFactory::Finalize()
{
	//�e��ԃN���X�̏I������
	factory->idle->Finalize();
	factory->jump->Finalize();
	factory->run->Finalize();
	factory->squat->Finalize();

	//�e��ԃN���X�̃C���X�^���X���폜
	delete factory->idle;
	delete factory->jump;
	delete factory->run;
	delete factory->squat;
}
