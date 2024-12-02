#include "Player.h"
#include "DxLib.h"

#include "../../../Utility/ResourceManager.h"
#include "../../../Objects/GameObjectManager.h"
#include "State/Factory/PlayerStateFactory.h"

#define D_GRAVITY (9.80f)      //�d�͉����x(m/ss)

/*�ł����Ȃ����疄�܂邩�炻�ꂼ��ŕ`�悵��������������*/


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
	now_state = ePlayerState::NONE;
	now_looks_state = ePlayerLooksState::NOMALMARIO;
	velocity = Vector2D(0, 0);
	g_velocity = 0.0f;
	is_mobility = true;
	is_huge = false;
	box_size = Vector2D(D_OBJECT_SIZE);
	p_box_size[0] = box_size;
	p_box_size[1] = Vector2D(D_OBJECT_SIZE, (D_OBJECT_SIZE * 2));

	ResourceManager* rm = Singleton<ResourceManager>::GetInstance();
	nomalmario_animation = rm->GetImages("Resource/Images/Mario/mario.png", 9, 9, 1, 32, 32);
	dekamario_animation = rm->GetImages("Resource/Images/Mario/dekamario.png", 10, 10, 1, 32, 64);
	image = nomalmario_animation[0];

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

	//�d�͑��x�̌v�Z
	g_velocity += D_GRAVITY;
	velocity.y += g_velocity * delta_second;

	//��ԕʂ̍X�V�������s��
	state->Update(delta_second);

	//�ړ��̎��s
	__super::Movement(delta_second);

	//y600.0f�n�_��n�ʂƉ���
	if (location.y > 600.0f)
	{
		location.y = 600.0f;
		g_velocity = 0.0f;
	}

	//x0.0f�n�_��ǂƉ���
	if (location.x < 0.0f + box_size.x)
	{
		location.x = 0.0f + box_size.x;
	}

	//�w�i�X�N���[�����E�[�ɒ�������ړ��͈͂��g�傷��
	if (screen_end == false)
	{
		//�E�B���h�E��x480.0f�n�_��ǂƉ���
		if (location.x > 480.0f - (box_size.x * 2 ))
		{
			location.x = 480.0f - (box_size.x * 2);
			velocity.x = 0.0f;
		}
	}
	else
	{
		GameObjectManager* mag = Singleton<GameObjectManager>::GetInstance();
		mag->DestroyGameObject(this);
		//�E�B���h�E��x960.0f�n�_��ǂƉ���
		if (location.x > 960.0f - box_size.x)
		{
			location.x = 960.0f - box_size.x;
		}
	}
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
		DrawRotaGraphF(location.x, location.y, 1.5, 0.0, image, TRUE);
	}
	else
	{
		DrawRotaGraphF(location.x, location.y - D_OBJECT_SIZE, 1.5, 0.0, image, TRUE);
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
}

//�q�b�g������
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
		//else
		//{
		//	//�߂荞�񂾍��������߂�
		//	location.x += diff.x + box_size.x;
		//}

		//// 2�̃I�u�W�F�N�g�̋������擾
		//Vector2D diff = location - hit_object->GetLocation();

		//// 2�̃I�u�W�F�N�g�̓����蔻��̑傫�����擾
		//Vector2D pbox_size = ((box_size + hit_object->GetBoxSize()) / 2.0f);

		//// �������傫�����傫���ꍇ�AHit���������
		//if (fabsf(diff.x) < pbox_size.x) 
		//{
		//	// �߂荞�ݗʂ��v�Z
		//	float overlap = pbox_size.x - fabsf(diff.x);

		//	// �Փ˕����𔻒肵�A�ʒu�𒲐�
		//	if (diff.x > 0) 
		//	{
		//		// �E��������Փ�
		//		location.x -= overlap;
		//	}
		//	else 
		//	{
		//		// ����������Փ�
		//		location.x += overlap;
		//	}
		//}

#else
		// �����蔻������擾���āA�J�v�Z��������ʒu�����߂�
		BoxCollision hc = hit_object->GetCollision();
		hc.point[0] += hit_object->GetLocation() - hit_object->GetBoxSize();
		hc.point[1] += hit_object->GetLocation() + hit_object->GetBoxSize();

		Vector2D p_point[2];
		p_point[0] = location + box_size;
		p_point[0] = location - box_size;

		float diff[2];
		diff[0] = p_point[0].x - hc.point[0].x;

#endif
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
			GameObjectBase::AnimationControl(delta_second, animation_image, animation_num);
			break;
		case ePlayerState::IDLE:
			image = animation_image[0];
			break;
		case ePlayerState::JUMP:
			image = animation_image[n_jump];
			break;
		case ePlayerState::SQUAT:
			image = animation_image[n_squat];
		case ePlayerState::NONE:
			break;
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


//���̃V�[���ɐ؂�ւ�
void Player::SetNextState(ePlayerState next_state)
{
	this->next_state = next_state;
}

//�v���C���[�̔���T�C�Y���擾
Vector2D& Player::GetBoxSize()
{
	return box_size;
}

//�v���C���[�̈ړ���Ԃ��擾
ePlayerState Player::GetPlayerState() const
{
	//���݂̈ړ����
	return now_state;
}

//�w�i�X�N���[�����[�ɒ���������ݒ�
void Player::SetScreenEnd(bool screen_end)
{
	this->screen_end = screen_end;
}
