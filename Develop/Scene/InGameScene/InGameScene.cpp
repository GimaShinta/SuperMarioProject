#include "InGameScene.h"
#include "DxLib.h"

#include "../../Utility/InputManager.h"
#include "../../Utility/ResourceManager.h"
#include "../../Objects/GameObjectManager.h"
#include "../../Application/Application.h"

#include "../../Objects/CharacterBase/Player/Player.h"
#include "../../Objects/CharacterBase/EnemyBase/Kuribo/Kuribo.h"

#include <fstream>
#include <iostream>

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
	//�w�i�X�e�[�W�Ǎ���
	LoadStageMapCSV();
	//�I�u�W�F�N�g�Ǎ���
	LoadStageMapObject();

	//�w�i�Ǎ���
	ResourceManager* rm = Singleton<ResourceManager>::GetInstance();
	back_ground_image1 = rm->GetImages("Resource/Images/sora.png")[0];
	back_ground_image2 = rm->GetImages("Resource/Images/Block/floor.png")[0];
	back_ground_image3 = rm->GetImages("Resource/Images/sora_g.png")[0];

	// �w�i�摜�̏������W�ݒ�
	screen_location = D_OBJECT_SIZE;

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
	

	// �v���C���[���ړ���Ԃ�������
	if (player->GetPlayerState() == ePlayerState::RUN)
	{
		// �v���C���[��x���W��480-boxsize�ȏ�ɂȂ�����w�i�X�N���[�����J�n
		if (player->GetLocation().x >= 480.0f - (player->GetBoxSize().x * 2))
		{
			// �X�N���[���X�s�[�h
			screen_location.x -= 0.3f;
		}
	}

	// �X�N���[���ő�l��ݒ�
	// 211�͉��̃u���b�N��
	float max_screen = -((211 * (D_OBJECT_SIZE * 2)) - (D_WIN_MAX_X + D_OBJECT_SIZE));

	// �w�i�摜���E�[�܂ł�������~�߂�
	if (screen_location.x <= max_screen)
	{
		screen_end = true;
		screen_location.x = max_screen;
	}

	//�w�i�摜���E�[�ɒ����������v���C���[�ɒʒm
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
	// csv����ǂݍ��񂾉摜���̔z������Ƃɕ`�悷��
	for (int i = 0; i < map_object.size(); i++)
	{
		// csv����ǂݍ��񂾏��𗘗p�ł���悤�ɂ���
		const MapObjectData& object = map_object[i];
		// �ŏ��̕���������đ������l��ς���
		switch (object.mode)
		{
		case 'S':
			screen_location.y = D_OBJECT_SIZE;
			back_ground_image = back_ground_image1;
			break;
		case 'G':
			screen_location.y = D_OBJECT_SIZE + ((D_OBJECT_SIZE * 2) * object.spos_y);
			back_ground_image = back_ground_image2;
			break;
		default:
			continue;
		}

		// �c�̃u���b�N�����J��Ԃ�
		for (int j = 0; j < object.y_size; j++)
		{
			// ���̃u���b�N�����J��Ԃ�
			for (int n = 0; n < object.x_size; n++)
			{
				DrawRotaGraph(screen_location.x + ((D_OBJECT_SIZE * 2) * n), screen_location.y + ((D_OBJECT_SIZE * 2) * j), 1.5, 0.0, back_ground_image, TRUE);
			}
		}
	}

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

//�X�e�[�W�w�i�Ǎ���
void InGameScene::LoadStageMapCSV()
{
	// �ǂݍ��ރt�@�C����
	std::string file_name = "Resource/Map/Map.csv";
	// �w��t�@�C����ǂݍ���
	std::ifstream ifs(file_name);

	// �G���[�`�F�b�N
	if (ifs.fail())
	{
		throw (file_name + "���J���܂���\n");
	}

	// �t�@�C������1�s���ǂݍ���
	std::string line;
	// �ǂݍ��񂾃f�[�^��mapObjects�Ɋi�[
	MapObjectData data;
	while (std::getline(ifs, line))
	{
		sscanf_s(
			line.c_str(),
			"%c,%d,%d,%d,%d",
			&data.mode, (unsigned int)sizeof(data.mode),
			&data.x_size, &data.y_size,
			&data.spos_x, &data.spos_y
		);

		map_object.push_back(data);
	}
}

//�I�u�W�F�N�g�Ǎ���
void InGameScene::LoadStageMapObject()
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

