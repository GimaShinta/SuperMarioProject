#include "Player.h"
#include "DxLib.h"

#include "../../../Utility/ResourceManager.h"
#include "../../../Objects/GameObjectManager.h"
#include "State/Factory/PlayerStateFactory.h"
#include "../../../Application/Application.h"

#include <cstdlib>

#define D_GRAVITY (9.80f)      //�d�͉����x(m/ss)

/*�ł����Ȃ����疄�܂邩�炻�ꂼ��ŕ`�悵��������������*/


Player::Player() :
	  zanki(0)
	, coin_count(0)
	, is_star(false)
	, screen_end(false)
	, is_huge(false)
	, flip_flag(FALSE)
{
}

Player::~Player()
{
}

//����������
void Player::Initialize()
{
	// �l�̏�����
	state = PlayerStateFactory::Get((*this), ePlayerState::IDLE);
	next_state = ePlayerState::NONE;
	now_state = ePlayerState::NONE;
	now_looks_state = ePlayerLooksState::NOMALMARIO;
	velocity = Vector2D(0, 0);
	g_velocity = 0.0f;
	is_mobility = true;
	box_size = Vector2D(D_OBJECT_SIZE);
	p_box_size[0] = box_size;
	p_box_size[1] = Vector2D(D_OBJECT_SIZE, (D_OBJECT_SIZE * 2));

	// �}���I�摜�̓Ǎ��݂Ə����ݒ�
	ResourceManager* rm = Singleton<ResourceManager>::GetInstance();
	nomalmario_animation = rm->GetImages("Resource/Images/Mario/mario.png", 9, 9, 1, 32, 32);
	dekamario_animation = rm->GetImages("Resource/Images/Mario/dekamario.png", 10, 10, 1, 32, 64);
	image = nomalmario_animation[0];

	// �����蔻��̃I�u�W�F�N�g�ݒ�
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
	// �����ڂ̏�Ԃɂ���ď�����ύX
	switch (now_looks_state)
	{
	case ePlayerLooksState::NOMALMARIO:
		is_huge = false;
		// �A�j���[�V��������
		AnimationControl(delta_second, nomalmario_animation, nomalmario_nums, 5, NULL);
		break;
	case ePlayerLooksState::DEKAMARIO:
		is_huge = true;
		// �A�j���[�V��������
		AnimationControl(delta_second, dekamario_animation, dekamario_nums, 6, 1);
		break;
	case ePlayerLooksState::FIREMARIO:
		is_huge = true;
		break;
	case ePlayerLooksState::STARNOMALMARIO:
		is_huge = false;
		break;
	case ePlayerLooksState::STARDEKAMARIO:
		is_huge = true;
		break;
	case ePlayerLooksState::DESTROYMARIO:
		break;
	}

	// �傫���ɂ���ē����蔻��T�C�Y��ύX����
	if (is_huge == false)
	{
		box_size = p_box_size[0];
	}
	else
	{
		box_size = p_box_size[1];
	}

	// state�̕ύX����
	if (next_state != ePlayerState::NONE && is_mobility == true)
	{
		//���݂̈ړ���Ԃ�ۊ�
		now_state = next_state;

		state = PlayerStateFactory::Get((*this), next_state);
		next_state = ePlayerState::NONE;
	}

	//��ԕʂ̍X�V�������s��
	state->Update(delta_second);

	//�d�͑��x�̌v�Z
	g_velocity += D_GRAVITY;
	velocity.y += g_velocity * delta_second;

	//x0.0f�n�_��ǂƉ���
	if (location.x < 0.0f + box_size.x)
	{
		location.x = 0.0f + box_size.x;
	}

	//�w�i�X�N���[�����E�[�ɒ�������v���C���[�̈ړ��͈͂��g�傷��
	if (screen_end == false)
	{
		//�E�B���h�E�̔����̒n�_��ǂƉ���
		if (location.x > D_WIN_MAX_X / 2)
		{
			location.x = D_WIN_MAX_X / 2;
		}
	}
	else
	{
		//�E�B���h�E�̉E�[�n�_��ǂƉ���
		if (location.x > D_WIN_MAX_X - box_size.x)
		{
			location.x = D_WIN_MAX_X - box_size.x;
		}
	}

	// �ړ��̎��s
	__super::Movement(delta_second);

	// ��ʊO�ō폜����
	__super::Update(delta_second);
}

/// <summary>
/// �`�揈��
/// </summary>
/// <param name="screen_offset"></param>
void Player::Draw(const Vector2D& screen_offset) const
{
	//��ԕʂ̕`�揈�����s��
	state->Draw();

	if (is_huge == false)
	{
		DrawRotaGraphF(location.x, location.y, 1.5, 0.0, image, TRUE, flip_flag);
	}
	else
	{
		DrawRotaGraphF(location.x, location.y - D_OBJECT_SIZE, 1.5, 0.0, image, TRUE, flip_flag);
	}

	//�e�N���X�̕`�揈�����s��
	//__super::Draw(screen_offset);

	DrawString(0, 120, "�v���C���[�̕`��ok", GetColor(255, 255, 255), TRUE);
}

//�I��������
void Player::Finalize()
{
	//�C���X�^���X�̎擾
	PlayerStateFactory* factory = Singleton<PlayerStateFactory>::GetInstance();
	factory->Finalize();
	ResourceManager::DeleteInstance();
	PlayerStateFactory::DeleteInstance();
}

