#include "InGameScene.h"
#include "DxLib.h"

#include "../../Utility/InputManager.h"
#include "../../Utility/ResourceManager.h"
#include "../../Objects/GameObjectManager.h"
#include "../../Application/Application.h"

#include "../../Objects/CharacterBase/Player/Player.h"
#include "../../Objects/CharacterBase/EnemyBase/Kuribo/Kuribo.h"
#include "../../Objects/CharacterBase/EnemyBase/Nokonoko/Nokonoko.h"
#include "../../Objects/BlockBase/Ground/Ground.h"

#include <fstream>
#include <iostream>

#define SCROLL_SPEED 300.0f
#define TOTAL_BLOCK_X 211
#define TOTAL_BLOCK_Y 30

//カメラ座標を求めてから生成と破棄をできればok

InGameScene::InGameScene() 
	: player(nullptr)
	, kuribo(nullptr)
	, nokonoko(nullptr)
	, fireboll(nullptr)
	, player_zanki(0)
	, back_ground_image(NULL)
	, screen_location(0)
	, screen_end(false)
	, is_scroll(false)
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
	//オブジェクト読込み
	LoadStageMapObject();

	//背景読込み
	ResourceManager* rm = Singleton<ResourceManager>::GetInstance();
	back_ground_image1 = rm->GetImages("Resource/Images/sora.png")[0];
	back_ground_image2 = rm->GetImages("Resource/Images/Block/floor.png")[0];
	back_ground_image3 = rm->GetImages("Resource/Images/sora_g.png")[0];

	// 背景画像の初期座標設定
	screen_location = D_OBJECT_SIZE;

	camera_location = (D_WIN_MAX_X / 2.0f, D_WIN_MAX_Y / 2.0f);
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

	// スクロール最大値を設定
	float max_screen = -((TOTAL_BLOCK_X * (D_OBJECT_SIZE * 2)) - (D_WIN_MAX_X + D_OBJECT_SIZE));
	
	// プレイヤーが移動状態だったら
	if (player->GetPlayerState() == ePlayerState::RUN)
	{
		// プレイヤーのx座標が480-boxsize以上になったら背景スクロールを開始
		if (player->GetLocation().x >= (D_WIN_MAX_X / 2) - (player->GetBoxSize().x * 2))
		{
			// スクロールスピード
			screen_location.x -= SCROLL_SPEED * delta_second;
			for (Ground* ground : grounds) 
			{
				ground->SetScroll(ground->GetLocation().x - (SCROLL_SPEED * delta_second));
			}
		}
	}

	// 地面のスクロールを止める
	// 座標はブロック数の半分で、そこからさらにウィンドウに表示できるブロック数を引き、値に変換する
	float scroll_end = -((56.0f / 2.0f) - 20.0f) * (D_OBJECT_SIZE * 2.0f);
	if (ground->GetLocation().x <= scroll_end)
	{
		ground->SetScroll(scroll_end);
	}

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
	// ステージ読込みで作成したオブジェクト情報の配列から描画する
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
		//case 'G':
		//	screen_location.y = D_OBJECT_SIZE + ((D_OBJECT_SIZE * 2) * object.spos_y);
		//	back_ground_image = back_ground_image2;
		//	break;
		default:
			continue;
		}

		// 背景ステージの描画
		// 縦のブロック数分繰り返す
		for (int j = 0; j < object.y_size; j++)
		{
			// 横のブロック数分繰り返す
			for (int n = 0; n < object.x_size; n++)
			{
				DrawRotaGraph(screen_location.x + ((D_OBJECT_SIZE * 2) * object.spos_x) + ((D_OBJECT_SIZE * 2) * n), screen_location.y + ((D_OBJECT_SIZE * 2) * j), 1.5, 0.0, back_ground_image, TRUE);
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

//ステージ読込み
void InGameScene::LoadStageMapCSV()
{
	// 読み込むファイル名
	std::string file_name = "Resource/Map/StageMap.csv";
	// 指定ファイルを読み込む
	std::ifstream ifs(file_name);

	// エラーチェック
	if (ifs.fail())
	{
		throw (file_name + "が開けません\n");
	}

	// ファイルから1行ずつ読み込む
	std::string line;
	// 生成するオブジェクト情報を生成
	MapObjectData data;
	while (std::getline(ifs, line))
	{
		// 読み込んだ文字と値を代入する
		sscanf_s(
			line.c_str(),
			"%c,%d,%d,%d,%d",
			&data.mode, (unsigned int)sizeof(data.mode),
			&data.x_size, &data.y_size,
			&data.spos_x, &data.spos_y
		);

		// 値を代入されたオブジェクト情報を配列に挿入
		map_object.push_back(data);
	}
}

//オブジェクト生成
void InGameScene::LoadStageMapObject()
{
	//インスタンスの取得
	GameObjectManager* obj_m = Singleton<GameObjectManager>::GetInstance();

#if 0

	// プレイヤーの生成
	Vector2D generate_location = Vector2D(200.0f, 600.0f);
	player = obj_m->CreateObject<Player>(generate_location);

	// エネミーの生成
	generate_location = Vector2D(800.0f, 600.0f);
	kuribo = obj_m->CreateObject<Kuribo>(generate_location);

	// エネミーの生成
	generate_location = Vector2D(700.0f, 600.0f - D_OBJECT_SIZE);
	nokonoko = obj_m->CreateObject<Nokonoko>(generate_location);

	// 地面の生成
	generate_location = Vector2D(300.0f + D_OBJECT_SIZE, 720.0f - (D_OBJECT_SIZE * 5));
	ground = obj_m->CreateObject<Ground>(generate_location);
#else

	// ステージ読込みで作成したオブジェクト情報の配列から描画する
	for (int i = 0; i < map_object.size(); i++)
	{
		// csvから読み込んだ情報を利用できるようにする
		const MapObjectData& object = map_object[i];

		// オブジェクトの生成座標
		Vector2D generate_location;

		// 最初の文字列を見て代入する値を変える
		switch (object.mode)
		{
		case 'P':
			// プレイヤーの生成
			generate_location = Vector2D(object.spos_x * (D_OBJECT_SIZE * 2), (object.spos_y * (D_OBJECT_SIZE * 2))) - D_OBJECT_SIZE;
			player = obj_m->CreateObject<Player>(generate_location);
			break;
		case 'K':
			// エネミーの生成
			generate_location = Vector2D(object.spos_x * (D_OBJECT_SIZE * 2), (object.spos_y * (D_OBJECT_SIZE * 2))) - D_OBJECT_SIZE;
			kuribo = obj_m->CreateObject<Kuribo>(generate_location);
			break;
		case 'G':
			// 地面を1つのオブジェクトとして生成する
			generate_location = Vector2D((object.x_size * D_OBJECT_SIZE) + (object.spos_x * (D_OBJECT_SIZE * 2)), (object.spos_y * (D_OBJECT_SIZE * 2)) + (D_OBJECT_SIZE * 2));
			ground = obj_m->CreateObject<Ground>(generate_location);
			// 地面の当たり判定の設定
			ground->SetGroundData(object.x_size, object.y_size);
			// 複数利用できるように配列で管理
			grounds.push_back(ground);
			break;
		default:
			continue;
		}
	}
#endif
}

// スクリーン座標に変換
Vector2D InGameScene::ChengeLocation(const Vector2D& pos)
{
	Vector2D screen_origin_position =
	{
		camera_location.x - D_WIN_MAX_X / 2.0f,
		camera_location.y - D_WIN_MAX_Y / 2.0f
	};
	Vector2D screen_position = Vector2D(pos.x - screen_origin_position.x, pos.y - screen_origin_position.y);
	return screen_location;
}

