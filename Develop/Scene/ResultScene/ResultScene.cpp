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

//初期化処理
void ResultScene::Initialize()
{
	// マリオ画像の読込みと初期設定
	ResourceManager* rm = Singleton<ResourceManager>::GetInstance();
	mario_image = rm->GetImages("Resource/Images/Mario/mario.png", 9, 9, 1, 32, 32)[0];

	player_zanki = 3;
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
		return eSceneType::eInGame;
	}

	//現在のシーン情報を取得
	return GetNowSceneType();
}

//描画処理
void ResultScene::Draw()
{
	DrawString(0, 0, "リザルト画面です", GetColor(255, 255, 255), TRUE);
	DrawString(0, 90, "スペースキーでリスタート", GetColor(0, 255, 0), TRUE);
	DrawRotaGraph(D_WIN_MAX_X / 2 - ((D_OBJECT_SIZE * 2) * 1.5), D_WIN_MAX_Y / 2, 1.2, 0.0, mario_image, TRUE);
	SetFontSize(32);
	DrawFormatString(D_WIN_MAX_X / 2 - ((D_OBJECT_SIZE * 2) * 1), D_WIN_MAX_Y / 2 - (D_OBJECT_SIZE / 2), GetColor(255, 255, 255), " × %d", player_zanki, TRUE);
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
