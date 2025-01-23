#include "EnemyBase.h"

EnemyBase::EnemyBase()
{
}

EnemyBase::~EnemyBase()
{
}

// ����������
void EnemyBase::Initialize()
{
}

// �X�V����
void EnemyBase::Update(float delata_second)
{
	__super::Update(delata_second);
}

// �`�揈��
void EnemyBase::Draw(const Vector2D& screen_offset) const
{
	__super::Draw(screen_offset);
}

// �I��������
void EnemyBase::Finalize()
{
}

// �q�b�g������
void EnemyBase::OnHitCollision(GameObjectBase* hit_object)
{
}

// �X�N���[���̕���������������
void EnemyBase::SetScroll(float scroll)
{
	this->location.x = scroll;
}