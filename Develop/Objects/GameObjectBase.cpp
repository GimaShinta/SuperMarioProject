#include "GameObjectBase.h"
#include "DxLib.h"

#include "GameObjectManager.h"
#include "../Utility/ResourceManager.h"
#include "../Application/Application.h"

GameObjectBase::GameObjectBase() :
	owner_scene(nullptr),
	location(0.0f),
	image(NULL),
	z_layer(0),
	is_mobility(false),
	is_destroy(false),
	animation_count(0),
	animation_time(0.0f)
{
}

GameObjectBase::~GameObjectBase()
{
}

void GameObjectBase::Initialize()
{
}

// 更新処理
void GameObjectBase::Update(float delata_second)
{
	// ウィンドウ外オブジェクトの削除
	// 地面オブジェクトの配置位置の関係上-400以下になったら
	GameObjectManager* objm = Singleton<GameObjectManager>::GetInstance();
	if (this->location.x <= -400)
	{
		objm->DestroyGameObject(this);
	}
	if (this->location.y >= 600 + this->GetBoxSize().y)
	{
		objm->DestroyGameObject(this);
	}
	if (this->is_destroy == true)
	{
		objm->DestroyGameObject(this);
	}
}

// 描画処理
void GameObjectBase::Draw(const Vector2D& screen_offset) const
{
	// オフセット値を基に画像の描画を行う
	Vector2D graph_location = this->location + screen_offset;
	DrawRotaGraphF(graph_location.x, graph_location.y, 1.5, 0.0, image, TRUE);
}

// 終了時処理
void GameObjectBase::Finalize()
{
}

// ヒット時処理
void GameObjectBase::OnHitCollision(GameObjectBase* hit_object)
{
}

/// <summary>
/// アニメーション制御
/// </summary>
/// <param name="delta_second"></param>
/// <param name="animation_image">アニメーション総画像</param>
/// <param name="animation_num">アニメーション順序</param>
void GameObjectBase::AnimationControl(float delta_second, std::vector<int>& animation_image, std::vector<int>& animation_num)
{
	//フレームレートで時間を計測
	animation_time += delta_second;
	//8秒経ったら画像を切り替える
	if (animation_time >= (1.0f / 16.0f))
	{
		//計測時間の初期化
		animation_time = 0.0f;
		//時間経過カウントの増加
		animation_count++;
		//カウントがアニメーション画像の要素数以上になったら
		if (animation_count >= animation_num.size())
		{
			//カウントの初期化
			animation_count = 0;
		}
		// アニメーションが順番に代入される
		image = animation_image[animation_num[animation_count]];
	}
}

// 画像の設定
void GameObjectBase::AnimationControl(float delta_second, int animation_imag)
{
	image = animation_imag;
}

void GameObjectBase::SetOwnerScene(GameObjectManager* scene)
{
 	this->owner_scene = scene;
}

// 位置座標の設定
void GameObjectBase::SetLocation(const Vector2D& location)
{
	this->location = location;
}

// 位置座標の取得
Vector2D& GameObjectBase::GetLocation()
{
	return location;
}

// オブジェクトサイズの取得
Vector2D& GameObjectBase::GetBoxSize()
{
	return box_size;
}

// 各オブジェクトのコリジョン情報の取得
const BoxCollision& GameObjectBase::GetCollision() const
{
	return collision;
}

const unsigned char GameObjectBase::GetZLayer() const
{
	return z_layer;
}

// 動き
const bool& GameObjectBase::GetMobility() const
{
	return is_mobility;
}

