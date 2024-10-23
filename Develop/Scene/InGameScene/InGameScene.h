#pragma once

#include "../SceneBase.h"
#include "../../Objects/GameObjectBase.h"

class InGameScene : public SceneBase
{
private:
	class Player* player;
	class Kuribo* kuribo;
	class Nokonoko* nokonoko;
	class Fireboll* fireboll;

private:
	int player_zanki;

public:
	InGameScene();
	~InGameScene();

public:
	void Initialize();
	eSceneType Update(float delta_second)override;
	void Draw();
	void Finalize();

	// 現在のシーンタイプ情報を取得する
	const eSceneType GetNowSceneType() const override;

public:
	void CheckCollision(GameObjectBase* target, GameObjectBase* partner);

private:
	void LoadStageMapCSV();
	void LoadStageMapObject();
};

