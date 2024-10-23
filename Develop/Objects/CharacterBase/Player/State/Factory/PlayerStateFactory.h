#pragma once

#include "../../../../../Singleton.h"

#include "../PlayerStateBase.h"
#include "../Enum/PlayerState.h"

class PlayerStateFactory : public Singleton<class T>
{
private:
	//�N���X�^�ϐ�
	class IdleState* idle;
	class RunState* run;
	class JumpState* jump;
	class SquatState* squat;

private:
	//����������
	void Initialize(class Player& player);

public:
	//��ԃN���X�Ǘ�����
	static PlayerStateBase* Get(class Player& player, ePlayerState state);
	
	//�I������
	void Finalize();
};

