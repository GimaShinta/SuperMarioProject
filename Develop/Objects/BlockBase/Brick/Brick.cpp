#include "Brick.h"
#include "DxLib.h"

#include "../../../Utility/ResourceManager.h"

Brick::Brick()
{
}

Brick::~Brick()
{
}

void Brick::Initialize()
{
	box_size = Vector2D(D_OBJECT_SIZE);
	is_mobility = true;

	//âÊëúÇÃê›íË
	ResourceManager* rm = Singleton<ResourceManager>::GetInstance();
	image = rm->GetImages("Resource/Images/Block/block.png", 1, 1, 1, 32, 32)[0];

	//ìñÇΩÇËîªíËÇÃê›íË
	collision.is_blocking = true;
	collision.object_type = eObjectType::eBlock;
	collision.hit_object_type.push_back(eObjectType::ePlayer);
	collision.hit_object_type.push_back(eObjectType::eEnemy);
}

void Brick::Update(float delata_second)
{
}

void Brick::Draw(const Vector2D& screen_offset) const
{
	__super::Draw(screen_offset);

	//îªíËÉTÉCÉYï`âÊ
	DrawBox(location.x - box_size.x, location.y - box_size.y,
		location.x + box_size.x, location.y + box_size.y, GetColor(255, 0, 0), FALSE);
}

void Brick::Finalize()
{
}

void Brick::OnHitCollision(GameObjectBase* hit_object)
{
}
