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

void SquatState::Initialize()
{
	//Box�T�C�Y��ݒ�
	player->box_size = Vector2D(32.0f);

	//���x��0�ɂ���
	player->velocity = 0.0f;
}

void SquatState::Update()
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

	//�n�ʂɐG�ꂽ��
	if (input->GetKeyUp(KEY_INPUT_DOWN))
	{
		//��~��ԂɑJ��
		player->SetNextState(ePlayerState::IDLE);
	}
}

void SquatState::Draw() const
{
	//���W���𐮐��l�ɕϊ�
	int x = 0, y = 0;
	player->GetLocation().ToInt(&x, &y);

	//�`��(���Ⴊ�ݕ����̒l�����炷)
	DrawBox(x - (int)(player->box_size.x), y - (int)(player->box_size.y - 24.0f),
		x + (int)(player->box_size.x), y + (int)(player->box_size.y), GetColor(255, 0, 0), FALSE);

	DrawString(0, 150, "�v���C���[���Ⴊ�ݒ�", GetColor(255, 255, 255), TRUE);
}

void SquatState::Finalize()
{
}

ePlayerLooksState SquatState::GetLooksState() const
{
	return ePlayerLooksState();
}

ePlayerState SquatState::GetState() const
{
	return ePlayerState();
}
