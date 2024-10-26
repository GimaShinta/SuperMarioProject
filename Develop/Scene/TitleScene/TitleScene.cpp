#include "TitleScene.h"
#include "DxLib.h"

#include "../../Utility/InputManager.h"

TitleScene::TitleScene():back_ground(NULL)
{
}

TitleScene::~TitleScene()
{
}

//初期化処理
void TitleScene::Initialize()
{
}

/// <summary>
/// 更新処理
/// </summary>
/// <param name="delta_second">1フレーム当たりの時間</param>
/// <returns>現在のシーン情報</returns>
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

//描画処理
void TitleScene::Draw()
{
	DrawString(0,0,"タイトル画面です",GetColor(255,255,255),TRUE);
	DrawString(0,60,"スペースキーでインゲーム",GetColor(0,255,0),TRUE);
}

//終了時処理
void TitleScene::Finalize()
{
}

//現在のシーン情報を取得
const eSceneType TitleScene::GetNowSceneType() const
{
	return eSceneType::eTitle;
}
