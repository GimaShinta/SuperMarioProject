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

//初期化処理
void TitleScene::Initialize()
{
	// 画像設定
	ResourceManager* rm = Singleton<ResourceManager>::GetInstance();
	back_ground_image = rm->GetImages("Resource/Images/title.png")[0];
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
	// 背景画像の描画
	DrawRotaGraph(480, 360, 1.5, 0.0, back_ground_image, TRUE);

	SetFontSize(48);
	DrawString(250,450,"１　PLAYER　GAME",GetColor(255,255,255),TRUE);
	DrawString(400,550,"SPACE",GetColor(255,255,255),TRUE);
	SetFontSize(16);
}

//終了時処理
void TitleScene::Finalize()
{
	InputManager::DeleteInstance();
}

//現在のシーン情報を取得
const eSceneType TitleScene::GetNowSceneType() const
{
	return eSceneType::eTitle;
}
