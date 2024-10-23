#pragma once

#include "../Objects/GameObjectManager.h"

enum class eSceneType
{
	eTitle,
	eInGame,
	eResult,
	eXit
};

class SceneBase
{
public:
	virtual void Initialize() {}
	virtual eSceneType Update(float delta_second) 
	{
		return GetNowSceneType();
	}
	virtual void Draw()
	{
		GameObjectManager* obj_manager = Singleton<GameObjectManager>::GetInstance();
		obj_manager->Draw();
	}
	virtual void Finalize() {}

public:
	virtual const eSceneType GetNowSceneType()const = 0;
};