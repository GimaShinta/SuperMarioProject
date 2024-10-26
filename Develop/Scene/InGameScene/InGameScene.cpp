#include "InGameScene.h"
#include "DxLib.h"

#include "../../Utility/InputManager.h"
#include "../../Objects/GameObjectManager.h"

#include "../../Objects/CharacterBase/Player/Player.h"
#include "../../Objects/CharacterBase/EnemyBase/Kuribo/Kuribo.h"

InGameScene::InGameScene()
{
}

InGameScene::~InGameScene()
{
}

//初期化処理
void InGameScene::Initialize()
{
	//ステージ読込み
	LoadStageMapCSV();
}

/// <summary>
/// 更新処理
/// </summary>
/// <param name="delta_second">1フレーム当たりの時間</param>
/// <returns>現在のシーン情報</returns>
eSceneType InGameScene::Update(float delta_second)
{
	// 自クラスのポインタ（実体をアドレスの先で保有）
	GameObjectManager* obj_manager = Singleton<GameObjectManager>::GetInstance();
	obj_manager->Update(delta_second);

	//入力機能の取得
	InputManager* input = Singleton<InputManager>::GetInstance();

	//SPACEキーでインゲーム画面に遷移する
	if (input->GetKeyDown(KEY_INPUT_SPACE))
	{
		return eSceneType::eResult;
	}
	//Zキーでタイトルへ戻る
	if (input->GetKeyDown(KEY_INPUT_Z))
	{
		return eSceneType::eTitle;
	}

	//現在のシーン情報
	return GetNowSceneType();
}

//描画処理
void InGameScene::Draw()
{
	DrawString(0, 0, "インゲーム画面です", GetColor(255, 255, 255), TRUE);
	DrawString(0, 60, "スペースキーでリザルト", GetColor(0, 255, 0), TRUE);
	DrawString(0, 90, "Zキーでタイトル", GetColor(0, 255, 0), TRUE);

	// 親クラスの描画処理を呼び出す
	__super::Draw();

}

//終了時処理
void InGameScene::Finalize()
{
}

//現在のシーン情報
const eSceneType InGameScene::GetNowSceneType() const
{
	return eSceneType::eInGame;
}

//ステージ読込み
void InGameScene::LoadStageMapCSV()
{
	//インスタンスの取得
	GameObjectManager* obj_manager = Singleton<GameObjectManager>::GetInstance();

	//プレイヤーの生成
	Vector2D generate_location = Vector2D(200.0f, 600.0f);
	player = obj_manager->CreateObject<Player>(generate_location);

	//エネミーの生成
	generate_location = Vector2D(800.0f, 600.0f);
	kuribo = obj_manager->CreateObject<Kuribo>(generate_location);
}

//オブジェクト読込み
void InGameScene::LoadStageMapObject()
{
}
