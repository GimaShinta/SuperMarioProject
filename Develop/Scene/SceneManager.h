#pragma once

#include "../Singleton.h"
#include "SceneBase.h"

//�V�[���}�l�[�W���[�N���X
class SceneManager : public Singleton<class T>
{
private:
	SceneBase* current_scene;

public:
	SceneManager();
	~SceneManager();

public:
	//�C���X�^���X�̍폜
	static void DeleteInstance();

public:
	//����������
	void Initialize();

	/// <summary>
	/// �X�V����
	/// </summary>
	/// <param name="delta_second">1�t���[��������̎���</param>
	/// <returns></returns>
	bool Update(float delta_second);

	//�`�揈��
	void Draw();

	//�I��������
	void Finalize();

public:
	//�V�[���̐؂�ւ�
	void ChangeScene(eSceneType scene_type);

private:
	//�V�[���̐���
	SceneBase* CreateScene(eSceneType scene_type);
};

