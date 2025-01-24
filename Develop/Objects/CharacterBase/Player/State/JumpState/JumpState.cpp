#include "JumpState.h"
#include "DxLib.h"

#include "../../Player.h"
#include "../Enum/PlayerState.h"

#include "../../../../../Utility/InputManager.h"
#include "../../../../../Utility/ResourceManager.h"

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
	this->player->velocity.y -= 800.0f;         //�W�����v��
	old_location = 0.0f;

	// �C���X�^���X�̎擾
	ResourceManager* rm = Singleton<ResourceManager>::GetInstance();
	// �W�����v���̓ǂݍ���
	jump_sound = rm->GetSounds("Resource/Sounds/SE_MiniJump.wav");

	// �W�����v���Đ�
	PlaySoundMem(jump_sound, DX_PLAYTYPE_BACK);
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

	if (player->is_destroy == true)
	{
		player->SetNextState(ePlayerState::DESTROY);
	}

	// �O����W�̍X�V
	old_location = player->GetLocation();
}

// �`�揈��
void JumpState::Draw() const
{
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
