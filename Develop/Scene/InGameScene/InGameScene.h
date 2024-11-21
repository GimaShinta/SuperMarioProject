#pragma once

#include "../SceneBase.h"
#include "../../Objects/GameObjectBase.h"

class InGameScene : public SceneBase
{
private:
	// オブジェクトの情報を格納する構造体
	struct MapObjectData 
	{
		char mode;
		int x_size;
		int y_size;
		int spos_x;
		int spos_y;
	};

private:
	class Player* player;
	class Kuribo* kuribo;
	class Nokonoko* nokonoko;
	class Fireboll* fireboll;

private:
	std::vector<MapObjectData> map_object;
	std::vector<int> back_ground_images;

private:
	int player_zanki;
	int back_ground_image;
	int back_ground_image1;
	int back_ground_image2;
	int back_ground_image3;
	Vector2D screen_location;
	Vector2D draw_location;
	bool screen_end;

public:
	InGameScene();
	~InGameScene();

public:
	//初期化処理
	void Initialize();

	/// <summary>
	/// 更新処理
	/// </summary>
	/// <param name="delta_second">1フレーム当たりの時間</param>
	/// <returns>現在のシーン情報</returns>
	eSceneType Update(float delta_second)override;

	//描画処理
	void Draw();

	//終了時処理
	void Finalize();

	// 現在のシーンタイプ情報を取得する
	const eSceneType GetNowSceneType() const override;

private:
	//ステージ読込み
	void LoadStageMapCSV();
	//オブジェクト読込み
	void LoadStageMapObject();
};

