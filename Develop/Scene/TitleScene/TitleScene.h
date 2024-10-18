#pragma once

#include "../SceneBase.h"

class TitleScene : public SceneBase
{
private:
	int back_ground;

public:
	TitleScene();
	~TitleScene();

public:
	void Initialize()override;
	eSceneType Update(float delta_second)override;
	void Draw()override;
	void Finalize()override;

	// 現在のシーンタイプ情報を取得する
	const eSceneType GetNowSceneType() const override;
};

