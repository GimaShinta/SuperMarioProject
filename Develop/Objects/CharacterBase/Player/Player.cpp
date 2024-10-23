#include "Player.h"
#include "DxLib.h"

#include "../../../Utility/ResourceManager.h"
#include "State/Factory/PlayerStateFactory.h"

#define D_GRAVITY (9.80f)      //�d�͉����x(m/ss)
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
	// state�̕ύX����
	if (next_state != ePlayerState::NONE)
	{
		state = PlayerStateFactory::Get((*this), next_state);
		next_state = ePlayerState::NONE;
	}

	//�d�͑��x�̌v�Z
	g_velocity += D_GRAVITY / 444.0f;
	velocity.y += g_velocity;

	//�ő�d�͂̐ݒ�
	if (velocity.y > D_MAX_SPEED)
	{
		velocity.y = D_MAX_SPEED;
	}

	//��ԕʂ̍X�V�������s��
	state->Update();

	//�ړ��̎��s
	location += velocity;

	//y600.0f�n�_��n�ʂƉ���
	if (600.0f < location.y)
	{
		location.y = 600.0f;
		g_velocity = 0.0f;
		velocity = 0.0f;
	}

	//x0.0f�n�_��ǂƉ���
	if (0.0f + box_size.x > location.x)
	{
		location.x = 0.0f + box_size.x;
		velocity = 0.0f;
	}
	//x1280.0f�n�_��ǂƉ���
	if (1280.0f - box_size.x < location.x)
	{
		location.x = 1280.0f - box_size.x;
		velocity = 0.0f;
	}
}

void Player::Draw(const Vector2D& screen_offset) const
{
	__super::Draw(screen_offset);

	DrawString(0, 120, "�v���C���[�̕`��ok", GetColor(255, 255, 255), TRUE);

	//��ԕʂ̕`�揈�����s��
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
