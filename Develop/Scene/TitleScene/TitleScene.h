#pragma once

#include "../SceneBase.h"

//タイトルシーンクラス
class TitleScene : public SceneBase
{
private:
	int back_ground_image;

public:
	TitleScene();
	~TitleScene();

public:
	//初期化処理
	void Initialize()override;

	/// <summary>
	/// 更新処理
	/// </summary>
	/// <param name="delta_second">1フレーム当たりの時間</param>
	/// <returns>現在のシーン情報</returns>
	eSceneType Update(float delta_second)override;

	//描画処理
	void Draw()override;

	//終了時処理
	void Finalize()override;

	// 現在のシーンタイプ情報を取得する
	const eSceneType GetNowSceneType() const override;
};

