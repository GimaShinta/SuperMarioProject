#pragma once

#include "../SceneBase.h"
#include "../../Objects/GameObjectBase.h"

class InGameScene : public SceneBase
{
private:
	// �I�u�W�F�N�g�̏����i�[����\����
	struct MapObjectData 
	{
		char mode;
		int x_size;
		int y_size;
		int spos_x;
		int spos_y;
	};

private:
	class Player* player;
	class Kuribo* kuribo;
	class Nokonoko* nokonoko;
	class Fireboll* fireboll;

private:
	std::vector<MapObjectData> map_object;
	std::vector<int> back_ground_images;

private:
	int player_zanki;
	int back_ground_image;
	int back_ground_image1;
	int back_ground_image2;
	int back_ground_image3;
	Vector2D screen_location;
	Vector2D draw_location;
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

