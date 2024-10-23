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
	static void DeleteInstance();

public:
	void Initialize();
	bool Update(float delta_second);
	void Draw();
	void Finalize();

public:
	void ChangeScene(eSceneType scene_type);

private:
	SceneBase* CreateScene(eSceneType scene_type);
};

