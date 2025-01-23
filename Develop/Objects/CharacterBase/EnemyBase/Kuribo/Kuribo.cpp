#include "Kuribo.h"
#include "DxLib.h"

#include "../../../../Utility/ResourceManager.h"
#include "../../../../Objects/GameObjectManager.h"

Kuribo::Kuribo()
{
}

Kuribo::~Kuribo()
{
}

// ����������
void Kuribo::Initialize()
{
	// ����T�C�Y�̐ݒ�
	box_size = Vector2D(24.0f);
	is_mobility = true;
	velocity.x = 100.0f;

	// �摜�̐ݒ�
	ResourceManager* rm = Singleton<ResourceManager>::GetInstance();
	emove_animation = rm->GetImages("Resource/Images/Enemy/kuribo.png", 3, 3, 1, 32, 32);
	image = emove_animation[0];

	// �����蔻��̐ݒ�
	collision.is_blocking = true;
	collision.object_type = eObjectType::eEnemy;
	collision.hit_object_type.push_back(eObjectType::ePlayer);
}

// �X�V����
void Kuribo::Update(float delta_second)
{
	// �A�j���[�V��������
	GameObjectBase::AnimationControl(delta_second, emove_animation, emove_nums);

	// �ړ��̎��s
	location.x -= velocity.x * delta_second;

	__super::Update(delta_second);
}

//�`�揈��
void Kuribo::Draw(const Vector2D& screen_offset) const
{
	//�e�N���X�̕`�揈�����Ăяo��
	__super::Draw(screen_offset);

	DrawString(0, 150, "�G�l�~�[�̕`��ok", GetColor(255, 255, 255), TRUE);

	//����T�C�Y�`��
	//DrawBox(location.x - box_size.x, location.y - box_size.y,
	//	location.x + box_size.x, location.y + box_size.y, GetColor(255, 0, 0), FALSE);
}

//�I��������
void Kuribo::Finalize()
{

}

//�q�b�g������
void Kuribo::OnHitCollision(GameObjectBase* hit_object)
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
	if (hit_object->GetCollision().object_type == eObjectType::ePlayer)
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
				}
				else
				{
					// �E������Փ�
					// �E������̏Փˎ��̏���
				}
			}
			else
			{
				// ���Y�������̏Փ� (��܂��͉�)
				if (direction.y < 0)
				{
					// �㑤����Փ�
					// �㑤����̏Փˎ��̏���
					// ���S�t���O
				}
				else
				{
					// ��������Փ�
					// ��������̏Փˎ��̏���
					GameObjectManager* objm = Singleton<GameObjectManager>::GetInstance();
					objm->DestroyGameObject(this);
					// ���S�t���O��ݒ�
					is_destroy = true;
				}
			}
		}
	}
}