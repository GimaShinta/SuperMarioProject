#include "Destroy.h"
#include "DxLib.h"

DestroyState::DestroyState(Player* p) : 
	PlayerStateBase(p)
{
}

DestroyState::~DestroyState()
{
}

// ����������
void DestroyState::Initialize()
{
	// ��ɔ�΂��A�j���[�V����
	player->velocity.y -= 250.0f;
}

// �X�V����
void DestroyState::Update(float delta_second)
{
	// �����蔻��Ȃ���Ԃ�ۑ�
	eObjectType type = eObjectType::eNone;
	// ���̏�Ԃ���ω���̏�ԂɈڍs
	switch (player->now_looks_state)
	{
	case ePlayerLooksState::NOMALMARIO:
		// �v���C���[�̓����蔻����폜
		player->SetObjectType(type);
		break;
	case ePlayerLooksState::DEKAMARIO:
		// �傫���}���I���珬�����}���I�ɏ�ԕω�
		player->now_looks_state = ePlayerLooksState::NOMALMARIO;
		break;
	case ePlayerLooksState::FIREMARIO:
		// �t�@�C�A�}���I����傫���}���I�ɏ�ԕω�
		player->now_looks_state = ePlayerLooksState::DEKAMARIO;
		break;
	case ePlayerLooksState::STARNOMALMARIO:
		// �X�^�[�̏������}���I���畁�ʂ̏������}���I�ɏ�ԕω�
		player->now_looks_state = ePlayerLooksState::NOMALMARIO;
		break;
	case ePlayerLooksState::STARDEKAMARIO:
		// �X�^�[�̑傫���}���I���畁�ʂ̑傫���}���I�ɏ�ԕω�
		player->now_looks_state = ePlayerLooksState::DEKAMARIO;
		break;
	}
}

// �`�揈��
void DestroyState::Draw() const
{
	//���W���𐮐��l�ɕϊ�
	int x = 0, y = 0;
	player->GetLocation().ToInt(&x, &y);

	//�`��
	//DrawBox(x - (int)(player->box_size.x), y - (int)(player->box_size.y),
	//	x + (int)(player->box_size.x), y + (int)(player->box_size.y), GetColor(255, 0, 0), FALSE);

	DrawString(200, 120, "�v���C���[�q�b�g", GetColor(255, 255, 255), TRUE);
}

// �I��������
void DestroyState::Finalize()
{
}

// ���݂̌����ڏ�Ԃ��擾
ePlayerLooksState DestroyState::GetLooksState() const
{
	return ePlayerLooksState();
}

// ���݂̈ړ���Ԃ��擾
ePlayerState DestroyState::GetState() const
{
	return ePlayerState();
}
