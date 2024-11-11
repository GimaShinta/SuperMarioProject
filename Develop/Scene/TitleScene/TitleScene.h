#pragma once

#include "../SceneBase.h"

//�^�C�g���V�[���N���X
class TitleScene : public SceneBase
{
private:
	int back_ground_image;

public:
	TitleScene();
	~TitleScene();

public:
	//����������
	void Initialize()override;

	/// <summary>
	/// �X�V����
	/// </summary>
	/// <param name="delta_second">1�t���[��������̎���</param>
	/// <returns>���݂̃V�[�����</returns>
	eSceneType Update(float delta_second)override;

	//�`�揈��
	void Draw()override;

	//�I��������
	void Finalize()override;

	// ���݂̃V�[���^�C�v�����擾����
	const eSceneType GetNowSceneType() const override;
};

