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

