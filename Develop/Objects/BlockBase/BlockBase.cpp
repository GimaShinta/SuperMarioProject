#include "BlockBase.h"

BlockBase::BlockBase() :
	  velocity(0.0f)
	, is_scroll(false)
{
}

BlockBase::~BlockBase()
{
}

// ����������
void BlockBase::Initialize()
{
}

// �X�V����
void BlockBase::Update(float delata_second)
{
}

// �`�揈��
void BlockBase::Draw(const Vector2D& screen_offset) const
{
	__super::Draw(screen_offset);
}

// �I��������
void BlockBase::Finalize()
{
}

// �q�b�g������
void BlockBase::OnHitCollision(GameObjectBase* hit_object)
{
}

void BlockBase::SetScroll(float scroll)
{
	this->location.x = scroll;
}