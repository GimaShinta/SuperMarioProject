#include "JumpState.h"
#include "DxLib.h"

#include "../../Player.h"
#include "../Enum/PlayerState.h"

#include "../../../../../Utility/InputManager.h"

JumpState::JumpState(Player* p) :
	PlayerStateBase(p)
{
}

JumpState::~JumpState()
{
}

void JumpState::Initialize()
{
	//Box�T�C�Y��ݒ�
	player->box_size = Vector2D(32.0f);

	//�ړ�����
	this->player->velocity.y -= 15.0f;         //�W�����v��
	old_location = 0.0f;
}

void JumpState::Update()
{
	//�C���X�^���X�̎擾
	InputManager* input = Singleton<InputManager>::GetInstance();

	//�ړ���ԂɑJ��
	if (input->GetKey(KEY_INPUT_LEFT) || input->GetKey(KEY_INPUT_RIGHT))
	{
		player->SetNextState(ePlayerState::RUN);
	}

	//���Ⴊ�ݏ�ԂɑJ��
	if (input->GetKey(KEY_INPUT_DOWN))
	{
		player->SetNextState(ePlayerState::SQUAT);
	}

	//�n�ʂɐG�ꂽ��
	if (old_location.y == player->GetLocation().y)
	{
		//��~��ԂɑJ��
		player->SetNextState(ePlayerState::IDLE);
	}

	//�O����W�̍X�V
	old_location = player->GetLocation();
}

void JumpState::Draw() const
{
	//���W���𐮐��l�ɕϊ�
	int x = 0, y = 0;
	player->GetLocation().ToInt(&x, &y);

	//�`��
	DrawBox(x - (int)(player->box_size.x), y - (int)(player->box_size.y),
		x + (int)(player->box_size.x), y + (int)(player->box_size.y), GetColor(255, 0, 0), FALSE);

	DrawString(200, 120, "�v���C���[�W�����v��", GetColor(255, 255, 255), TRUE);
}

void JumpState::Finalize()
{
}

ePlayerLooksState JumpState::GetLooksState() const
{
	return ePlayerLooksState();
}

ePlayerState JumpState::GetState() const
{
	return ePlayerState::JUMP;
}
