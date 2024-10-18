#pragma once

#include "../SceneBase.h"

class ResultScene : public SceneBase
{
private:
	class Player* player_zanki;

private:
	int back_ground;
	int player_zanki;

public:
	ResultScene();
	~ResultScene();

public:
	void Initialize();
	eSceneType Update(const float& delta_second);
	void Draw();
	void Finalize();

	// 現在のシーンタイプ情報を取得する
	const eSceneType GetNowSceneType() const override;
};

