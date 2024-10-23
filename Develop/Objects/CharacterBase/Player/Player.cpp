#include "Player.h"
#include "DxLib.h"

#include "../../../Utility/ResourceManager.h"

Player::Player()
{
}

Player::~Player()
{
}

void Player::Initialize()
{
	ResourceManager* rm = Singleton<ResourceManager>::GetInstance();
	image = rm->GetImages("Resource/Images/Mario/mario.png", 9, 9, 1, 32, 32)[0];
}

void Player::Update(float delata_second)
{
}

void Player::Draw(const Vector2D& screen_offset) const
{
	__super::Draw(screen_offset);
	DrawString(0, 120, "ÉvÉåÉCÉÑÅ[ÇÃï`âÊok", GetColor(255, 255, 255), TRUE);
}

void Player::Finalize()
{
}

int Player::GetZanki()
{
	return 0;
}

bool Player::GetPowerUp() const
{
	return false;
}

void Player::SetPowerDown()
{
}

bool Player::GetDestroy() const
{
	return false;
}

void Player::AnimationControl(float delta_second)
{
}
