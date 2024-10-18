#include "ResultScene.h"

ResultScene::ResultScene()
{
}

ResultScene::~ResultScene()
{
}

void ResultScene::Initialize()
{
}

eSceneType ResultScene::Update(const float& delta_second)
{
	return GetNowSceneType();
}

void ResultScene::Draw()
{
}

void ResultScene::Finalize()
{
}

const eSceneType ResultScene::GetNowSceneType() const
{
	return eSceneType::eResult;
}
