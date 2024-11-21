#include "BlockBase.h"

BlockBase::BlockBase()
{
}

BlockBase::~BlockBase()
{
}

void BlockBase::Initialize()
{
}

void BlockBase::Update(float delata_second)
{
}

void BlockBase::Draw(const Vector2D& screen_offset) const
{
	__super::Draw(screen_offset);
}

void BlockBase::Finalize()
{
}

void BlockBase::OnHitCollision(GameObjectBase* hit_object)
{
}
