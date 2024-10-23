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

	//入力機能の取得
	InputManager* input = Singleton<InputManager>::GetInstance();

	//SPACEキーでインゲーム画面に遷移する
	if (input->GetKeyDown(KEY_INPUT_SPACE))
	{
		return eSceneType::eInGame;
	}

	// シーン情報
	return GetNowSceneType();
}

void TitleScene::Draw()
{
	DrawString(0,0,"タイトル画面です",GetColor(255,255,255),TRUE);
	DrawString(0,60,"スペースキーでインゲーム",GetColor(0,255,0),TRUE);
}

void TitleScene::Finalize()
{
}

const eSceneType TitleScene::GetNowSceneType() const
{
	return eSceneType::eTitle;
}
