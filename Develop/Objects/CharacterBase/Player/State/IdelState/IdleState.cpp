#include "IdleState.h"
#include "DxLib.h"

#include "../../Player.h"
#include "../Enum/PlayerState.h"

#include "../../../../../Utility/InputManager.h"

IdleState::IdleState(Player* p) :
	PlayerStateBase(p)
{
}

IdleState::~IdleState()
{
}

void IdleState::Initialize()
{
	//Box�T�C�Y��ݒ�
	player->box_size = Vector2D(32.0f);

	//���x��0�ɂ���
	player->velocity = 0.0f;
}

void IdleState::Update()
{
	InputManager* input = Singleton<InputManager>::GetInstance();

	//�ړ���ԂɑJ��
	if (input->GetKey(KEY_INPUT_LEFT) || input->GetKey(KEY_INPUT_RIGHT))
	{
		player->SetNextState(ePlayerState::RUN);
	}

	//�W�����v��ԂɑJ��
	if (input->GetKeyDown(KEY_INPUT_UP))
	{
		player->SetNextState(ePlayerState::JUMP);
	}

	//���Ⴊ�ݏ�ԂɑJ��
	if (input->GetKey(KEY_INPUT_DOWN))
	{
		player->SetNextState(ePlayerState::SQUAT);
	}
}

void IdleState::Draw() const
{
	//���W���𐮐��l�ɕϊ�
	int x = 0, y = 0;
	player->GetLocation().ToInt(&x, &y);

	//�`��
	DrawBox(x - (int)(player->box_size.x), y - (int)(player->box_size.y), 
		x + (int)(player->box_size.x), y + (int)(player->box_size.y), GetColor(255, 0, 0), FALSE);

	DrawString(0, 150, "�v���C���[��~��", GetColor(255, 255, 255), TRUE);
}

void IdleState::Finalize()
{
}

ePlayerLooksState IdleState::GetLooksState() const
{
	return ePlayerLooksState();
}

ePlayerState IdleState::GetState() const
{
	return ePlayerState::IDLE;
}
