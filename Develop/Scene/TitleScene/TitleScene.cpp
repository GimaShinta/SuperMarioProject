#include "TitleScene.h"
#include "DxLib.h"

TitleScene::TitleScene():back_ground(NULL)
{
}

TitleScene::~TitleScene()
{
}

void TitleScene::Initialize()
{
}

eSceneType TitleScene::Update(float delta_second)
{
	// ÉVÅ[ÉìèÓïÒ
	return GetNowSceneType();
}

void TitleScene::Draw()
{
}

void TitleScene::Finalize()
{
}

const eSceneType TitleScene::GetNowSceneType() const
{
	return eSceneType::eTitle;
}
