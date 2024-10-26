#include "InGameScene.h"
#include "DxLib.h"

#include "../../Utility/InputManager.h"
#include "../../Objects/GameObjectManager.h"

#include "../../Objects/CharacterBase/Player/Player.h"
#include "../../Objects/CharacterBase/EnemyBase/Kuribo/Kuribo.h"

InGameScene::InGameScene()
{
}

InGameScene::~InGameScene()
{
}

//����������
void InGameScene::Initialize()
{
	//�X�e�[�W�Ǎ���
	LoadStageMapCSV();
}

/// <summary>
/// �X�V����
/// </summary>
/// <param name="delta_second">1�t���[��������̎���</param>
/// <returns>���݂̃V�[�����</returns>
eSceneType InGameScene::Update(float delta_second)
{
	// ���N���X�̃|�C���^�i���̂��A�h���X�̐�ŕۗL�j
	GameObjectManager* obj_manager = Singleton<GameObjectManager>::GetInstance();
	obj_manager->Update(delta_second);

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

	//���݂̃V�[�����
	return GetNowSceneType();
}

//�`�揈��
void InGameScene::Draw()
{
	DrawString(0, 0, "�C���Q�[����ʂł�", GetColor(255, 255, 255), TRUE);
	DrawString(0, 60, "�X�y�[�X�L�[�Ń��U���g", GetColor(0, 255, 0), TRUE);
	DrawString(0, 90, "Z�L�[�Ń^�C�g��", GetColor(0, 255, 0), TRUE);

	// �e�N���X�̕`�揈�����Ăяo��
	__super::Draw();

}

//�I��������
void InGameScene::Finalize()
{
}

//���݂̃V�[�����
const eSceneType InGameScene::GetNowSceneType() const
{
	return eSceneType::eInGame;
}

//�X�e�[�W�Ǎ���
void InGameScene::LoadStageMapCSV()
{
	//�C���X�^���X�̎擾
	GameObjectManager* obj_manager = Singleton<GameObjectManager>::GetInstance();

	//�v���C���[�̐���
	Vector2D generate_location = Vector2D(200.0f, 600.0f);
	player = obj_manager->CreateObject<Player>(generate_location);

	//�G�l�~�[�̐���
	generate_location = Vector2D(800.0f, 600.0f);
	kuribo = obj_manager->CreateObject<Kuribo>(generate_location);
}

//�I�u�W�F�N�g�Ǎ���
void InGameScene::LoadStageMapObject()
{
}
