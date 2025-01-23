#include "IdleState.h"
#include "DxLib.h"

#include "../../Player.h"
#include "../Enum/PlayerState.h"

#include "../../../../../Utility/InputManager.h"
#include "../../../../../Utility/ResourceManager.h"

IdleState::IdleState(Player* p) :
	PlayerStateBase(p)
{
}

IdleState::~IdleState()
{
}

// ����������
void IdleState::Initialize()
{
	//���x��0�ɂ���
	player->velocity = 0.0f;

	//�摜�̐ݒ�
	ResourceManager* rm = Singleton<ResourceManager>::GetInstance();
	state_image = rm->GetImages("Resource/Images/Enemy/kuribo.png", 3, 3, 1, 32, 32)[0];
}

// �X�V����
void IdleState::Update(float delta_second)
{
	// �C���X�^���X�̎擾
	InputManager* input = Singleton<InputManager>::GetInstance();

	// �ړ���ԂɑJ��
	if (input->GetKey(KEY_INPUT_LEFT) || input->GetKey(KEY_INPUT_RIGHT))
	{
		player->SetNextState(ePlayerState::RUN);
	}

	// �W�����v��ԂɑJ��
	if (input->GetKeyDown(KEY_INPUT_UP))
	{
		player->SetNextState(ePlayerState::JUMP);
	}

	// ���Ⴊ�ݏ�ԂɑJ��
	if (input->GetKey(KEY_INPUT_DOWN))
	{
		player->SetNextState(ePlayerState::SQUAT);
	}

	if (player->is_destroy == true)
	{
		player->SetNextState(ePlayerState::DESTROY);
	}
}

// �`�揈��
void IdleState::Draw() const
{
	//���W���𐮐��l�ɕϊ�
	int x = 0, y = 0;
	player->GetLocation().ToInt(&x, &y);

	//�`��
	//DrawBox(x - (int)(player->box_size.x), y - (int)(player->box_size.y), 
	//	x + (int)(player->box_size.x), y + (int)(player->box_size.y), GetColor(255, 0, 0), FALSE);

	DrawString(200, 120, "�v���C���[��~��", GetColor(255, 255, 255), TRUE);
}

// �I��������
void IdleState::Finalize()
{
}

// ���݂̌����ڏ�Ԃ̎擾
ePlayerLooksState IdleState::GetLooksState() const
{
	return ePlayerLooksState();
}

// ���݂̈ړ���Ԃ̎擾
ePlayerState IdleState::GetState() const
{
	return ePlayerState::IDLE;
}
