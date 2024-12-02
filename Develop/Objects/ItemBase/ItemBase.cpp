#include "ItemBase.h"

ItemBase::ItemBase()
{
}

ItemBase::~ItemBase()
{
}

void ItemBase::Initialize()
{
}

void ItemBase::Update(float delata_second)
{
}

void ItemBase::Draw(const Vector2D& screen_offset) const
{
	__super::Draw(screen_offset);
}

void ItemBase::Finalize()
{
}

void ItemBase::OnHitCollision(GameObjectBase* hit_object)
{
}
