#include "Hatena.h"
#include "DxLib.h"

#include "../../../Utility/ResourceManager.h"
#include "../../../Objects/GameObjectManager.h"
#include "../../ItemBase/Mushroom/Mushroom.h"

Hatena::Hatena() :
	is_kara(false),
	kara_image(NULL)
{
}

Hatena::~Hatena()
{
}

// 初期化処理
void Hatena::Initialize()
{
	box_size = Vector2D(D_OBJECT_SIZE);
	is_mobility = true;

	//画像の設定
	ResourceManager* rm = Singleton<ResourceManager>::GetInstance();
	hatena_animation = rm->GetImages("Resource/Images/Block/hatena.png", 4, 4, 1, 32, 32);
	kara_image = rm->GetImages("Resource/Images/Block/kara_block.png")[0];
	image = hatena_animation[0];

	//当たり判定の設定
	collision.is_blocking = true;
	collision.object_type = eObjectType::eBlock;
	collision.hit_object_type.push_back(eObjectType::ePlayer);
	collision.hit_object_type.push_back(eObjectType::eEnemy);
}

// 更新処理
void Hatena::Update(float delata_second)
{
	// 空かどうか
	if (is_kara == true)
	{
		image = kara_image;
	}
	else
	{
		// アニメーション
		AnimationControl(delata_second);
	}
}

// 描画処理
void Hatena::Draw(const Vector2D& screen_offset) const
{
	__super::Draw(screen_offset);
}

// 終了時処理
void Hatena::Finalize()
{
}

// ヒット時処理
void Hatena::OnHitCollision(GameObjectBase* hit_object)
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
	if (hit_object->GetCollision().object_type == eObjectType::ePlayer && is_kara == false)
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

			if (dot_x < dot_y)
			{
				// 主にX軸方向の衝突 (左または右)
				if (direction.x < 0)
				{
					// 左側から衝突
				}
				else
				{
					// 右側から衝突

				}
			}
			else
			{
				// 主にY軸方向の衝突 (上または下)
				if (direction.y < 0)
				{
					// 上側から衝突
					is_kara = true;
					Vector2D hatena_location = Vector2D(location.x, location.y - (box_size.y * 2));
					mush = objm->CreateObject<Mushroom>(hatena_location);
				}
				else
				{
					// 下側から衝突
				}
			}
		}
	}
}

//　アニメーションの制御
void Hatena::AnimationControl(float delta_second)
{
	//フレームレートで時間を計測
	animation_time += delta_second;
	//8秒経ったら画像を切り替える
	if (animation_time >= (1.0f / 4.0f))
	{
		//計測時間の初期化
		animation_time = 0.0f;
		//時間経過カウントの増加
		animation_count++;
		//カウントがアニメーション画像の要素数以上になったら
		if (animation_count >= hatena_num.size())
		{
			//カウントの初期化
			animation_count = 0;
		}
		// アニメーションが順番に代入される
		image = hatena_animation[hatena_num[animation_count]];
	}
}
