#include "Ground.h"
#include "DxLib.h"

#include "../../../Utility/ResourceManager.h"

Ground::Ground()
{
}

Ground::~Ground()
{
}

// ‰Šú‰»ˆ—
void Ground::Initialize()
{
	is_mobility = true;

	//‰æ‘œ‚Ìİ’è
	ResourceManager* rm = Singleton<ResourceManager>::GetInstance();
	image = rm->GetImages("Resource/Images/Block/floor.png", 1, 1, 1, 32, 32)[0];

	//“–‚½‚è”»’è‚Ìİ’è
	collision.is_blocking = true;
	collision.object_type = eObjectType::eGround;
	collision.hit_object_type.push_back(eObjectType::ePlayer);
	collision.hit_object_type.push_back(eObjectType::eEnemy);
}

void Ground::Update(float delata_second)
{
}

// •`‰æˆ—
void Ground::Draw(const Vector2D& screen_offset) const
{

}

// ƒqƒbƒgˆ—
void Ground::OnHitCollision(GameObjectBase* hit_object)
{
}

void Ground::SetGroundData(int x_size, int y_size)
{
	box_size.x = x_size * D_OBJECT_SIZE;
	box_size.y = y_size * D_OBJECT_SIZE;
}
