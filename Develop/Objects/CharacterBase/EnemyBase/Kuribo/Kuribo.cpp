#include "Kuribo.h"
#include "DxLib.h"

#include "../../../../Utility/ResourceManager.h"

Kuribo::Kuribo()
{
}

Kuribo::~Kuribo()
{
}

void Kuribo::Initialize()
{
	box_size = Vector2D(32.0f);
	is_mobility = true;

	ResourceManager* rm = Singleton<ResourceManager>::GetInstance();
	image = rm->GetImages("Resource/Images/Enemy/kuribo.png", 3, 3, 1, 32, 32)[0];

	collision.is_blocking = true;
	collision.object_type = eObjectType::eEnemy;
	collision.hit_object_type.push_back(eObjectType::ePlayer);
}

void Kuribo::Update(float delata_second)
{
}

void Kuribo::Draw(const Vector2D& screen_offset) const
{
	__super::Draw(screen_offset);

	DrawString(0, 150, "エネミーの描画ok", GetColor(255, 255, 255), TRUE);

	//判定サイズ描画
	DrawBox(location.x - box_size.x, location.y - box_size.y,
		location.x + box_size.x, location.y + box_size.y, GetColor(255, 0, 0), FALSE);

}

void Kuribo::Finalize()
{

}

void Kuribo::OnHitCollision(GameObjectBase* hit_object)
{
}
