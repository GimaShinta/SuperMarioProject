#include "Kuribo.h"
#include "DxLib.h"

#include "../../../../Utility/ResourceManager.h"

Kuribo::Kuribo()
{
}

Kuribo::~Kuribo()
{
}

//����������
void Kuribo::Initialize()
{
	//����T�C�Y�̐ݒ�
	box_size = Vector2D(24.0f);
	is_mobility = true;
	velocity.x = 100.0f;

	//�摜�̐ݒ�
	ResourceManager* rm = Singleton<ResourceManager>::GetInstance();
	emove_animation = rm->GetImages("Resource/Images/Enemy/kuribo.png", 3, 3, 1, 32, 32);
	image = emove_animation[0];

	//�����蔻��̐ݒ�
	collision.is_blocking = true;
	collision.object_type = eObjectType::eEnemy;
	collision.hit_object_type.push_back(eObjectType::ePlayer);
}

//�X�V����
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
	DrawBox(location.x - box_size.x, location.y - box_size.y,
		location.x + box_size.x, location.y + box_size.y, GetColor(255, 0, 0), FALSE);
}

//�I��������
void Kuribo::Finalize()
{

}

//�q�b�g������
void Kuribo::OnHitCollision(GameObjectBase* hit_object)
{
}