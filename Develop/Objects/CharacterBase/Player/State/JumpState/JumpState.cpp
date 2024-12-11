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

// ����������
void JumpState::Initialize()
{
	//�ړ�����
	this->player->velocity.y -= 400.0f;         //�W�����v��
	old_location = 0.0f;
}

// �X�V����
void JumpState::Update(float delta_second)
{
	//�C���X�^���X�̎擾
	InputManager* input = Singleton<InputManager>::GetInstance();

	// �W�����v��Ԃ̂܂܈ړ�
	if (input->GetKey(KEY_INPUT_LEFT))
	{
		this->player->velocity.x -= 1.0f;
	}
	else if (input->GetKey(KEY_INPUT_RIGHT))
	{
		this->player->velocity.x += 1.0f;
	}

	// ���Ⴊ�ݏ�ԂɑJ��
	if (input->GetKey(KEY_INPUT_DOWN))
	{
		player->SetNextState(ePlayerState::SQUAT);
	}

	// �n�ʂɐG�ꂽ��
	if (old_location.y == player->GetLocation().y)
	{
		// ��~��ԂɑJ��
		player->SetNextState(ePlayerState::IDLE);
	}

	// �O����W�̍X�V
	old_location = player->GetLocation();
}

// �`�揈��
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

// �I��������
void JumpState::Finalize()
{
}

// ���݂̌����ڏ�Ԃ̎擾
ePlayerLooksState JumpState::GetLooksState() const
{
	return ePlayerLooksState();
}

// ���݂̈ړ���Ԃ̎擾
ePlayerState JumpState::GetState() const
{
	return ePlayerState::JUMP;
}
