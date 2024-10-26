#pragma once

#include "../SceneBase.h"

//���U���g�V�[���N���X
class ResultScene : public SceneBase
{
private:
	class Player* player;

private:
	int back_ground;
	int player_zanki;

public:
	ResultScene();
	~ResultScene();

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
};

