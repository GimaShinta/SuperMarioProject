#include "ResultScene.h"
#include "DxLib.h"

#include "../../Utility/InputManager.h"

ResultScene::ResultScene()
{
}

ResultScene::~ResultScene()
{
}

void ResultScene::Initialize()
{
}

eSceneType ResultScene::Update(float delta_second)
{
	//���͋@�\�̎擾
	InputManager* input = Singleton<InputManager>::GetInstance();

	//SPACE�L�[�ŃC���Q�[����ʂɑJ�ڂ���
	if (input->GetKeyDown(KEY_INPUT_SPACE))
	{
		return eSceneType::eTitle;
	}
	if (input->GetKeyDown(KEY_INPUT_Z))
	{
		return eSceneType::eInGame;
	}

	return GetNowSceneType();
}

void ResultScene::Draw()
{
	DrawString(0, 0, "���U���g��ʂł�", GetColor(255, 255, 255), TRUE);
	DrawString(0, 60, "�X�y�[�X�L�[�Ń^�C�g��", GetColor(0, 255, 0), TRUE);
	DrawString(0, 90, "Z�L�[�ŃC���Q�[��", GetColor(0, 255, 0), TRUE);
}

void ResultScene::Finalize()
{
}

const eSceneType ResultScene::GetNowSceneType() const
{
	return eSceneType::eResult;
}
