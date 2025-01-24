#include "InGameScene.h"
#include "DxLib.h"

// Utilityのインクルード
#include "../../Utility/InputManager.h"
#include "../../Utility/ResourceManager.h"
#include "../../Objects/GameObjectManager.h"
#include "../../Application/Application.h"

// オブジェクトのインクルード
#include "../../Objects/CharacterBase/Player/Player.h"
#include "../../Objects/CharacterBase/EnemyBase/Kuribo/Kuribo.h"
#include "../../Objects/CharacterBase/EnemyBase/Nokonoko/Nokonoko.h"
#include "../../Objects/BlockBase/Ground/Ground.h"
#include "../../Objects/BlockBase/Hatena/Hatena.h"
#include "../../Objects/BlockBase/Brick/Brick.h"
#include "../../Objects/BlockBase/Kai/Kai.h"
#include "../../Objects/BlockBase/BlockBase.h"
#include "../../Objects/BlockBase/Pole/Pole.h"
#include "../../Objects/CharacterBase/EnemyBase/EnemyBase.h"

#include <fstream>
#include <iostream>

#define SCROLL_MAX_SPEED 500.0f
#define TOTAL_BLOCK_X 211
#define TOTAL_BLOCK_Y 30

// カメラ座標を求めてから生成と破棄をできればok

InGameScene::InGameScene() 
	: player(nullptr)
	, kuribo(nullptr)
	, nokonoko(nullptr)
	, fireboll(nullptr)
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
	// ステージ読込み
	LoadStageMapCSV();
	// オブジェクト読込み
	LoadStageMapObject();
	// 画像の読込み
	LoadImages();

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

	// プレイヤーのx座標が480-boxsize以上になったら背景スクロールを開始
	if (player->GetLocation().x >= (D_WIN_MAX_X / 2))
	{
		// 右方向に速度がある時のみスクロールする
		if (player->velocity.x > 0)
		{
			// プレイヤーのスピードに合わせてスクロール
			Vector2D p_speed = player->GetVelocity();
			// 背景用スクロール
			screen_location.x -= p_speed.x * delta_second;
			// 複数のオブジェクト用スクロール
			for (BlockBase* block : blocks)
			{
				if (screen_end == false)
				{
					block->SetScroll(block->GetLocation().x - (p_speed.x * delta_second));
				}
			}
			for (EnemyBase* enemy : enemys)
			{
				enemy->SetScroll(enemy->GetLocation().x - (p_speed.x * delta_second));
			}
		}
	}

	// オブジェクトブロック数の半分で、そこからさらにウィンドウに表示できるブロック数を引き、値に変換する
	float scroll_end = -((56.0f / 2.0f) - 20.0f) * (D_OBJECT_SIZE * 2.0f);
	// 地面オブジェクトのスクロールを止める
	if (ground->GetLocation().x < scroll_end)
	{
		ground->SetScroll(scroll_end);
	}

	// スクロール最大値を設定
	float max_screen = -((TOTAL_BLOCK_X * (D_OBJECT_SIZE * 2)) - (D_WIN_MAX_X + D_OBJECT_SIZE));
	// 背景画像が右端までいったら画面内に収まるように止める
	if (screen_location.x <= max_screen)
	{
		screen_end = true;
		screen_location.x = max_screen;
	}

	// 背景画像が右端に着いたかをプレイヤーに通知
	player->SetScreenEnd(screen_end);

	// 速度の制限
	if (player->velocity.x >= SCROLL_MAX_SPEED)
	{
		player->velocity.x = SCROLL_MAX_SPEED;
	}
	else if (player->velocity.x <= -SCROLL_MAX_SPEED)
	{
		player->velocity.x = -SCROLL_MAX_SPEED;
	}

	if (player->GetPlayerState() == ePlayerState::DESTROY)
	{
		return eSceneType::eResult;
	}

	// マリオがゴールしたらタイトルに遷移
	if (player->GetGoal() == true)
	{
		return eSceneType::eTitle;
	}

	// 現在のシーン情報
	return GetNowSceneType();
}

// 描画処理
void InGameScene::Draw()
{
	// 背景画像の描画
	BackDraw();

	// 親クラスの描画処理を呼び出す
	__super::Draw();

}

