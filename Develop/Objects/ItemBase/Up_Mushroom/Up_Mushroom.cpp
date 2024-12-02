#include "Up_Mushroom.h"

Up_Mushroom::Up_Mushroom()
{
}

Up_Mushroom::~Up_Mushroom()
{
}

void Up_Mushroom::Initialize()
{
}

void Up_Mushroom::Update(float delata_second)
{
}

void Up_Mushroom::Draw(const Vector2D& screen_offset) const
{
	//親クラスの描画処理を呼び出す
	__super::Draw(screen_offset);
}

void Up_Mushroom::Finalize()
{
}

void Up_Mushroom::OnHitCollision(GameObjectBase* hit_object)
{
}
