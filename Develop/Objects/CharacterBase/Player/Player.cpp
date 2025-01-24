#include "Player.h"
#include "DxLib.h"

#include "../../../Utility/ResourceManager.h"
#include "../../../Objects/GameObjectManager.h"
#include "State/Factory/PlayerStateFactory.h"
#include "../../../Application/Application.h"

#include <cstdlib>

#define D_GRAVITY (30.0f)      //�d�͉����x(m/ss)

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

	// ���̓ǂݍ���
	back_ground_sound = rm->GetSounds("Resource/Sounds/BGM_MarioGround.wav");
	goal_sound[0] = rm->GetSounds("Resource/Sounds/SE_PoleTouch.wav");
	goal_sound[1] = rm->GetSounds("Resource/Sounds/SE_Goal.wav");
	step_on_sound = rm->GetSounds("Resource/Sounds/SE_StepOn.wav");
	destroy_sound[0] = rm->GetSounds("Resource/Sounds/SE_Touch.wav");
	destroy_sound[1] = rm->GetSounds("Resource/Sounds/SE_Death.wav");

	// ���̍Đ�
	PlaySoundMem(back_ground_sound, DX_PLAYTYPE_BACK);

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
		AnimationControl(delta_second, nomalmario_animation, nomalmario_nums, 5, NULL, 6);
		break;
	case ePlayerLooksState::DEKAMARIO:
		is_huge = true;
		// �A�j���[�V��������
		AnimationControl(delta_second, dekamario_animation, dekamario_nums, 6, 1, NULL);
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

	// �ړ������s����֐��̌Ăяo��
	__super::Movement(delta_second);

	// ��ʊO�ō폜����֐��̌Ăяo��
	__super::Update(delta_second);
}

/// <summary>
/// �`�揈��
/// </summary>
/// <param name="screen_offset"></param>
void Player::Draw(const Vector2D& screen_offset) const
{
	// ��ԕʂ̕`�揈�����s��
	state->Draw();

	if (is_huge == false)
	{
		DrawRotaGraphF(location.x, location.y, 1.5, 0.0, image, TRUE, flip_flag);
	}
	else
	{
		DrawRotaGraphF(location.x, location.y - D_OBJECT_SIZE, 1.5, 0.0, image, TRUE, flip_flag);
	}
}

//�I��������
void Player::Finalize()
{
	// �C���X�^���X�̎擾
	PlayerStateFactory* factory = Singleton<PlayerStateFactory>::GetInstance();
	factory->Finalize();
	// �C���X�^���X�̍폜
	ResourceManager::DeleteInstance();
	PlayerStateFactory::DeleteInstance();

	// BGM�̒�~
	StopSoundMem(back_ground_sound);
}

