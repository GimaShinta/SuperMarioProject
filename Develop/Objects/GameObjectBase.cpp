#include "GameObjectBase.h"
#include "DxLib.h"

#include "GameObjectManager.h"
#include "../Utility/ResourceManager.h"
#include "../Application/Application.h"

GameObjectBase::GameObjectBase() :
	owner_scene(nullptr),
	location(0.0f),
	image(NULL),
	z_layer(0),
	is_mobility(false),
	is_destroy(false),
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

// �X�V����
void GameObjectBase::Update(float delata_second)
{
	// �E�B���h�E�O�I�u�W�F�N�g�̍폜
	// �n�ʃI�u�W�F�N�g�̔z�u�ʒu�̊֌W��-400�ȉ��ɂȂ�����
	GameObjectManager* objm = Singleton<GameObjectManager>::GetInstance();
	if (this->location.x <= -400)
	{
		objm->DestroyGameObject(this);
	}
	if (this->location.y >= 600 + this->GetBoxSize().y)
	{
		objm->DestroyGameObject(this);
	}
	if (this->is_destroy == true)
	{
		objm->DestroyGameObject(this);
	}
}

// �`�揈��
void GameObjectBase::Draw(const Vector2D& screen_offset) const
{
	// �I�t�Z�b�g�l����ɉ摜�̕`����s��
	Vector2D graph_location = this->location + screen_offset;
	DrawRotaGraphF(graph_location.x, graph_location.y, 1.5, 0.0, image, TRUE);
}

// �I��������
void GameObjectBase::Finalize()
{
}

// �q�b�g������
void GameObjectBase::OnHitCollision(GameObjectBase* hit_object)
{
}

/// <summary>
/// �A�j���[�V��������
/// </summary>
/// <param name="delta_second"></param>
/// <param name="animation_image">�A�j���[�V�������摜</param>
/// <param name="animation_num">�A�j���[�V��������</param>
void GameObjectBase::AnimationControl(float delta_second, std::vector<int>& animation_image, std::vector<int>& animation_num)
{
	//�t���[�����[�g�Ŏ��Ԃ��v��
	animation_time += delta_second;
	//8�b�o������摜��؂�ւ���
	if (animation_time >= (1.0f / 16.0f))
	{
		//�v�����Ԃ̏�����
		animation_time = 0.0f;
		//���Ԍo�߃J�E���g�̑���
		animation_count++;
		//�J�E���g���A�j���[�V�����摜�̗v�f���ȏ�ɂȂ�����
		if (animation_count >= animation_num.size())
		{
			//�J�E���g�̏�����
			animation_count = 0;
		}
		// �A�j���[�V���������Ԃɑ�������
		image = animation_image[animation_num[animation_count]];
	}
}

// �摜�̐ݒ�
void GameObjectBase::AnimationControl(float delta_second, int animation_imag)
{
	image = animation_imag;
}

void GameObjectBase::SetOwnerScene(GameObjectManager* scene)
{
 	this->owner_scene = scene;
}

// �ʒu���W�̐ݒ�
void GameObjectBase::SetLocation(const Vector2D& location)
{
	this->location = location;
}

// �ʒu���W�̎擾
Vector2D& GameObjectBase::GetLocation()
{
	return location;
}

// �I�u�W�F�N�g�T�C�Y�̎擾
Vector2D& GameObjectBase::GetBoxSize()
{
	return box_size;
}

// �e�I�u�W�F�N�g�̃R���W�������̎擾
const BoxCollision& GameObjectBase::GetCollision() const
{
	return collision;
}

const unsigned char GameObjectBase::GetZLayer() const
{
	return z_layer;
}

// ����
const bool& GameObjectBase::GetMobility() const
{
	return is_mobility;
}

