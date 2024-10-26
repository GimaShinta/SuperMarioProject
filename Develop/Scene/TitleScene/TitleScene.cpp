#include "TitleScene.h"
#include "DxLib.h"

#include "../../Utility/InputManager.h"

TitleScene::TitleScene():back_ground(NULL)
{
}

TitleScene::~TitleScene()
{
}

//����������
void TitleScene::Initialize()
{
}

/// <summary>
/// �X�V����
/// </summary>
/// <param name="delta_second">1�t���[��������̎���</param>
/// <returns>���݂̃V�[�����</returns>
eSceneType TitleScene::Update(float delta_second)
{
	//���͋@�\�̎擾
	InputManager* input = Singleton<InputManager>::GetInstance();

	//SPACE�L�[�ŃC���Q�[����ʂɑJ�ڂ���
	if (input->GetKeyDown(KEY_INPUT_SPACE))
	{
		return eSceneType::eInGame;
	}

	// �V�[�����
	return GetNowSceneType();
}

//�`�揈��
void TitleScene::Draw()
{
	DrawString(0,0,"�^�C�g����ʂł�",GetColor(255,255,255),TRUE);
	DrawString(0,60,"�X�y�[�X�L�[�ŃC���Q�[��",GetColor(0,255,0),TRUE);
}

//�I��������
void TitleScene::Finalize()
{
}

//���݂̃V�[�������擾
const eSceneType TitleScene::GetNowSceneType() const
{
	return eSceneType::eTitle;
}
