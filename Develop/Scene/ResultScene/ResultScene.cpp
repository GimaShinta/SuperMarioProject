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
	//入力機能の取得
	InputManager* input = Singleton<InputManager>::GetInstance();

	//SPACEキーでインゲーム画面に遷移する
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
	DrawString(0, 0, "リザルト画面です", GetColor(255, 255, 255), TRUE);
	DrawString(0, 60, "スペースキーでタイトル", GetColor(0, 255, 0), TRUE);
	DrawString(0, 90, "Zキーでインゲーム", GetColor(0, 255, 0), TRUE);
}

void ResultScene::Finalize()
{
}

const eSceneType ResultScene::GetNowSceneType() const
{
	return eSceneType::eResult;
}
