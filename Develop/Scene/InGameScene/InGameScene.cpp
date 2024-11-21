#include "InGameScene.h"
#include "DxLib.h"

#include "../../Utility/InputManager.h"
#include "../../Utility/ResourceManager.h"
#include "../../Objects/GameObjectManager.h"
#include "../../Application/Application.h"

#include "../../Objects/CharacterBase/Player/Player.h"
#include "../../Objects/CharacterBase/EnemyBase/Kuribo/Kuribo.h"

#include <fstream>
#include <iostream>

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
	//背景ステージ読込み
	LoadStageMapCSV();
	//オブジェクト読込み
	LoadStageMapObject();

	//背景読込み
	ResourceManager* rm = Singleton<ResourceManager>::GetInstance();
	back_ground_image1 = rm->GetImages("Resource/Images/sora.png")[0];
	back_ground_image2 = rm->GetImages("Resource/Images/Block/floor.png")[0];
	back_ground_image3 = rm->GetImages("Resource/Images/sora_g.png")[0];

	// 背景画像の初期座標設定
	screen_location = D_OBJECT_SIZE;

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
	

	// プレイヤーが移動状態だったら
	if (player->GetPlayerState() == ePlayerState::RUN)
	{
		// プレイヤーのx座標が480-boxsize以上になったら背景スクロールを開始
		if (player->GetLocation().x >= 480.0f - (player->GetBoxSize().x * 2))
		{
			// スクロールスピード
			screen_location.x -= 0.3f;
		}
	}

	// スクロール最大値を設定
	// 211は横のブロック数
	float max_screen = -((211 * (D_OBJECT_SIZE * 2)) - (D_WIN_MAX_X + D_OBJECT_SIZE));

	// 背景画像が右端までいったら止める
	if (screen_location.x <= max_screen)
	{
		screen_end = true;
		screen_location.x = max_screen;
	}

	//背景画像が右端に着いたかをプレイヤーに通知
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
	// csvから読み込んだ画像情報の配列をもとに描画する
	for (int i = 0; i < map_object.size(); i++)
	{
		// csvから読み込んだ情報を利用できるようにする
		const MapObjectData& object = map_object[i];
		// 最初の文字列を見て代入する値を変える
		switch (object.mode)
		{
		case 'S':
			screen_location.y = D_OBJECT_SIZE;
			back_ground_image = back_ground_image1;
			break;
		case 'G':
			screen_location.y = D_OBJECT_SIZE + ((D_OBJECT_SIZE * 2) * object.spos_y);
			back_ground_image = back_ground_image2;
			break;
		default:
			continue;
		}

		// 縦のブロック数分繰り返す
		for (int j = 0; j < object.y_size; j++)
		{
			// 横のブロック数分繰り返す
			for (int n = 0; n < object.x_size; n++)
			{
				DrawRotaGraph(screen_location.x + ((D_OBJECT_SIZE * 2) * n), screen_location.y + ((D_OBJECT_SIZE * 2) * j), 1.5, 0.0, back_ground_image, TRUE);
			}
		}
	}

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

//ステージ背景読込み
void InGameScene::LoadStageMapCSV()
{
	// 読み込むファイル名
	std::string file_name = "Resource/Map/Map.csv";
	// 指定ファイルを読み込む
	std::ifstream ifs(file_name);

	// エラーチェック
	if (ifs.fail())
	{
		throw (file_name + "が開けません\n");
	}

	// ファイルから1行ずつ読み込む
	std::string line;
	// 読み込んだデータをmapObjectsに格納
	MapObjectData data;
	while (std::getline(ifs, line))
	{
		sscanf_s(
			line.c_str(),
			"%c,%d,%d,%d,%d",
			&data.mode, (unsigned int)sizeof(data.mode),
			&data.x_size, &data.y_size,
			&data.spos_x, &data.spos_y
		);

		map_object.push_back(data);
	}
}

//オブジェクト読込み
void InGameScene::LoadStageMapObject()
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