/// <summary>
/// �q�b�g������
/// </summary>
/// <param name="hit_object">���������I�u�W�F�N�g</param>
void Player::OnHitCollision(GameObjectBase* hit_object)
{
	// �C���X�^���X�̎擾
	GameObjectManager* objm = Singleton<GameObjectManager>::GetInstance();

	//�Q�̃I�u�W�F�N�g�̋������擾
	Vector2D diff = location - hit_object->GetLocation();

	// �߂荞�ݕ������v�Z
	Vector2D direction = diff.Normalize();

	// �Փ˖ʂɑ΂���@���x�N�g�����v�Z
	Vector2D normal = direction * -1.0f;

	// �v���C���[�̑��x�x�N�g��
	Vector2D p_velocity = velocity;

	// �G���u���b�N�ɓ���������
	if (hit_object->GetCollision().object_type == eObjectType::eEnemy)
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
					// ���S�t���O
					is_destroy = true;
					// �T�E���h�̍Đ����~�߂�
					StopSoundMem(back_ground_sound);
					//// ���ʉ��Đ�
					//PlaySoundMem(destroy_sound[0], DX_PLAYTYPE_NORMAL);
					//PlaySoundMem(destroy_sound[1], DX_PLAYTYPE_BACK);
				}
				else
				{
					// �E������Փ�
					// �E������̏Փˎ��̏���
					// ���S�t���O
					is_destroy = true;
					// �T�E���h�̍Đ����~�߂�
					StopSoundMem(back_ground_sound);
					//// ���ʉ��Đ�
					//PlaySoundMem(destroy_sound[0], DX_PLAYTYPE_NORMAL);
					//PlaySoundMem(destroy_sound[1], DX_PLAYTYPE_BACK);
				}
			}
			else
			{
				// ���Y�������̏Փ� (��܂��͉�)
				if (direction.y < 0)
				{
					// �㑤����Փ�
					// �㑤����̏Փˎ��̏���
					velocity.y -= 1250.0f;
					// ���̍Đ�
					PlaySoundMem(step_on_sound, DX_PLAYTYPE_BACK);
				}
				else
				{
					// ��������Փ�
					// ��������̏Փˎ��̏���
					// ���S�t���O
					is_destroy = true;
				}
			}
		}
	}
	else if (hit_object->GetCollision().object_type == eObjectType::eGoal)
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

			if (dot_x < dot_y)
			{
				// ���X�������̏Փ� (���܂��͉E)
				if (direction.x < 0)
				{
					// ��������Փ�
					// ��������̏Փˎ��̏���
					location.x += normal.x * direction.x;
					goal = true;
					// �T�E���h�̍Đ����~�߂�
					StopSoundMem(back_ground_sound);
					//�@�T�E���h�Đ�
					PlaySoundMem(goal_sound[0], DX_PLAYTYPE_NORMAL);
					PlaySoundMem(goal_sound[1], DX_PLAYTYPE_NORMAL);
				}
				else
				{
					// �E������Փ�
					// �E������̏Փˎ��̏���
					location.x -= normal.x * direction.x;
					goal = true;
				}
			}
			else
			{
				// ���Y�������̏Փ� (��܂��͉�)
				if (direction.y < 0)
				{
					// �㑤����Փ�
					// �㑤����̏Փˎ��̏���
					location.y -= normal.y * direction.y;
				}
				else
				{
					// ��������Փ�
					// ��������̏Փˎ��̏���
					location.y += normal.y * direction.y;
				}
			}
		}
	}
	else
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

			if (dot_x < dot_y)
			{
				// ���X�������̏Փ� (���܂��͉E)
				if (direction.x < 0)
				{
					// ��������Փ�
					// ��������̏Փˎ��̏���
					location.x += normal.x * direction.x;
				}
				else
				{
					// �E������Փ�
					// �E������̏Փˎ��̏���
					location.x -= normal.x * direction.x;

				}
			}
			else
			{
				// ���Y�������̏Փ� (��܂��͉�)
				if (direction.y < 0)
				{
					// �㑤����Փ�
					// �㑤����̏Փˎ��̏���
					location.y -= normal.y * direction.y;
					//location.y = hit_object->GetLocation().y - (hit_object->GetBoxSize().y + D_OBJECT_SIZE);
					g_velocity = 0.0f;
				}
				else
				{
					// ��������Փ�
					// ��������̏Փˎ��̏���
					location.y += normal.y * direction.y;
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
void Player::AnimationControl(float delta_second, std::vector<int>& animation_image, std::vector<int>& animation_num, int n_jump, int n_squat, int n_destroy)
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
			break;
		case ePlayerState::DESTROY:
			image = animation_image[n_destroy];
			break;
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

// �S�[�����Ă��邩
bool Player::GetGoal()
{
	return goal;
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

// �v���C���[�̑��x���擾
Vector2D Player::GetVelocity()
{
	return velocity;
}

// �v���C���[�̃I�u�W�F�N�g�^�C�v��ύX����
void Player::SetObjectType(eObjectType type)
{
	collision.object_type = type;
}
