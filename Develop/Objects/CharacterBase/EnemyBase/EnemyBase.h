#pragma once

#include "../CharacterBase.h"

//�G�l�~�[���N���X
class EnemyBase :public CharacterBase
{
protected:
	enum eEnemyState
	{
		NONE,
		MOVE,
		DESTROTY
	};

protected:
	// �G�̉摜
	std::vector<int> emove_animation;
	// �G�̃A�j���[�V�����̏���
	std::vector<int> emove_nums = { 0,1 };

public:
	EnemyBase();
	~EnemyBase();

public:
	// ����������
	virtual void Initialize() override;
	// �X�V����
	virtual void Update(float delata_second) override;
	// �`�揈��
	virtual void Draw(const Vector2D& screen_offset)const override;
	// �I��������
	virtual void Finalize() override;

public:
	// �q�b�g������
	virtual void OnHitCollision(GameObjectBase* hit_object) override;

//public:
//	void Movement(float delta_second);

	// �X�N���[���̕���������������
	void SetScroll(float scroll);
};

