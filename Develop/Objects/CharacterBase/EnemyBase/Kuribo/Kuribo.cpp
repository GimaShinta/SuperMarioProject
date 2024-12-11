#include "Kuribo.h"
#include "DxLib.h"

#include "../../../../Utility/ResourceManager.h"

Kuribo::Kuribo()
{
}

Kuribo::~Kuribo()
{
}

//初期化処理
void Kuribo::Initialize()
{
	//判定サイズの設定
	box_size = Vector2D(24.0f);
	is_mobility = true;
	velocity.x = 100.0f;

	//画像の設定
	ResourceManager* rm = Singleton<ResourceManager>::GetInstance();
	emove_animation = rm->GetImages("Resource/Images/Enemy/kuribo.png", 3, 3, 1, 32, 32);
	image = emove_animation[0];

	//当たり判定の設定
	collision.is_blocking = true;
	collision.object_type = eObjectType::eEnemy;
	collision.hit_object_type.push_back(eObjectType::ePlayer);
}

//更新処理
void Kuribo::Update(float delta_second)
{
	// アニメーション制御
	GameObjectBase::AnimationControl(delta_second, emove_animation, emove_nums);

	// 移動の実行
	location.x -= velocity.x * delta_second;

	__super::Update(delta_second);
}

//描画処理
void Kuribo::Draw(const Vector2D& screen_offset) const
{
	//親クラスの描画処理を呼び出す
	__super::Draw(screen_offset);

	DrawString(0, 150, "エネミーの描画ok", GetColor(255, 255, 255), TRUE);

	//判定サイズ描画
	DrawBox(location.x - box_size.x, location.y - box_size.y,
		location.x + box_size.x, location.y + box_size.y, GetColor(255, 0, 0), FALSE);
}

//終了時処理
void Kuribo::Finalize()
{

}

//ヒット時処理
void Kuribo::OnHitCollision(GameObjectBase* hit_object)
{
}