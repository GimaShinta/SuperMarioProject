#include "Ground.h"
#include "DxLib.h"

#include "../../../Utility/ResourceManager.h"

Ground::Ground()
{
}

Ground::~Ground()
{
}

// 初期化処理
void Ground::Initialize()
{
	is_mobility = true;

	//画像の設定
	ResourceManager* rm = Singleton<ResourceManager>::GetInstance();
	image = rm->GetImages("Resource/Images/Block/floor.png", 1, 1, 1, 32, 32)[0];

	//当たり判定の設定
	collision.is_blocking = true;
	collision.object_type = eObjectType::eGround;
	collision.hit_object_type.push_back(eObjectType::ePlayer);
	collision.hit_object_type.push_back(eObjectType::eEnemy);
}

void Ground::Update(float delata_second)
{
}

// 描画処理
void Ground::Draw(const Vector2D& screen_offset) const
{
	//判定サイズ描画
	DrawBox(location.x - box_size.x, location.y - box_size.y,
		location.x + box_size.x, location.y + box_size.y, GetColor(255, 0, 0), FALSE);
}

// ヒット時処理
void Ground::OnHitCollision(GameObjectBase* hit_object)
{
}

void Ground::SetGroundData(int x_size, int y_size)
{
	box_size.x = x_size * D_OBJECT_SIZE;
	box_size.y = y_size * D_OBJECT_SIZE;
}
