#include "Nokonoko.h"
#include "DxLib.h"

#include "../../../../Utility/ResourceManager.h"

Nokonoko::Nokonoko()
{
}

Nokonoko::~Nokonoko()
{
}

void Nokonoko::Initialize()
{
	//判定サイズの設定
	box_size = Vector2D(24.0f, 36.0f);
	is_mobility = true;

	//画像の設定
	ResourceManager* rm = Singleton<ResourceManager>::GetInstance();
	image = rm->GetImages("Resource/Images/Enemy/nokonoko.png", 2, 2, 1, 32, 64)[0];

	//当たり判定の設定
	collision.is_blocking = true;
	collision.object_type = eObjectType::eEnemy;
	collision.hit_object_type.push_back(eObjectType::ePlayer);
}

void Nokonoko::Update(float delata_second)
{
}

void Nokonoko::Draw(const Vector2D& screen_offset) const
{
	//親クラスの描画処理を呼び出す
	__super::Draw(screen_offset);

	DrawString(0, 150, "エネミーの描画ok", GetColor(255, 255, 255), TRUE);

	//判定サイズ描画
	DrawBox(location.x - box_size.x, location.y - (box_size.y - 12),
		location.x + box_size.x, location.y + (box_size.y + 12), GetColor(255, 0, 0), FALSE);
}

void Nokonoko::Finalize()
{
}

void Nokonoko::OnHitCollision(GameObjectBase* hit_object)
{
}