// 終了時処理
void InGameScene::Finalize()
{
	//オブジェクト管理クラスの情報を取得
	GameObjectManager* gom = Singleton<GameObjectManager>::GetInstance();
	//オブジェクト管理クラスの終了時処理を呼び出す
	gom->Finalize();

	// インスタンスの削除
	ResourceManager::DeleteInstance();
	GameObjectManager::DeleteInstance();
	InputManager::DeleteInstance();
}

// 現在のシーン情報
const eSceneType InGameScene::GetNowSceneType() const
{
	return eSceneType::eInGame;
}

// ステージの読込み
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

// オブジェクトの生成
void InGameScene::LoadStageMapObject()
{
	//インスタンスの取得
	GameObjectManager* obj_m = Singleton<GameObjectManager>::GetInstance();

	// ステージ読込みで作成したオブジェクト情報の配列から描画する
	for (int i = 0; i < map_object.size(); i++)
	{
		// csvから読み込んだ情報を利用できるようにする
		const MapObjectData& object = map_object[i];

		// オブジェクトの生成座標
		Vector2D generate_location = Vector2D(object.spos_x * (D_OBJECT_SIZE * 2), (object.spos_y * (D_OBJECT_SIZE * 2))) - D_OBJECT_SIZE;

		// 最初の文字列を見て代入する値を変える
		switch (object.mode)
		{
		case 'P':
			// プレイヤーの生成
			player = obj_m->CreateObject<Player>(generate_location);
			break;
		case 'K':
			// エネミーの生成
			kuribo = obj_m->CreateObject<Kuribo>(generate_location);
			enemys.push_back(kuribo);
			break;
		case 'H':
			// ハテナブロックの生成
			hatena = obj_m->CreateObject<Hatena>(generate_location);
			// 複数利用できるように配列で管理
			blocks.push_back(hatena);
			break;
		case 'B':
			// 破壊ブロックの生成
			brick = obj_m->CreateObject<Brick>(generate_location);
			// 複数利用できるように配列で管理
			blocks.push_back(brick);
			break;
		//case 'I':
		//	// 破壊不可ブロックの生成
		//	kai = obj_m->CreateObject<Kai>(generate_location);
		//	// 複数利用できるように配列で管理
		//	blocks.push_back(kai);
		//	break;
		case 'M':
			// ポールトップの生成
			pole_t = obj_m->CreateObject<PoleTop>(generate_location);
			// 複数利用できるように配列で管理
			blocks.push_back(pole_t);
			break;
		case 'L':
			// ポールダウンの生成
			pole_d = obj_m->CreateObject<PoleDown>(generate_location);
			// 複数利用できるように配列で管理
			blocks.push_back(pole_d);
			break;
		case 'G':
			// 地面を1つのオブジェクトとして生成する
			generate_location = Vector2D((object.x_size * D_OBJECT_SIZE) + (object.spos_x * (D_OBJECT_SIZE * 2)), (object.spos_y * (D_OBJECT_SIZE * 2)));
			ground = obj_m->CreateObject<Ground>(generate_location);
			// 地面の当たり判定の設定
			ground->SetGroundData(object.x_size, object.y_size);
			// 複数利用できるように配列で管理
			blocks.push_back(ground);
			break;
		default:
			continue;
		}
	}
}

