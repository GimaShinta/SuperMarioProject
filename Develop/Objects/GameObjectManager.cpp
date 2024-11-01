#include "GameObjectManager.h"

GameObjectManager::GameObjectManager()
{
}

GameObjectManager::~GameObjectManager()
{
	//����Y��h�~
	Finalize();
}

//����������
void GameObjectManager::Initialize()
{
}

//�X�V����
void GameObjectManager::Update(const float& delta_second)
{
	//�����ł���I�u�W�F�N�g�����C���z��Ɉړ�������
	CheckCreateObject();

	// ���X�g���̃I�u�W�F�N�g���X�V����
	for (GameObjectBase* obj : game_object)
	{
		obj->Update(delta_second);
	}

	// �����蔻��m�F����
	for (int i = 0; i < game_object.size(); i++)
	{
		//�ړ��̋���
		if (game_object[i]->GetMobility() == false)
		{
			continue;
		}

		//���Ă���I�u�W�F�N�g�������ł���Γ����蔻��𖳂���
		for (int j = 0; j < game_object.size(); j++)
		{
			if (i == j)
			{
				continue;
			}

			//�������Ă��邩���`�F�b�N
			CheckCollision(game_object[i], game_object[j]);
		}
	}

	//�폜�����I�u�W�F�N�g��z��ɓ����
	CheckDesroyObject();
}

//�`�揈��
void GameObjectManager::Draw() const
{
	// �I�u�W�F�N�g���X�g���̃I�u�W�F�N�g��`�悷��
	for (GameObjectBase* obj : game_object)
	{
		//���C���z��ɂ���I�u�W�F�N�g�̕`��
		obj->Draw(screen_offset);
	}
}

//�I��������
void GameObjectManager::Finalize()
{
	// �I�u�W�F�N�g���X�g���̃I�u�W�F�N�g��j������
	DestoryAllObject();

	// ���I�z��̉��
	if (!create_object.empty())
	{
		create_object.clear();
	}
	if (!destroy_object.empty())
	{
		destroy_object.clear();
	}
}

//��������I�u�W�F�N�g�����邩������
void GameObjectManager::CheckCreateObject()
{
	// ��������I�u�W�F�N�g������΁A�I�u�W�F�N�g���X�g���ɑ}������
	if (!create_object.empty())
	{
		for (GameObjectBase* obj : create_object)
		{
			// ���C���[������ɏ��Ԃ����ւ���
			int z_layer = obj->GetZLayer();
			std::vector<GameObjectBase*>::iterator itr = game_object.begin();	// �I�u�W�F�N�g���X�g�̐擪
			// ���X�g�̖����ɂȂ�܂ő�������
			for (; itr != game_object.end(); itr++)
			{
				// Z���C���[���傫���ꏊ�ɗv�f��ǉ�����
				// �� itr->ZLayer{1, 1, 2, 3}�Az_layer = 2 �̎�
				//    itr->ZLayer{1, 1, 2, z_layer, 3}�Ƃ���
				if (z_layer < (*itr)->GetZLayer())
				{
					break;
				}
			}
			// ���X�g�̓r���ɑ}������
			game_object.insert(itr, obj);
		}
		// �������X�g���������
		create_object.clear();
	}
}

//�폜�����I�u�W�F�N�g�����邩������
void GameObjectManager::CheckDesroyObject()
{
	// �j�����X�g������łȂ��ꍇ�A���X�g���̃I�u�W�F�N�g��j������
	if (!destroy_object.empty())
	{
		for (GameObjectBase* obj : destroy_object)
		{
			std::vector<GameObjectBase*>::iterator itr = game_object.begin();	// �I�u�W�F�N�g���X�g�̐擪
			// ���X�g�̖����ɂȂ�܂ő�������
			for (; itr != game_object.end(); itr++)
			{
				// ���X�g���ɂ���΁A�폜����
				if ((*itr) == obj)
				{
					game_object.erase(itr);
					obj->Finalize();
					delete obj;
					break;
				}
			}
		}
		// ���I�z��̊J��
		game_object.clear();
	}
}

