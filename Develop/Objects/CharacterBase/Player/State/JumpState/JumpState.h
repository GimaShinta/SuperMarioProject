#pragma once

#include "../PlayerStateBase.h"

// �v���C���[�̃W�����v��ԃN���X
class JumpState : public PlayerStateBase
{
private:
	// �W�����v����
	int jump_sound;

public:
	JumpState(class Player* p);
	~JumpState();

public:
	// ����������
	void Initialize() override;
	// �X�V����
	void Update(float delta_second) override;
	// �`�揈��
	void Draw() const override;
	// �I��������
	void Finalize() override;

public:
	// ���݂̌����ڏ�Ԃ��擾
	ePlayerLooksState GetLooksState() const override;
	// ���݂̈ړ���Ԃ��擾
	ePlayerState GetState() const override;
};