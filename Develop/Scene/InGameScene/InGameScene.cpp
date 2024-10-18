#include "InGameScene.h"

InGameScene::InGameScene()
{
}

InGameScene::~InGameScene()
{
}

void InGameScene::Initialize()
{
}

eSceneType InGameScene::Update(const float& delta_second)
{
	return GetNowSceneType();
}

void InGameScene::Draw()
{
}

void InGameScene::Finalize()
{
}

const eSceneType InGameScene::GetNowSceneType() const
{
	return eSceneType::eInGame;
}

void InGameScene::CheckCollision(GameObjectBase* target, GameObjectBase* partner)
{
}

void InGameScene::LoadStageMapCSV()
{
}

void InGameScene::LoadStageMapObject()
{
}
