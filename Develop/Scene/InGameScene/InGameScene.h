#pragma once

#include "../SceneBase.h"
#include "../../Objects/GameObjectBase.h"

// インゲームクラス
class InGameScene : public SceneBase
{
private:
	// オブジェクト情報を格納する構造体
	struct MapObjectData 
	{
		char mode;
		int x_size;
		int y_size;
		int spos_x;
		int spos_y;
	};

private:
	// クラスポインタ変数
	class Player* player;
	class Kuribo* kuribo;
	class Nokonoko* nokonoko;
	class Fireboll* fireboll;
	class Ground* ground;
	class Hatena* hatena;
	class Brick* brick;
	class Kai* kai;
	class BlockBase* block;
	class EnemyBase* enemy;
	class PoleTop* pole_t;
	class PoleDown* pole_d;

private:
	// オブジェクト配列
	std::vector<BlockBase*> blocks;
	std::vector<EnemyBase*> enemys;
	std::vector<MapObjectData> map_object;

private:
	Vector2D screen_location;
	Vector2D draw_location;
	Vector2D camera_location;
	bool screen_end;
	bool is_scroll;

private:
	// 背景画像
	std::vector<int> back_ground_images;

private:
	// 画像用変数
	int back_ground_image;
	int back_ground_sora;
	int back_ground_block;
	int back_ground_blocks;
	int back_ground_mountain[6];
	int back_ground_ha[3];
	int back_ground_cloud[6];
	int back_ground_dokan[4];
	int back_ground_siro;
	int back_ground_pole[3];

public:
	InGameScene();
	~InGameScene();

public:
	// 初期化処理
	void Initialize();

	/// <summary>
	/// 更新処理
	/// </summary>
	/// <param name="delta_second">1フレーム当たりの時間</param>
	/// <returns>現在のシーン情報</returns>
	eSceneType Update(float delta_second)override;

	// 描画処理
	void Draw();

	// 終了時処理
	void Finalize();

	// 現在のシーンタイプ情報を取得する
	const eSceneType GetNowSceneType() const override;

private:
	// ステージ読込み
	void LoadStageMapCSV();
	// オブジェクト読込み
	void LoadStageMapObject();
	// 画像の読込み
	void LoadImages();
	// 背景画像の描画
	void BackDraw();

private:
	Vector2D ChengeLocation(const Vector2D& pos);
};

