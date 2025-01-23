#include "Pole.h"

#include "../../../Utility/ResourceManager.h"

Pole::Pole()
{
}

Pole::~Pole()
{
}

void Pole::Initialize()
{
	box_size = Vector2D(D_OBJECT_SIZE);
	is_mobility = true;

	//“–‚½‚è”»’è‚Ìİ’è
	collision.is_blocking = true;
	collision.object_type = eObjectType::eGoal;
	collision.hit_object_type.push_back(eObjectType::ePlayer);
	collision.hit_object_type.push_back(eObjectType::eEnemy);
}

void Pole::Update(float delata_second)
{
}

void Pole::Draw(const Vector2D& screen_offset) const
{
	__super::Draw(screen_offset);
}

void Pole::Finalize()
{
}

void Pole::OnHitCollision(GameObjectBase* hit_object)
{
}

void PoleTop::Initialize()
{
	__super::Initialize();

	//‰æ‘œ‚Ìİ’è
	ResourceManager* rm = Singleton<ResourceManager>::GetInstance();
	image = rm->GetImages("Resource/Images/pole.png", 1, 1, 1, 32, 32)[0];
}

void PoleDown::Initialize()
{
	__super::Initialize();

	//‰æ‘œ‚Ìİ’è
	ResourceManager* rm = Singleton<ResourceManager>::GetInstance();
	image = rm->GetImages("Resource/Images/pole_down.png", 1, 1, 1, 32, 32)[0];
}
