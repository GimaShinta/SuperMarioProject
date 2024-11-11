#include "InGameScene.h"
#include "DxLib.h"

#include "../../Utility/InputManager.h"
#include "../../Objects/GameObjectManager.h"
#include "../../Utility/ResourceManager.h"

#include "../../Objects/CharacterBase/Player/Player.h"
#include "../../Objects/CharacterBase/EnemyBase/Kuribo/Kuribo.h"

InGameScene::InGameScene() 
	: player(nullptr)
	, kuribo(nullptr)
	, nokonoko(nullptr)
	, fireboll(nullptr)
	, player_zanki(0)
	, back_ground_image(NULL)
	, screen_location(0)
	, screen_end(false)
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
	ResourceManager* rm = Singleton<ResourceManager>::GetInstance();
	back_ground_image = rm->GetImages("Resource/Images/�z�u�f��/NES---Super-Mario-Bros---World-1-1�i�C���Łj.png")[0];

	//�w�i�摜�̏������W�ݒ�
	screen_location = Vector2D(5064, 720);
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

	//�v���C���[���ړ���Ԃ�x350�ȏ�ɂȂ�����w�i�X�N���[�����J�n
	Vector2D p_location = player->GetLocation();
	Vector2D p_size = player->GetBoxSize();
	//�v���C���[���ړ���Ԃ�������
	if (player->GetPlayerState() == ePlayerState::RUN)
	{
		//x350�ȏ�ɂȂ�����w�i�X�N���[�����J�n
		if (p_location.x + p_size.x >= 350)
		{
			screen_location.x -= 0.5;
		}
	}

	//�w�i�摜���E�[�܂ł�������~�߂�
	if (screen_location.x <= -4104)
	{
		screen_end = true;
		screen_location.x = -4104;
	}

	//�w�i�摜���E�[�ɂ����������v���C���[�ɒʒm
	player->SetScreenEnd(screen_end);

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
	// �w�i�摜�̕`��
	DrawRotaGraph(screen_location.x, screen_location.y, 3.0, 0.0, back_ground_image, TRUE);

	DrawString(0, 0, "�C���Q�[����ʂł�", GetColor(255, 255, 255), TRUE);
	DrawString(0, 60, "�X�y�[�X�L�[�Ń��U���g", GetColor(0, 255, 0), TRUE);
	DrawString(0, 90, "Z�L�[�Ń^�C�g��", GetColor(0, 255, 0), TRUE);

	// �e�N���X�̕`�揈�����Ăяo��
	__super::Draw();

}

//�I��������
void InGameScene::Finalize()
{
	//�I�u�W�F�N�g�Ǘ��N���X�̏����擾
	GameObjectManager* gom = Singleton<GameObjectManager>::GetInstance();
	//�I�u�W�F�N�g�Ǘ��N���X�̏I�����������Ăяo��
	gom->Finalize();
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
	GameObjectManager* obj_m = Singleton<GameObjectManager>::GetInstance();

	//�v���C���[�̐���
	Vector2D generate_location = Vector2D(200.0f, 600.0f);
	player = obj_m->CreateObject<Player>(generate_location);

	//�G�l�~�[�̐���
	generate_location = Vector2D(800.0f, 600.0f);
	kuribo = obj_m->CreateObject<Kuribo>(generate_location);
}

//�I�u�W�F�N�g�Ǎ���
void InGameScene::LoadStageMapObject()
{
}
