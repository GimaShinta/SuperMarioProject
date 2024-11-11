#include "InGameScene.h"
#include "DxLib.h"

#include "../../Utility/InputManager.h"
#include "../../Objects/GameObjectManager.h"
#include "../../Utility/ResourceManager.h"

#include "../../Objects/CharacterBase/Player/Player.h"
#include "../../Objects/CharacterBase/EnemyBase/Kuribo/Kuribo.h"

InGameScene::InGameScene() 
	: player(nullptr)
	, kuribo(nullptr)
	, nokonoko(nullptr)
	, fireboll(nullptr)
	, player_zanki(0)
	, back_ground_image(NULL)
	, screen_location(0)
	, screen_end(false)
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
	ResourceManager* rm = Singleton<ResourceManager>::GetInstance();
	back_ground_image = rm->GetImages("Resource/Images/配置素材/NES---Super-Mario-Bros---World-1-1（修正版）.png")[0];

	//背景画像の初期座標設定
	screen_location = Vector2D(5064, 720);
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

	//プレイヤーが移動状態でx350以上になったら背景スクロールを開始
	Vector2D p_location = player->GetLocation();
	Vector2D p_size = player->GetBoxSize();
	//プレイヤーが移動状態だったら
	if (player->GetPlayerState() == ePlayerState::RUN)
	{
		//x350以上になったら背景スクロールを開始
		if (p_location.x + p_size.x >= 350)
		{
			screen_location.x -= 0.5;
		}
	}

	//背景画像が右端までいったら止める
	if (screen_location.x <= -4104)
	{
		screen_end = true;
		screen_location.x = -4104;
	}

	//背景画像が右端にいったかをプレイヤーに通知
	player->SetScreenEnd(screen_end);

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
	// 背景画像の描画
	DrawRotaGraph(screen_location.x, screen_location.y, 3.0, 0.0, back_ground_image, TRUE);

	DrawString(0, 0, "インゲーム画面です", GetColor(255, 255, 255), TRUE);
	DrawString(0, 60, "スペースキーでリザルト", GetColor(0, 255, 0), TRUE);
	DrawString(0, 90, "Zキーでタイトル", GetColor(0, 255, 0), TRUE);

	// 親クラスの描画処理を呼び出す
	__super::Draw();

}

//終了時処理
void InGameScene::Finalize()
{
	//オブジェクト管理クラスの情報を取得
	GameObjectManager* gom = Singleton<GameObjectManager>::GetInstance();
	//オブジェクト管理クラスの終了時処理を呼び出す
	gom->Finalize();
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
	GameObjectManager* obj_m = Singleton<GameObjectManager>::GetInstance();

	//プレイヤーの生成
	Vector2D generate_location = Vector2D(200.0f, 600.0f);
	player = obj_m->CreateObject<Player>(generate_location);

	//エネミーの生成
	generate_location = Vector2D(800.0f, 600.0f);
	kuribo = obj_m->CreateObject<Kuribo>(generate_location);
}

//オブジェクト読込み
void InGameScene::LoadStageMapObject()
{
}
