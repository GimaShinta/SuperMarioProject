#include "Hatena.h"
#include "DxLib.h"

#include "../../../Utility/ResourceManager.h"

Hatena::Hatena()
{
}

Hatena::~Hatena()
{
}

void Hatena::Initialize()
{
	box_size = Vector2D(D_OBJECT_SIZE);
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

void Hatena::Update(float delata_second)
{
}

void Hatena::Draw(const Vector2D& screen_offset) const
{
	__super::Draw(screen_offset);

	//”»’èƒTƒCƒY•`‰æ
	DrawBox(location.x - box_size.x, location.y - box_size.y,
		location.x + box_size.x, location.y + box_size.y, GetColor(255, 0, 0), FALSE);
}

void Hatena::Finalize()
{
}

void Hatena::OnHitCollision(GameObjectBase* hit_object)
{
}
