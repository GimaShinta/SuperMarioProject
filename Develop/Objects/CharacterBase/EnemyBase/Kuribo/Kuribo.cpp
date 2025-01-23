#include "Kuribo.h"
#include "DxLib.h"

#include "../../../../Utility/ResourceManager.h"
#include "../../../../Objects/GameObjectManager.h"

Kuribo::Kuribo()
{
}

Kuribo::~Kuribo()
{
}

// 初期化処理
void Kuribo::Initialize()
{
	// 判定サイズの設定
	box_size = Vector2D(24.0f);
	is_mobility = true;
	velocity.x = 100.0f;

	// 画像の設定
	ResourceManager* rm = Singleton<ResourceManager>::GetInstance();
	emove_animation = rm->GetImages("Resource/Images/Enemy/kuribo.png", 3, 3, 1, 32, 32);
	image = emove_animation[0];

	// 当たり判定の設定
	collision.is_blocking = true;
	collision.object_type = eObjectType::eEnemy;
	collision.hit_object_type.push_back(eObjectType::ePlayer);
}

// 更新処理
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
	//DrawBox(location.x - box_size.x, location.y - box_size.y,
	//	location.x + box_size.x, location.y + box_size.y, GetColor(255, 0, 0), FALSE);
}

//終了時処理
void Kuribo::Finalize()
{

}

//ヒット時処理
void Kuribo::OnHitCollision(GameObjectBase* hit_object)
{
	// インスタンスの取得
	GameObjectManager* objm = Singleton<GameObjectManager>::GetInstance();

	// めり込み量を見て比べる。xが優先されているように見える
	//２つのオブジェクトの距離を取得
	Vector2D diff = location - hit_object->GetLocation();

	// めり込み方向を計算
	Vector2D direction = diff.Normalize();

	// 衝突面に対する法線ベクトルを計算
	Vector2D normal = direction * -1.0f;

	// プレイヤーの速度ベクトル
	Vector2D p_velocity = velocity;

	// 敵かブロックに当たった時
	if (hit_object->GetCollision().object_type == eObjectType::ePlayer)
	{
		// 衝突方向の判定
		if (Vector2D::Dot(normal, p_velocity) < 0)
		{
			// プレイヤーは衝突面から離れる方向に動いている
			// 特に処理は不要
		}
		else
		{
			// プレイヤーは衝突面に向かって動いている
			// 衝突方向をX軸、Y軸で比較
			Vector2D x_axis(1.0f, 0.0f);
			Vector2D y_axis(0.0f, 1.0f);

			float dot_x = abs(Vector2D::Dot(normal, x_axis));
			float dot_y = abs(Vector2D::Dot(normal, y_axis));

			if (dot_x > dot_y)
			{
				// 主にX軸方向の衝突 (左または右)
				if (direction.x < 0)
				{
					// 左側から衝突
					// 左側からの衝突時の処理
				}
				else
				{
					// 右側から衝突
					// 右側からの衝突時の処理
				}
			}
			else
			{
				// 主にY軸方向の衝突 (上または下)
				if (direction.y < 0)
				{
					// 上側から衝突
					// 上側からの衝突時の処理
					// 死亡フラグ
				}
				else
				{
					// 下側から衝突
					// 下側からの衝突時の処理
					GameObjectManager* objm = Singleton<GameObjectManager>::GetInstance();
					objm->DestroyGameObject(this);
					// 死亡フラグを設定
					is_destroy = true;
				}
			}
		}
	}
}