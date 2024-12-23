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

	//画像の設定
	ResourceManager* rm = Singleton<ResourceManager>::GetInstance();
	hatena_animation = rm->GetImages("Resource/Images/Block/hatena.png", 4, 4, 1, 32, 32);
	image = hatena_animation[0];

	//当たり判定の設定
	collision.is_blocking = true;
	collision.object_type = eObjectType::eBlock;
	collision.hit_object_type.push_back(eObjectType::ePlayer);
	collision.hit_object_type.push_back(eObjectType::eEnemy);
}

void Hatena::Update(float delata_second)
{
}

void Hatena::Draw(const Vector2D& screen_offset) const
{
	__super::Draw(screen_offset);

	//判定サイズ描画
	DrawBox(location.x - box_size.x, location.y - box_size.y,
		location.x + box_size.x, location.y + box_size.y, GetColor(255, 0, 0), FALSE);
}

void Hatena::Finalize()
{
}

void Hatena::OnHitCollision(GameObjectBase* hit_object)
{
}
