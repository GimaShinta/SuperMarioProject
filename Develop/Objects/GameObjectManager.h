#pragma once

#include "../Singleton.h"
#include "GameObjectBase.h"

#include <vector>
#include <string>

// �I�u�W�F�N�g�̐����Ɣj�����Ǘ�����N���X
class GameObjectManager : public Singleton<class T>
{
private:
	// �����������I�u�W�F�N�g������z��
	std::vector<GameObjectBase*> create_object;
	// �j���������I�u�W�F�N�g������z��
	std::vector<GameObjectBase*> destroy_object;
	// �C���Q�[���ɑ��݂���I�u�W�F�N�g������z��
	std::vector<GameObjectBase*> game_object;
	Vector2D screen_offset;// �X�N���[���I�t�Z�b�g�̓E�B���h�E��0,0�ʒu����ǂꂾ������Ă���̂��𔻒肷��̂Ɏg����


public:
	GameObjectManager();
	virtual ~GameObjectManager();

public:
	// �C���X�^���X�̍폜
	static void DeleteInstance();

public:
	// ����������
	virtual void Initialize();

	// �X�V����
	virtual void Update(const float& delta_second);

	// �`�揈��
	virtual void Draw() const;

	// �I��������
	virtual void Finalize();

	// �����ł���I�u�W�F�N�g�����邩���`�F�b�N
	virtual void CheckCreateObject();

	// �폜�ł���I�u�W�F�N�g�����邩���`�F�b�N
	virtual void CheckDesroyObject();

	//virtual std::vector<GameObjectBase*>& CreateGameObject();

	// �I�u�W�F�N�g�̐���
	template <class OBJECT>
	OBJECT* CreateObject(const Vector2D& generate_location)
	{
		// ��������Q�[���I�u�W�F�N�g�N���X�𓮓I�m��
		OBJECT* new_instance = new OBJECT();
		// GameObjectBase���p�����Ă��邩�m�F
		GameObjectBase* new_object = dynamic_cast<GameObjectBase*>(new_instance);
		// �G���[�`�F�b�N
		if (new_object == nullptr)
		{
			// ���I�m�ۂ����������̊J��
			delete new_instance;
			// ��O�e�L�X�g��ʒm
			throw std::string("�Q�[���I�u�W�F�N�g�������ł��܂���ł���");
			return nullptr;
		}
		// �V�[�����̐ݒ�
		new_object->SetOwnerScene(this);
		// �I�u�W�F�N�g�̏�����
		new_object->Initialize();
		// �ʒu���̐ݒ�
		new_object->SetLocation(generate_location);
		// �����I�u�W�F�N�g���X�g�̖����Ɋi�[����
		create_object.push_back(new_object);
		// ���������Q�[���I�u�W�F�N�g�̃|�C���^��Ԃ�
		return new_instance;
	}

	// �I�u�W�F�N�g���폜����
	void DestroyGameObject(GameObjectBase* target);

public:
	// �����蔻��̃`�F�b�N
	virtual void CheckCollision(GameObjectBase* target, GameObjectBase* partner);

	const Vector2D GetScreenOffset() const;

private:
	//�S�ẴI�u�W�F�N�g���폜
	void DestoryAllObject();

};
