#include "TitleScene.h"
#include "DxLib.h"

#include "../../Utility/InputManager.h"

TitleScene::TitleScene():back_ground(NULL)
{
}

TitleScene::~TitleScene()
{
}

void TitleScene::Initialize()
{
}

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

void TitleScene::Draw()
{
	DrawString(0,0,"�^�C�g����ʂł�",GetColor(255,255,255),TRUE);
	DrawString(0,60,"�X�y�[�X�L�[�ŃC���Q�[��",GetColor(0,255,0),TRUE);
}

void TitleScene::Finalize()
{
}

const eSceneType TitleScene::GetNowSceneType() const
{
	return eSceneType::eTitle;
}
