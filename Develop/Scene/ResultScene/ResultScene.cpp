#include "ResultScene.h"
#include "DxLib.h"

#include "../../Utility/InputManager.h"

ResultScene::ResultScene()
{
}

ResultScene::~ResultScene()
{
}

//����������
void ResultScene::Initialize()
{
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
		return eSceneType::eTitle;
	}
	//Z�L�[�ŃC���Q�[����ʂɑJ�ڂ���
	if (input->GetKeyDown(KEY_INPUT_Z))
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
	DrawString(0, 60, "�X�y�[�X�L�[�Ń^�C�g��", GetColor(0, 255, 0), TRUE);
	DrawString(0, 90, "Z�L�[�ŃC���Q�[��", GetColor(0, 255, 0), TRUE);
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
