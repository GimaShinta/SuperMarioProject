#pragma once

#include "../Singleton.h"
#include "SceneBase.h"

//シーンマネージャークラス
class SceneManager : public Singleton<class T>
{
private:
	SceneBase* current_scene;

public:
	SceneManager();
	~SceneManager();

public:
	//インスタンスの削除
	static void DeleteInstance();

public:
	//初期化処理
	void Initialize();

	/// <summary>
	/// 更新処理
	/// </summary>
	/// <param name="delta_second">1フレーム当たりの時間</param>
	/// <returns></returns>
	bool Update(float delta_second);

	//描画処理
	void Draw();

	//終了時処理
	void Finalize();

public:
	//シーンの切り替え
	void ChangeScene(eSceneType scene_type);

private:
	//シーンの生成
	SceneBase* CreateScene(eSceneType scene_type);
};

