#pragma once

#include "../Singleton.h"
#include "SceneBase.h"

class SceneManager : public Singleton<class T>
{

public:
	SceneManager();
	~SceneManager();

private:
	SceneBase* current_scene;

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

