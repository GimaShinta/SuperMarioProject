#include "InGameScene.h"
#include "DxLib.h"

#include "../../Utility/InputManager.h"
#include "../../Utility/ResourceManager.h"
#include "../../Objects/GameObjectManager.h"
#include "../../Application/Application.h"

#include "../../Objects/CharacterBase/Player/Player.h"
#include "../../Objects/CharacterBase/EnemyBase/Kuribo/Kuribo.h"
#include "../../Objects/CharacterBase/EnemyBase/Nokonoko/Nokonoko.h"
#include "../../Objects/BlockBase/Ground/Ground.h"

#include <fstream>
#include <iostream>

#define SCROLL_SPEED 300.0f
#define TOTAL_BLOCK_X 211
#define TOTAL_BLOCK_Y 30

//�J�������W�����߂Ă��琶���Ɣj�����ł����ok

InGameScene::InGameScene() 
	: player(nullptr)
	, kuribo(nullptr)
	, nokonoko(nullptr)
	, fireboll(nullptr)
	, player_zanki(0)
	, back_ground_image(NULL)
	, screen_location(0)
	, screen_end(false)
	, is_scroll(false)
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
	//�I�u�W�F�N�g�Ǎ���
	LoadStageMapObject();

	//�w�i�Ǎ���
	ResourceManager* rm = Singleton<ResourceManager>::GetInstance();
	back_ground_image1 = rm->GetImages("Resource/Images/sora.png")[0];
	back_ground_image2 = rm->GetImages("Resource/Images/Block/floor.png")[0];
	back_ground_image3 = rm->GetImages("Resource/Images/sora_g.png")[0];

	// �w�i�摜�̏������W�ݒ�
	screen_location = D_OBJECT_SIZE;

	camera_location = (D_WIN_MAX_X / 2.0f, D_WIN_MAX_Y / 2.0f);
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

	// �X�N���[���ő�l��ݒ�
	float max_screen = -((TOTAL_BLOCK_X * (D_OBJECT_SIZE * 2)) - (D_WIN_MAX_X + D_OBJECT_SIZE));
	
	// �v���C���[���ړ���Ԃ�������
	if (player->GetPlayerState() == ePlayerState::RUN)
	{
		// �v���C���[��x���W��480-boxsize�ȏ�ɂȂ�����w�i�X�N���[�����J�n
		if (player->GetLocation().x >= (D_WIN_MAX_X / 2) - (player->GetBoxSize().x * 2))
		{
			// �X�N���[���X�s�[�h
			screen_location.x -= SCROLL_SPEED * delta_second;
			for (Ground* ground : grounds) 
			{
				ground->SetScroll(ground->GetLocation().x - (SCROLL_SPEED * delta_second));
			}
		}
	}

	// �n�ʂ̃X�N���[�����~�߂�
	// ���W�̓u���b�N���̔����ŁA�������炳��ɃE�B���h�E�ɕ\���ł���u���b�N���������A�l�ɕϊ�����
	float scroll_end = -((56.0f / 2.0f) - 20.0f) * (D_OBJECT_SIZE * 2.0f);
	if (ground->GetLocation().x <= scroll_end)
	{
		ground->SetScroll(scroll_end);
	}

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
	// �X�e�[�W�Ǎ��݂ō쐬�����I�u�W�F�N�g���̔z�񂩂�`�悷��
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
		//case 'G':
		//	screen_location.y = D_OBJECT_SIZE + ((D_OBJECT_SIZE * 2) * object.spos_y);
		//	back_ground_image = back_ground_image2;
		//	break;
		default:
			continue;
		}

		// �w�i�X�e�[�W�̕`��
		// �c�̃u���b�N�����J��Ԃ�
		for (int j = 0; j < object.y_size; j++)
		{
			// ���̃u���b�N�����J��Ԃ�
			for (int n = 0; n < object.x_size; n++)
			{
				DrawRotaGraph(screen_location.x + ((D_OBJECT_SIZE * 2) * object.spos_x) + ((D_OBJECT_SIZE * 2) * n), screen_location.y + ((D_OBJECT_SIZE * 2) * j), 1.5, 0.0, back_ground_image, TRUE);
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

//�X�e�[�W�Ǎ���
void InGameScene::LoadStageMapCSV()
{
	// �ǂݍ��ރt�@�C����
	std::string file_name = "Resource/Map/StageMap.csv";
	// �w��t�@�C����ǂݍ���
	std::ifstream ifs(file_name);

	// �G���[�`�F�b�N
	if (ifs.fail())
	{
		throw (file_name + "���J���܂���\n");
	}

	// �t�@�C������1�s���ǂݍ���
	std::string line;
	// ��������I�u�W�F�N�g���𐶐�
	MapObjectData data;
	while (std::getline(ifs, line))
	{
		// �ǂݍ��񂾕����ƒl��������
		sscanf_s(
			line.c_str(),
			"%c,%d,%d,%d,%d",
			&data.mode, (unsigned int)sizeof(data.mode),
			&data.x_size, &data.y_size,
			&data.spos_x, &data.spos_y
		);

		// �l�������ꂽ�I�u�W�F�N�g����z��ɑ}��
		map_object.push_back(data);
	}
}

//�I�u�W�F�N�g����
void InGameScene::LoadStageMapObject()
{
	//�C���X�^���X�̎擾
	GameObjectManager* obj_m = Singleton<GameObjectManager>::GetInstance();

#if 0

	// �v���C���[�̐���
	Vector2D generate_location = Vector2D(200.0f, 600.0f);
	player = obj_m->CreateObject<Player>(generate_location);

	// �G�l�~�[�̐���
	generate_location = Vector2D(800.0f, 600.0f);
	kuribo = obj_m->CreateObject<Kuribo>(generate_location);

	// �G�l�~�[�̐���
	generate_location = Vector2D(700.0f, 600.0f - D_OBJECT_SIZE);
	nokonoko = obj_m->CreateObject<Nokonoko>(generate_location);

	// �n�ʂ̐���
	generate_location = Vector2D(300.0f + D_OBJECT_SIZE, 720.0f - (D_OBJECT_SIZE * 5));
	ground = obj_m->CreateObject<Ground>(generate_location);
#else

	// �X�e�[�W�Ǎ��݂ō쐬�����I�u�W�F�N�g���̔z�񂩂�`�悷��
	for (int i = 0; i < map_object.size(); i++)
	{
		// csv����ǂݍ��񂾏��𗘗p�ł���悤�ɂ���
		const MapObjectData& object = map_object[i];

		// �I�u�W�F�N�g�̐������W
		Vector2D generate_location;

		// �ŏ��̕���������đ������l��ς���
		switch (object.mode)
		{
		case 'P':
			// �v���C���[�̐���
			generate_location = Vector2D(object.spos_x * (D_OBJECT_SIZE * 2), (object.spos_y * (D_OBJECT_SIZE * 2))) - D_OBJECT_SIZE;
			player = obj_m->CreateObject<Player>(generate_location);
			break;
		case 'K':
			// �G�l�~�[�̐���
			generate_location = Vector2D(object.spos_x * (D_OBJECT_SIZE * 2), (object.spos_y * (D_OBJECT_SIZE * 2))) - D_OBJECT_SIZE;
			kuribo = obj_m->CreateObject<Kuribo>(generate_location);
			break;
		case 'G':
			// �n�ʂ�1�̃I�u�W�F�N�g�Ƃ��Đ�������
			generate_location = Vector2D((object.x_size * D_OBJECT_SIZE) + (object.spos_x * (D_OBJECT_SIZE * 2)), (object.spos_y * (D_OBJECT_SIZE * 2)) + (D_OBJECT_SIZE * 2));
			ground = obj_m->CreateObject<Ground>(generate_location);
			// �n�ʂ̓����蔻��̐ݒ�
			ground->SetGroundData(object.x_size, object.y_size);
			// �������p�ł���悤�ɔz��ŊǗ�
			grounds.push_back(ground);
			break;
		default:
			continue;
		}
	}
#endif
}

// �X�N���[�����W�ɕϊ�
Vector2D InGameScene::ChengeLocation(const Vector2D& pos)
{
	Vector2D screen_origin_position =
	{
		camera_location.x - D_WIN_MAX_X / 2.0f,
		camera_location.y - D_WIN_MAX_Y / 2.0f
	};
	Vector2D screen_position = Vector2D(pos.x - screen_origin_position.x, pos.y - screen_origin_position.y);
	return screen_location;
}

