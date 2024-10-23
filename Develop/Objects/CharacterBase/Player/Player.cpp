#include "Player.h"
#include "DxLib.h"

#include "../../../Utility/ResourceManager.h"
#include "State/Factory/PlayerStateFactory.h"

#define D_GRAVITY (9.80f)      //重力加速度(m/ss)
#define D_MAX_SPEED (10.0f)

Player::Player()
{
}

Player::~Player()
{
}

void Player::Initialize()
{
	state = PlayerStateFactory::Get((*this), ePlayerState::IDLE);
	next_state = ePlayerState::NONE;
	velocity = Vector2D(0, 0);
	g_velocity = 0.0f;

	ResourceManager* rm = Singleton<ResourceManager>::GetInstance();
	image = rm->GetImages("Resource/Images/Mario/mario.png", 9, 9, 1, 32, 32)[0];
}

void Player::Update(float delta_second)
{
	// stateの変更処理
	if (next_state != ePlayerState::NONE)
	{
		state = PlayerStateFactory::Get((*this), next_state);
		next_state = ePlayerState::NONE;
	}

	//重力速度の計算
	g_velocity += D_GRAVITY / 444.0f;
	velocity.y += g_velocity;

	//最大重力の設定
	if (velocity.y > D_MAX_SPEED)
	{
		velocity.y = D_MAX_SPEED;
	}

	//状態別の更新処理を行う
	state->Update();

	//移動の実行
	location += velocity;

	//y600.0f地点を地面と仮定
	if (600.0f < location.y)
	{
		location.y = 600.0f;
		g_velocity = 0.0f;
		velocity = 0.0f;
	}

	//x0.0f地点を壁と仮定
	if (0.0f + box_size.x > location.x)
	{
		location.x = 0.0f + box_size.x;
		velocity = 0.0f;
	}
	//x1280.0f地点を壁と仮定
	if (1280.0f - box_size.x < location.x)
	{
		location.x = 1280.0f - box_size.x;
		velocity = 0.0f;
	}
}

void Player::Draw(const Vector2D& screen_offset) const
{
	__super::Draw(screen_offset);

	DrawString(0, 120, "プレイヤーの描画ok", GetColor(255, 255, 255), TRUE);

	//状態別の描画処理を行う
	state->Draw();
}

void Player::Finalize()
{
	PlayerStateFactory* factory = Singleton<PlayerStateFactory>::GetInstance();
	factory->Finalize();
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

void Player::SetNextState(ePlayerState next_state)
{
	this->next_state = next_state;
}