//�q�b�g������
void Player::OnHitCollision(GameObjectBase* hit_object)
{
	// �C���X�^���X�̎擾
	GameObjectManager* objm = Singleton<GameObjectManager>::GetInstance();

	// �߂荞�ݗʂ����Ĕ�ׂ�Bx���D�悳��Ă���悤�Ɍ�����
	//�Q�̃I�u�W�F�N�g�̋������擾
	Vector2D diff = location - hit_object->GetLocation();

	// �߂荞�ݕ������v�Z
	Vector2D direction = diff.Normalize();

	// �Փ˖ʂɑ΂���@���x�N�g�����v�Z
	Vector2D normal = direction * -1.0f;

	// �v���C���[�̑��x�x�N�g��
	Vector2D p_velocity = velocity;

	// �G���u���b�N�ɓ���������
	if (hit_object->GetCollision().object_type == eObjectType::eEnemy || hit_object->GetCollision().object_type == eObjectType::eBlock)
	{
		// �Փ˕����̔���
		if (Vector2D::Dot(normal, p_velocity) < 0)
		{
			// �v���C���[�͏Փ˖ʂ��痣�������ɓ����Ă���
			// ���ɏ����͕s�v
		}
		else
		{
			// �v���C���[�͏Փ˖ʂɌ������ē����Ă���
			// �Փ˕�����X���AY���Ŕ�r
			Vector2D x_axis(1.0f, 0.0f);
			Vector2D y_axis(0.0f, 1.0f);

			float dot_x = abs(Vector2D::Dot(normal, x_axis));
			float dot_y = abs(Vector2D::Dot(normal, y_axis));

			if (dot_x > dot_y)
			{
				// ���X�������̏Փ� (���܂��͉E)
				if (direction.x < 0)
				{
					// ��������Փ�
					// ��������̏Փˎ��̏���
					objm->DestroyGameObject(this);
				}
				else
				{
					// �E������Փ�
					// �E������̏Փˎ��̏���
					objm->DestroyGameObject(this);
				}
			}
			else
			{
				// ���Y�������̏Փ� (��܂��͉�)
				if (direction.y < 0)
				{
					// �㑤����Փ�
					// �㑤����̏Փˎ��̏���
					velocity.y -= 1000.0f;
				}
				else
				{
					// ��������Փ�
					// ��������̏Փˎ��̏���
					objm->DestroyGameObject(this);
				}
			}
		}
	}

	// ���������̂��n�ʂ�������
	if (hit_object->GetCollision().object_type == eObjectType::eGround)
	{
		float ground_location = hit_object->GetLocation().y - (hit_object->GetBoxSize().y + D_OBJECT_SIZE);
		// y600.0f�n�_��n�ʂƉ���.
		if (location.y > ground_location)
		{
			location.y = ground_location;
			g_velocity = 0.0f;
		}
	}
}

/// <summary>
/// �A�j���[�V�����̐���
/// </summary>
/// <param name="delta_second">1�t���[��������̎���</param>
/// <param name="animation_image">�A�j���[�V�������摜</param>
/// <param name="animation_num">�A�j���[�V��������</param>
/// <param name="n_jump">�W�����v�摜�̈ʒu</param>
/// <param name="n_squat">���Ⴊ�݉摜�̈ʒu</param>
void Player::AnimationControl(float delta_second, std::vector<int>& animation_image, std::vector<int>& animation_num, int n_jump, int n_squat)
{
	switch (now_state)
	{
		case ePlayerState::RUN:
			// �A�j���[�V�������摜�ƃA�j���[�V���������������Ƃ���
			GameObjectBase::AnimationControl(delta_second, animation_image, animation_num);
			break;
		case ePlayerState::IDLE:
			// ��~���Ă���摜����
			image = animation_image[0];
			break;
		case ePlayerState::JUMP:
			// n_jump�Ԗڂɂ���W�����v�摜����
			image = animation_image[n_jump];
			break;
		case ePlayerState::SQUAT:
			// n_squat�Ԗڂɂ��邵�Ⴊ�݉摜����
			image = animation_image[n_squat];
		case ePlayerState::NONE:
			break;
	}
}

// �c��c�@�̎擾
int Player::GetZanki()
{
	return 0;
}

// �p���[�A�b�v��Ԃ�������
bool Player::GetPowerUp() const
{
	return false;
}

// �p���[�_�E��������
void Player::SetPowerDown()
{
}

// ���񂾏�Ԃ�������
bool Player::GetDestroy() const
{
	return false;
}


// ���̃V�[���ɐ؂�ւ�
void Player::SetNextState(ePlayerState next_state)
{
	this->next_state = next_state;
}

// �v���C���[�̔���T�C�Y���擾
Vector2D& Player::GetBoxSize()
{
	return box_size;
}

// �v���C���[�̈ړ���Ԃ��擾
ePlayerState Player::GetPlayerState() const
{
	//���݂̈ړ����
	return now_state;
}

// �w�i�X�N���[�����[�ɒ���������ݒ�
void Player::SetScreenEnd(bool screen_end)
{
	this->screen_end = screen_end;
}

Vector2D Player::GetVelocity()
{
	return velocity;
}
