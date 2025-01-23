#include "Hatena.h"
#include "DxLib.h"

#include "../../../Utility/ResourceManager.h"
#include "../../../Objects/GameObjectManager.h"
#include "../../ItemBase/Mushroom/Mushroom.h"

Hatena::Hatena() :
	is_kara(false),
	kara_image(NULL)
{
}

Hatena::~Hatena()
{
}

// ����������
void Hatena::Initialize()
{
	box_size = Vector2D(D_OBJECT_SIZE);
	is_mobility = true;

	//�摜�̐ݒ�
	ResourceManager* rm = Singleton<ResourceManager>::GetInstance();
	hatena_animation = rm->GetImages("Resource/Images/Block/hatena.png", 4, 4, 1, 32, 32);
	kara_image = rm->GetImages("Resource/Images/Block/kara_block.png")[0];
	image = hatena_animation[0];

	//�����蔻��̐ݒ�
	collision.is_blocking = true;
	collision.object_type = eObjectType::eBlock;
	collision.hit_object_type.push_back(eObjectType::ePlayer);
	collision.hit_object_type.push_back(eObjectType::eEnemy);
}

// �X�V����
void Hatena::Update(float delata_second)
{
	// �󂩂ǂ���
	if (is_kara == true)
	{
		image = kara_image;
	}
	else
	{
		// �A�j���[�V����
		AnimationControl(delata_second);
	}
}

// �`�揈��
void Hatena::Draw(const Vector2D& screen_offset) const
{
	__super::Draw(screen_offset);
}

// �I��������
void Hatena::Finalize()
{
}

// �q�b�g������
void Hatena::OnHitCollision(GameObjectBase* hit_object)
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
	if (hit_object->GetCollision().object_type == eObjectType::ePlayer && is_kara == false)
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
				}
				else
				{
					// �E������Փ�

				}
			}
			else
			{
				// ���Y�������̏Փ� (��܂��͉�)
				if (direction.y < 0)
				{
					// �㑤����Փ�
					is_kara = true;
					Vector2D hatena_location = Vector2D(location.x, location.y - (box_size.y * 2));
					mush = objm->CreateObject<Mushroom>(hatena_location);
				}
				else
				{
					// ��������Փ�
				}
			}
		}
	}
}

//�@�A�j���[�V�����̐���
void Hatena::AnimationControl(float delta_second)
{
	//�t���[�����[�g�Ŏ��Ԃ��v��
	animation_time += delta_second;
	//8�b�o������摜��؂�ւ���
	if (animation_time >= (1.0f / 4.0f))
	{
		//�v�����Ԃ̏�����
		animation_time = 0.0f;
		//���Ԍo�߃J�E���g�̑���
		animation_count++;
		//�J�E���g���A�j���[�V�����摜�̗v�f���ȏ�ɂȂ�����
		if (animation_count >= hatena_num.size())
		{
			//�J�E���g�̏�����
			animation_count = 0;
		}
		// �A�j���[�V���������Ԃɑ�������
		image = hatena_animation[hatena_num[animation_count]];
	}
}
