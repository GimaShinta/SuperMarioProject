#include "InGameScene.h"
#include "DxLib.h"

#include "../../Utility/InputManager.h"
#include "../../Objects/GameObjectManager.h"

#include "../../Objects/CharacterBase/Player/Player.h"

InGameScene::InGameScene()
{
}

InGameScene::~InGameScene()
{
}

void InGameScene::Initialize()
{
	LoadStageMapCSV();
}

eSceneType InGameScene::Update(float delta_second)
{
	GameObjectManager* obj_manager = Singleton<GameObjectManager>::GetInstance();
	obj_manager->Update(0);

	//���͋@�\�̎擾
	InputManager* input = Singleton<InputManager>::GetInstance();

	//SPACE�L�[�ŃC���Q�[����ʂɑJ�ڂ���
	if (input->GetKeyDown(KEY_INPUT_SPACE))
	{
		return eSceneType::eResult;
	}
	//Z�L�[�Ń^�C�g���֖߂�
	if (input->GetKeyDown(KEY_INPUT_Z))
	{
		return eSceneType::eTitle;
	}

	return GetNowSceneType();
}

void InGameScene::Draw()
{
	DrawString(0, 0, "�C���Q�[����ʂł�", GetColor(255, 255, 255), TRUE);
	DrawString(0, 60, "�X�y�[�X�L�[�Ń��U���g", GetColor(0, 255, 0), TRUE);
	DrawString(0, 90, "Z�L�[�Ń^�C�g��", GetColor(0, 255, 0), TRUE);

	// �e�N���X�̕`�揈�����Ăяo��
	__super::Draw();

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
	GameObjectManager* obj_manager = Singleton<GameObjectManager>::GetInstance();
	Vector2D generate_location = (640.0f, 600.0f);
	player = obj_manager->CreateObject<Player>(generate_location);
}

void InGameScene::LoadStageMapObject()
{
}
