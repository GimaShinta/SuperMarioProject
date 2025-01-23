#pragma once

#include "../SceneBase.h"

// リザルトシーンクラス
class ResultScene : public SceneBase
{
private:
	// マリオ画像
	int mario_image;
	// プレイヤー残機
	int player_zanki;

public:
	ResultScene();
	~ResultScene();

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
};

