#pragma once

#include "../SceneBase.h"
#include "../../Objects/GameObjectBase.h"

class InGameScene : public SceneBase
{
private:
	class Player* player;
	class Kuribo* kuribo;
	class Nokonoko* nokonoko;
	class Fireboll* fireboll;

private:
	int player_zanki;
	int back_ground_image;
	Vector2D screen_location;
	bool screen_end;

public:
	InGameScene();
	~InGameScene();

public:
	//����������
	void Initialize();

	/// <summary>
	/// �X�V����
	/// </summary>
	/// <param name="delta_second">1�t���[��������̎���</param>
	/// <returns>���݂̃V�[�����</returns>
	eSceneType Update(float delta_second)override;

	//�`�揈��
	void Draw();

	//�I��������
	void Finalize();

	// ���݂̃V�[���^�C�v�����擾����
	const eSceneType GetNowSceneType() const override;

private:
	//�X�e�[�W�Ǎ���
	void LoadStageMapCSV();
	//�I�u�W�F�N�g�Ǎ���
	void LoadStageMapObject();
};

