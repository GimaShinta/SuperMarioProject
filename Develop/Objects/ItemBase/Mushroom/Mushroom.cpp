#include "Mushroom.h"

#include "../../../Utility/ResourceManager.h"

Mushroom::Mushroom():
	velocity(0)
{
}

Mushroom::~Mushroom()
{
}

void Mushroom::Initialize()
{
	box_size = Vector2D(D_OBJECT_SIZE);
	is_mobility = true;
	velocity.x = 1;

	//‰æ‘œ‚Ìİ’è
	ResourceManager* rm = Singleton<ResourceManager>::GetInstance();
	image = rm->GetImages("Resource/Images/Item/Mushroom.png")[0];

	//“–‚½‚è”»’è‚Ìİ’è
	collision.is_blocking = true;
	collision.object_type = eObjectType::eBlock;
	collision.hit_object_type.push_back(eObjectType::ePlayer);
}

void Mushroom::Update(float delata_second)
{
	location += velocity;
}

void Mushroom::Draw(const Vector2D& screen_offset) const
{
	__super::Draw(screen_offset);

}

void Mushroom::Finalize()
{
}

void Mushroom::OnHitCollision(GameObjectBase* hit_object)
{
	velocity *= -1;
}
