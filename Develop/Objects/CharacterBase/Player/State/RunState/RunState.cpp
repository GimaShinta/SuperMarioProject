#include "RunState.h"
#include "DxLib.h"

#include "../../Player.h"
#include "../Enum/PlayerState.h"

#include "../../../../../Utility/InputManager.h"

RunState::RunState(Player* p) :
	PlayerStateBase(p)
{
}

RunState::~RunState()
{
}

// ����������
void RunState::Initialize()
{
}

// �X�V����
void RunState::Update(float delta_second)
{
	// �C���X�^���X�̎擾
	InputManager* input = Singleton<InputManager>::GetInstance();

	// �ړ������Ɣ��]
	if (input->GetKey(KEY_INPUT_LEFT))
	{
		this->player->velocity.x -= 2.0f;
		this->player->flip_flag = TRUE;
		old_location = 0.0f;
	}
	else if (input->GetKey(KEY_INPUT_RIGHT))
	{
		this->player->velocity.x += 2.0f;
		this->player->flip_flag = FALSE;
		old_location = 0.0f;
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
void RunState::Draw() const
{
}

// �I��������
void RunState::Finalize()
{
}

// ���݂̌����ڂ̏�Ԃ��擾
ePlayerLooksState RunState::GetLooksState() const
{
	return ePlayerLooksState();
}

// ���݂̓����̏�Ԃ��擾
ePlayerState RunState::GetState() const
{
	return ePlayerState::RUN;
}