// 背景画像の読込み
void InGameScene::LoadImages()
{
	// 背景画像の読込み
	ResourceManager* rm = Singleton<ResourceManager>::GetInstance();
	back_ground_sora = rm->GetImages("Resource/Images/sora.png")[0];
	back_ground_block = rm->GetImages("Resource/Images/Block/floor.png")[0];
	back_ground_siro = rm->GetImages("Resource/Images/siro1.png")[0];
	back_ground_blocks = rm->GetImages("Resource/Images/Block/kai_block.png", 1, 1, 1, 32, 32)[0];
	// 山の画像の読込み
	back_ground_mountain[0] = rm->GetImages("Resource/Images/mountain_left.png")[0];
	back_ground_mountain[1] = rm->GetImages("Resource/Images/mountain_right.png")[0];
	back_ground_mountain[2] = rm->GetImages("Resource/Images/mountain_up.png")[0];
	back_ground_mountain[5] = rm->GetImages("Resource/Images/mountain_surface2.png")[0];
	back_ground_mountain[4] = rm->GetImages("Resource/Images/mountain_surface.png")[0];
	back_ground_mountain[3] = rm->GetImages("Resource/Images/mountain_surface1.png")[0];
	// 葉の画像の読込み
	back_ground_ha[0] = rm->GetImages("Resource/Images/ha0.png")[0];
	back_ground_ha[1] = rm->GetImages("Resource/Images/ha1.png")[0];
	back_ground_ha[2] = rm->GetImages("Resource/Images/ha2.png")[0];
	// 雲の画像の読込み
	back_ground_cloud[0] = rm->GetImages("Resource/Images/cloud1.png")[0];
	back_ground_cloud[1] = rm->GetImages("Resource/Images/cloud2.png")[0];
	back_ground_cloud[2] = rm->GetImages("Resource/Images/cloud3.png")[0];
	back_ground_cloud[3] = rm->GetImages("Resource/Images/cloud6.png")[0];
	back_ground_cloud[4] = rm->GetImages("Resource/Images/cloud5.png")[0];
	back_ground_cloud[5] = rm->GetImages("Resource/Images/cloud4.png")[0];
	//土管の画像の読込み
	back_ground_dokan[0] = rm->GetImages("Resource/Images/dokan_left_down.png")[0];
	back_ground_dokan[1] = rm->GetImages("Resource/Images/dokan_left_up.png")[0];
	back_ground_dokan[2] = rm->GetImages("Resource/Images/dokan_right_down.png")[0];
	back_ground_dokan[3] = rm->GetImages("Resource/Images/dokan_right_up.png")[0];
	// ポールの画像の読込み
	back_ground_pole[0] = rm->GetImages("Resource/Images/pole.png")[0];
	back_ground_pole[1] = rm->GetImages("Resource/Images/pole_down.png")[0];
	back_ground_pole[2] = rm->GetImages("Resource/Images/flag.png")[0];
}

// 背景画像の設定
void InGameScene::BackDraw()
{
	// ステージ読込みで作成したオブジェクト情報の配列から描画する
	for (int i = 0; i < map_object.size(); i++)
	{
		// csvから読み込んだ情報を利用できるようにする
		const MapObjectData& object = map_object[i];

		// 位置情報の再設定
		screen_location.y = (object.spos_y * (D_OBJECT_SIZE * 2)) - D_OBJECT_SIZE;

		// 最初の文字列を見て代入する値を変える
		switch (object.mode)
		{
		case 'S':
			back_ground_image = back_ground_sora;
			break;
		case '0':
			back_ground_image = back_ground_mountain[0];
			break;
		case '1':
			back_ground_image = back_ground_mountain[1];
			break;
		case '2':
			back_ground_image = back_ground_mountain[2];
			break;
		case '3':
			back_ground_image = back_ground_mountain[3];
			break;
		case '4':
			back_ground_image = back_ground_mountain[4];
			break;
		case '5':
			back_ground_image = back_ground_mountain[5];
			break;
		case '6':
			back_ground_image = back_ground_ha[0];
			break;
		case '7':
			back_ground_image = back_ground_ha[1];
			break;
		case '8':
			back_ground_image = back_ground_ha[2];
			break;
		case 'a':
			back_ground_image = back_ground_cloud[0];
			break;
		case 'b':
			back_ground_image = back_ground_cloud[1];
			break;
		case 'c':
			back_ground_image = back_ground_cloud[2];
			break;
		case 'd':
			back_ground_image = back_ground_cloud[3];
			break;
		case 'e':
			back_ground_image = back_ground_cloud[4];
			break;
		case 'f':
			back_ground_image = back_ground_cloud[5];
			break;
		//case 'I':
		//	back_ground_image = back_ground_blocks;
		//	break;
		case 'G':
			back_ground_image = back_ground_block;
			break;
		case 'D':
			back_ground_image = back_ground_dokan[0];
			break;
		case 'E':
			back_ground_image = back_ground_dokan[1];
			break;
		case 'F':
			back_ground_image = back_ground_dokan[2];
			break;
		case 'J':
			back_ground_image = back_ground_dokan[3];
			break;
		case 's':
			back_ground_image = back_ground_siro;
			break;
		case 'j':
			back_ground_image = back_ground_pole[2];
			break;
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