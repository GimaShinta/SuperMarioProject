#include "Kai.h"
#include "DxLib.h"

#include "../../../Utility/ResourceManager.h"


Kai::Kai()
{
}

Kai::~Kai()
{
}

void Kai::Initialize()
{
	box_size = Vector2D(D_OBJECT_SIZE);
	is_mobility = true;

	//画像の設定
	ResourceManager* rm = Singleton<ResourceManager>::GetInstance();
	image = rm->GetImages("Resource/Images/Block/kai_block.png", 1, 1, 1, 32, 32)[0];

	//当たり判定の設定
	collision.is_blocking = true;
	collision.object_type = eObjectType::eBlock;
	collision.hit_object_type.push_back(eObjectType::ePlayer);
	collision.hit_object_type.push_back(eObjectType::eEnemy);
}

void Kai::Update(float delata_second)
{
}

void Kai::Draw(const Vector2D& screen_offset) const
{
	__super::Draw(screen_offset);
}

void Kai::Finalize()
{
}

void Kai::OnHitCollision(GameObjectBase* hit_object)
{
}

void Kai::SetGroundData(int x_size, int y_size)
{
	box_size.x = x_size * D_OBJECT_SIZE;
	box_size.y = y_size * D_OBJECT_SIZE;
}
