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

void RunState::Initialize()
{
	//Box�T�C�Y��ݒ�
	player->box_size = Vector2D(32.0f);
}

void RunState::Update()
{
	InputManager* input = Singleton<InputManager>::GetInstance();

	if (input->GetKey(KEY_INPUT_LEFT))
	{
		this->player->velocity.x -= 0.5f;         //�W�����v��
		old_location = 0.0f;
	}
	else if (input->GetKey(KEY_INPUT_RIGHT))
	{
		this->player->velocity.x += 0.5f;         //�W�����v��
		old_location = 0.0f;
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

	//�n�ʂɐG�ꂽ��
	if (old_location.y == player->GetLocation().y)
	{
		//��~��ԂɑJ��
		player->SetNextState(ePlayerState::IDLE);
	}

	//�O����W�̍X�V
	old_location = player->GetLocation();
}

void RunState::Draw() const
{
	//���W���𐮐��l�ɕϊ�
	int x = 0, y = 0;
	player->GetLocation().ToInt(&x, &y);

	//�`��
	DrawBox(x - (int)(player->box_size.x), y - (int)(player->box_size.y),
		x + (int)(player->box_size.x), y + (int)(player->box_size.y), GetColor(255, 0, 0), FALSE);

	DrawString(0, 150, "�v���C���[�ړ���", GetColor(255, 255, 255), TRUE);
}

void RunState::Finalize()
{
}

ePlayerLooksState RunState::GetLooksState() const
{
	return ePlayerLooksState();
}

ePlayerState RunState::GetState() const
{
	return ePlayerState::RUN;
}
