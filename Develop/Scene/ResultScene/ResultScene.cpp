#include "ResultScene.h"
#include "../../Application/Application.h"
#include "DxLib.h"

#include "../../Utility/InputManager.h"
#include "../../Utility/ResourceManager.h"

ResultScene::ResultScene()
{
}

ResultScene::~ResultScene()
{
}

//����������
void ResultScene::Initialize()
{
	// �}���I�摜�̓Ǎ��݂Ə����ݒ�
	ResourceManager* rm = Singleton<ResourceManager>::GetInstance();
	mario_image = rm->GetImages("Resource/Images/Mario/mario.png", 9, 9, 1, 32, 32)[0];

	player_zanki = 3;
}

/// <summary>
/// �X�V����
/// </summary>
/// <param name="delta_second">1�t���[��������̎���</param>
/// <returns>���݂̃V�[�����</returns>
eSceneType ResultScene::Update(float delta_second)
{
	//���͋@�\�̎擾
	InputManager* input = Singleton<InputManager>::GetInstance();

	//SPACE�L�[�Ń^�C�g����ʂɑJ�ڂ���
	if (input->GetKeyDown(KEY_INPUT_SPACE))
	{
		return eSceneType::eInGame;
	}

	//���݂̃V�[�������擾
	return GetNowSceneType();
}

//�`�揈��
void ResultScene::Draw()
{
	DrawString(0, 0, "���U���g��ʂł�", GetColor(255, 255, 255), TRUE);
	DrawString(0, 90, "�X�y�[�X�L�[�Ń��X�^�[�g", GetColor(0, 255, 0), TRUE);
	DrawRotaGraph(D_WIN_MAX_X / 2 - ((D_OBJECT_SIZE * 2) * 1.5), D_WIN_MAX_Y / 2, 1.2, 0.0, mario_image, TRUE);
	SetFontSize(32);
	DrawFormatString(D_WIN_MAX_X / 2 - ((D_OBJECT_SIZE * 2) * 1), D_WIN_MAX_Y / 2 - (D_OBJECT_SIZE / 2), GetColor(255, 255, 255), " �~ %d", player_zanki, TRUE);
}

//�I��������
void ResultScene::Finalize()
{
	InputManager::DeleteInstance();
}

//���݂̃V�[�������擾
const eSceneType ResultScene::GetNowSceneType() const
{
	return eSceneType::eResult;
}
