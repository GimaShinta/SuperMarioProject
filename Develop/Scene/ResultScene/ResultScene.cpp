#include "ResultScene.h"
#include "../../Application/Application.h"
#include "DxLib.h"

#include "../../Utility/InputManager.h"
#include "../../Utility/ResourceManager.h"

int player_zanki = 3;

ResultScene::ResultScene():
	mario_image(NULL),
	gameover_sound(NULL)
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
	gameover_sound = rm->GetSounds("Resource/Sounds/SE_GameOver.wav");
	destroy_sound[0] = rm->GetSounds("Resource/Sounds/SE_Touch.wav");
	destroy_sound[1] = rm->GetSounds("Resource/Sounds/SE_Death.wav");

	if (player_zanki > 0)
	{
		// 死ぬ音再生
		PlaySoundMem(destroy_sound[0], DX_PLAYTYPE_NORMAL);
		PlaySoundMem(destroy_sound[1], DX_PLAYTYPE_NORMAL);
	}

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

	// 残機が0ではないとき
	if (player_zanki > 0)
	{
		//SPACEキーでタイトル画面に遷移する
		if (input->GetKeyDown(KEY_INPUT_SPACE))
		{
			// 残機を減らす
			player_zanki--;
			return eSceneType::eInGame;
		}
	}
	else
	{
		PlaySoundMem(gameover_sound, DX_PLAYTYPE_NORMAL);
		// 残機が0になったらタイトルへ遷移
		player_zanki = 3;
		return eSceneType::eTitle;
	}

	//現在のシーン情報を取得
	return GetNowSceneType();
}

//描画処理
void ResultScene::Draw()
{
	DrawRotaGraph(D_WIN_MAX_X / 2 - ((D_OBJECT_SIZE * 2) * 1.5), D_WIN_MAX_Y / 2, 1.2, 0.0, mario_image, TRUE);
	SetFontSize(32);
	DrawFormatString(D_WIN_MAX_X / 2 - ((D_OBJECT_SIZE * 2) * 1), D_WIN_MAX_Y / 2 - (D_OBJECT_SIZE / 2), GetColor(255, 255, 255), " × %d", player_zanki, TRUE);
	DrawString(340,450, "SPACE TO START", GetColor(255, 255, 255), TRUE);
	SetFontSize(16);
}

//終了時処理
void ResultScene::Finalize()
{
	// インスタンスの削除
	InputManager::DeleteInstance();
}

//現在のシーン情報を取得
const eSceneType ResultScene::GetNowSceneType() const
{
	return eSceneType::eResult;
}