//std::vector<GameObjectBase*>& GameObjectManager::CreateGameObject()
//{
//	return ;
//}

//�폜�z��ɂ���I�u�W�F�N�g���폜����
void GameObjectManager::DestroyGameObject(GameObjectBase* target)
{
	// �k���|�`�F�b�N
	if (target == nullptr)
	{
		return;
	}

	// �j���I�u�W�F�N�g���X�g���ɂ���΁A�ǉ����Ȃ�
	for (GameObjectBase* obj : destroy_object)
	{
		if (obj == target)
		{
			return;
		}
	}

	// �j�����s���I�u�W�F�N�g���X�g�ɒǉ�����
	destroy_object.push_back(target);
}

//�����蔻��̃`�F�b�N
void GameObjectManager::CheckCollision(GameObjectBase* target, GameObjectBase* partner)
{
#if 0
	// �k���|�`�F�b�N
	if (target == nullptr || partner == nullptr)
	{
		return;
	}

	//�Q�̃I�u�W�F�N�g�̏������擾
	Vector2D diff = target->GetLocation() - partner->GetLocation();

	//�Q�̃I�u�W�F�N�g�̓����蔻��̑傫�����擾
	Vector2D box_size = ((target->GetBoxSize() + partner->GetBoxSize()) / 2.0f);

	BoxCollision tc = target->GetCollision();
	BoxCollision pc = partner->GetCollision();

	// �����蔻�肪�L�����m�F����
	if (tc.IsCheckHitTarget(pc.object_type) || pc.IsCheckHitTarget(tc.object_type))
	{
		//�������傫�����傫���ꍇ�AHit���������
		if ((fabsf(diff.x) < box_size.x)&& (fabsf(diff.y) < box_size.y))
		{
			//�����������Ƃ��I�u�W�F�N�g�ɒʒm����
			target->OnHitCollision(partner);
			partner->OnHitCollision(target);
		}
	}

#else

	// ���g�������Ă��邩���`�F�b�N
	if (target == nullptr || partner == nullptr)
	{
		return;
	}

	// �����蔻������擾
	BoxCollision tc = target->GetCollision();
	BoxCollision pc = partner->GetCollision();

	// �����蔻�肪�L�����m�F����
	if (tc.IsCheckHitTarget(pc.object_type) || pc.IsCheckHitTarget(tc.object_type))
	{
		// �Ίp����̒��_���W�����߂�
		// target��`�̍���̍��W�����߂�
		tc.point[0] += target->GetLocation() - target->GetBoxSize();
		// targt��`�̉E���̍��W�����߂�
		tc.point[1] += target->GetLocation() + target->GetBoxSize();
		// partner��`�̍���̍��W�����߂�
		pc.point[0] += partner->GetLocation() - partner->GetBoxSize();
		// partner��`�̉E���̍��W�����߂�
		pc.point[1] += partner->GetLocation() + partner->GetBoxSize();

		// �J�v�Z�����m�̓����蔻��
		if (IsCheckCollision(tc, pc))
		{
			// �������Ă��邱�Ƃ�ʒm����
			target->OnHitCollision(partner);
			partner->OnHitCollision(target);
		}

	}

#endif
}

const Vector2D GameObjectManager::GetScreenOffset() const
{
	return screen_offset;
}

//���C���z��ɂ���I�u�W�F�N�g��S�č폜
void GameObjectManager::DestoryAllObject()
{
	// �I�u�W�F�N�g���X�g����Ȃ珈�����I������
	if (game_object.empty())
	{
		return;
	}
	// �I�u�W�F�N�g���X�g���̃I�u�W�F�N�g���폜����
	for (GameObjectBase* obj : game_object)
	{
		obj->Finalize();
		delete obj;
	}
	// ���I�z��̉��
	game_object.clear();
}