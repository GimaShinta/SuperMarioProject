#include "GameObjectBase.h"
#include "DxLib.h"

#include "GameObjectManager.h"
#include "../Utility/ResourceManager.h"

GameObjectBase::GameObjectBase() :
	owner_scene(nullptr),
	location(0.0f),
	image(NULL),
	z_layer(0),
	is_mobility(false),
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

void GameObjectBase::Update(float delata_second)
{
}

void GameObjectBase::Draw(const Vector2D& screen_offset) const
{
	// オフセット値を基に画像の描画を行う
	Vector2D graph_location = this->location + screen_offset;
	DrawRotaGraphF(graph_location.x, graph_location.y, 1.5, 0.0, image, TRUE);
}

void GameObjectBase::Finalize()
{
}

void GameObjectBase::OnHitCollision(GameObjectBase* hit_object)
{
}

//アニメーション制御
void GameObjectBase::AnimationControl(float delta_second, std::vector<int>& animation_image, std::vector<int>& animation_num)
{
	//フレームレートで時間を計測
	animation_time += delta_second;
	//8秒経ったら画像を切り替える
	if (animation_time >= (1.0f / 10.0f))
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

void GameObjectBase::AnimationControl(float delta_second, int animation_imag)
{
	image = animation_imag;
}

void GameObjectBase::SetOwnerScene(GameObjectManager* scene)
{
	this->owner_scene = scene;
}

void GameObjectBase::SetLocation(const Vector2D& location)
{
	this->location = location;
}

Vector2D& GameObjectBase::GetLocation()
{
	return location;
}

Vector2D& GameObjectBase::GetBoxSize()
{
	return box_size;
}

const BoxCollision& GameObjectBase::GetCollision() const
{
	return collision;
}

const unsigned char GameObjectBase::GetZLayer() const
{
	return z_layer;
}

const bool& GameObjectBase::GetMobility() const
{
	return is_mobility;
}

