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

//����������
void Player::Initialize()
{
	state = PlayerStateFactory::Get((*this), ePlayerState::IDLE);
	next_state = ePlayerState::NONE;
	velocity = Vector2D(0, 0);
	g_velocity = 0.0f;
	is_mobility = true;

	ResourceManager* rm = Singleton<ResourceManager>::GetInstance();
	image = rm->GetImages("Resource/Images/Mario/mario.png", 9, 9, 1, 32, 32)[0];

	collision.is_blocking = true;
	collision.object_type = eObjectType::ePlayer;
	collision.hit_object_type.push_back(eObjectType::eEnemy);
}

/// <summary>
/// �X�V����
/// </summary>
/// <param name="delta_second">1�t���[��������̎���</param>
void Player::Update(float delta_second)
{
	// state�̕ύX����
	if (next_state != ePlayerState::NONE)
	{
		state = PlayerStateFactory::Get((*this), next_state);
		next_state = ePlayerState::NONE;
	}

#if 1
	//�d�͑��x�̌v�Z
	g_velocity += D_GRAVITY / 444.0f;
	velocity.y += g_velocity;

	//�ő�d�͂̐ݒ�
	if (velocity.y > D_MAX_SPEED)
	{
		velocity.y = D_MAX_SPEED;
	}
#endif

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

/// <summary>
/// �`�揈��
/// </summary>
/// <param name="screen_offset"></param>
void Player::Draw(const Vector2D& screen_offset) const
{
	__super::Draw(screen_offset);

	DrawString(0, 120, "�v���C���[�̕`��ok", GetColor(255, 255, 255), TRUE);

	//��ԕʂ̕`�揈�����s��
	state->Draw();
}

//�I��������
void Player::Finalize()
{
	//�C���X�^���X�̎擾
	PlayerStateFactory* factory = Singleton<PlayerStateFactory>::GetInstance();
	factory->Finalize();
}

void Player::OnHitCollision(GameObjectBase* hit_object)
{
	if (hit_object->GetCollision().object_type == eObjectType::eEnemy)
	{
#if 1
		//�Q�̃I�u�W�F�N�g�̋������擾
		Vector2D diff = location - hit_object->GetLocation();

		//�Q�̃I�u�W�F�N�g�̓����蔻��̑傫�����擾
		Vector2D pbox_size = ((box_size + hit_object->GetBoxSize()) / 2.0f);

		//�������傫�����傫���ꍇ�AHit���������
		if ((fabsf(diff.x) < box_size.x))
		{
			//�߂荞�񂾍��������߂�
			location.x -= diff.x + box_size.x;
		}
		if ((fabsf(diff.y) < box_size.y))
		{
			//�߂荞�񂾍��������߂�
			location.y -= diff.y + box_size.y;
			velocity.y -= 15;
		}
#endif
	}
}

//�c��c�@�̎擾
int Player::GetZanki()
{
	return 0;
}

//�p���[�A�b�v��Ԃ�������
bool Player::GetPowerUp() const
{
	return false;
}

//�p���[�_�E��������
void Player::SetPowerDown()
{
}

//���񂾏�Ԃ�������
bool Player::GetDestroy() const
{
	return false;
}

//�A�j���[�V��������
void Player::AnimationControl(float delta_second)
{
}

//���̃V�[���ɐ؂�ւ�
void Player::SetNextState(ePlayerState next_state)
{
	this->next_state = next_state;
}

Vector2D& Player::GetBoxSize()
{
	return box_size;
}
