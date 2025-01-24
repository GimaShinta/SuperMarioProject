#include "TitleScene.h"
#include "DxLib.h"
#include "../../Application/Application.h"

#include "../../Utility/InputManager.h"
#include "../../Utility/ResourceManager.h"

TitleScene::TitleScene():back_ground_image(NULL)
{
}

TitleScene::~TitleScene()
{
}

//����������
void TitleScene::Initialize()
{
	// �摜�ݒ�
	ResourceManager* rm = Singleton<ResourceManager>::GetInstance();
	back_ground_image = rm->GetImages("Resource/Images/title.png")[0];
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
	// �w�i�摜�̕`��
	DrawRotaGraph(480, 360, 1.5, 0.0, back_ground_image, TRUE);

	SetFontSize(48);
	DrawString(250,450,"�P�@PLAYER�@GAME",GetColor(255,255,255),TRUE);
	DrawString(400,550,"SPACE",GetColor(255,255,255),TRUE);
	SetFontSize(16);
}

//�I��������
void TitleScene::Finalize()
{
	InputManager::DeleteInstance();
}

//���݂̃V�[�������擾
const eSceneType TitleScene::GetNowSceneType() const
{
	return eSceneType::eTitle;
}
