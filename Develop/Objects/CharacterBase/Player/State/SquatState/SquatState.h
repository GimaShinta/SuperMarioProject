#pragma once

#include "../PlayerStateBase.h"

//���Ⴊ�ݏ�ԃN���X
class SquatState : public PlayerStateBase
{
public:
	SquatState(class Player* p);
	~SquatState();

public:
	//����������
	void Initialize() override;
	//�X�V����
	void Update(float delta_second) override;
	//�`�揈��
	void Draw() const override;
	//�I��������
	void Finalize() override;

public:
	//���݂̌����ڂ̏�Ԃ��擾
	ePlayerLooksState GetLooksState() const override;
	//���݂̂̓����̏�Ԃ��擾
	ePlayerState GetState() const override;
};

