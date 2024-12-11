#include "ResultScene.h"
#include "DxLib.h"

#include "../../Utility/InputManager.h"

ResultScene::ResultScene()
{
}

ResultScene::~ResultScene()
{
}

//初期化処理
void ResultScene::Initialize()
{
}

/// <summary>
/// 更新処理
/// </summary>
/// <param name="delta_second">1フレーム当たりの時間</param>
/// <returns>現在のシーン情報</returns>
eSceneType ResultScene::Update(float delta_second)
{
	//入力機能の取得
	InputManager* input = Singleton<InputManager>::GetInstance();

	//SPACEキーでタイトル画面に遷移する
	if (input->GetKeyDown(KEY_INPUT_SPACE))
	{
		return eSceneType::eTitle;
	}
	//Zキーでインゲーム画面に遷移する
	if (input->GetKeyDown(KEY_INPUT_Z))
	{
		return eSceneType::eInGame;
	}

	//現在のシーン情報を取得
	return GetNowSceneType();
}

//描画処理
void ResultScene::Draw()
{
	DrawString(0, 0, "リザルト画面です", GetColor(255, 255, 255), TRUE);
	DrawString(0, 60, "スペースキーでタイトル", GetColor(0, 255, 0), TRUE);
	DrawString(0, 90, "Zキーでインゲーム", GetColor(0, 255, 0), TRUE);
}

//終了時処理
void ResultScene::Finalize()
{
	InputManager::DeleteInstance();
}

//現在のシーン情報を取得
const eSceneType ResultScene::GetNowSceneType() const
{
	return eSceneType::eResult;
}
