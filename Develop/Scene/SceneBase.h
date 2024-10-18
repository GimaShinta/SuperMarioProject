#pragma once

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
	virtual void Draw() {}
	virtual void Finalize() {}

public:
	virtual const eSceneType GetNowSceneType()const = 0;
};