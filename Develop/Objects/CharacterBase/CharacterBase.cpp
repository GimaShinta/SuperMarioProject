#include "CharacterBase.h"

CharacterBase::CharacterBase()
{
}

CharacterBase::~CharacterBase()
{
}

void CharacterBase::Initialize()
{
}

void CharacterBase::Update(float delata_second)
{
	__super::Update(delata_second);
}

void CharacterBase::Draw(const Vector2D& screen_offset) const
{
	__super::Draw(screen_offset);
}

void CharacterBase::Finalize()
{
}

void CharacterBase::OnHitCollision(GameObjectBase* hit_object)
{
}

void CharacterBase::Movement(float delta_second)
{
	location += velocity * delta_second;
}

void CharacterBase::SetVelocity(const Vector2D& velocity)
{
	this->velocity = velocity;
}
