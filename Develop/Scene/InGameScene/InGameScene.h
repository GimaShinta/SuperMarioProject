#pragma once

#include "../SceneBase.h"
#include "../../Objects/GameObjectBase.h"

class InGameScene : public SceneBase
{
private:
	// �I�u�W�F�N�g�����i�[����\����
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
	class Ground* ground;
	class Hatena* hatena;
	class Brick* brick;
	class Kai* kai;
	class BlockBase* block;
	class EnemyBase* enemy;

private:
	std::vector<BlockBase*> blocks;
	std::vector<EnemyBase*> enemys;
	std::vector<MapObjectData> map_object;
	std::vector<int> back_ground_images;

private:
	int player_zanki;
	int back_ground_image;
	int back_ground_sora;
	int back_ground_block;
	int back_ground_blocks;
	int back_ground_mountain[6];
	int back_ground_ha[3];
	int back_ground_cloud[6];
	Vector2D screen_location;
	Vector2D draw_location;
	Vector2D camera_location;
	bool screen_end;
	bool is_scroll;

public:
	InGameScene();
	~InGameScene();

public:
	// ����������
	void Initialize();

	/// <summary>
	/// �X�V����
	/// </summary>
	/// <param name="delta_second">1�t���[��������̎���</param>
	/// <returns>���݂̃V�[�����</returns>
	eSceneType Update(float delta_second)override;

	// �`�揈��
	void Draw();

	// �I��������
	void Finalize();

	// ���݂̃V�[���^�C�v�����擾����
	const eSceneType GetNowSceneType() const override;

private:
	// �X�e�[�W�Ǎ���
	void LoadStageMapCSV();
	// �I�u�W�F�N�g�Ǎ���
	void LoadStageMapObject();

	void LoadImages();

private:
	Vector2D ChengeLocation(const Vector2D& pos);
};

