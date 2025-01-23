#include "SquatState.h"
#include "DxLib.h"

#include "../../Player.h"
#include "../Enum/PlayerState.h"

#include "../../../../../Utility/InputManager.h"

SquatState::SquatState(Player* p) :
	PlayerStateBase(p)
{
}

SquatState::~SquatState()
{
}

// ����������
void SquatState::Initialize()
{
	// Box�T�C�Y��ݒ�
	player->box_size.y /= 2;

	// ���x��0�ɂ���
	player->velocity.x = 0.0f;
}

// �X�V����
void SquatState::Update(float delta_second)
{
	// �C���X�^���X�̎擾
	InputManager* input = Singleton<InputManager>::GetInstance();

	// �n�ʂɐG�ꂽ��
	if (input->GetKeyUp(KEY_INPUT_DOWN))
	{
		// ��~��ԂɑJ��
		player->SetNextState(ePlayerState::IDLE);
	}

	if (player->is_destroy == true)
	{
		player->SetNextState(ePlayerState::DESTROY);
	}

}

// �`�揈��
void SquatState::Draw() const
{
	// ���W���𐮐��l�ɕϊ�
	int x = 0, y = 0;
	player->GetLocation().ToInt(&x, &y);

	// �`��(���Ⴊ�ݕ����̒l�����炷)
	DrawBox(x - (int)(player->box_size.x), y - (int)(player->box_size.y - D_OBJECT_SIZE),
		x + (int)(player->box_size.x), y + (int)(player->box_size.y), GetColor(255, 0, 0), FALSE);

	DrawString(200, 120, "�v���C���[���Ⴊ�ݒ�", GetColor(255, 255, 255), TRUE);
}

// �I��������
void SquatState::Finalize()
{
}

// ���݂̌����ڂ̏�Ԃ��擾
ePlayerLooksState SquatState::GetLooksState() const
{
	return ePlayerLooksState();
}

// ���݂̓����̏�Ԃ��擾
ePlayerState SquatState::GetState() const
{
	return ePlayerState();
}
