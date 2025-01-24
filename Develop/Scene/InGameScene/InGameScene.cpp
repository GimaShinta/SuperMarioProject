#include "InGameScene.h"
#include "DxLib.h"

// Utility�̃C���N���[�h
#include "../../Utility/InputManager.h"
#include "../../Utility/ResourceManager.h"
#include "../../Objects/GameObjectManager.h"
#include "../../Application/Application.h"

// �I�u�W�F�N�g�̃C���N���[�h
#include "../../Objects/CharacterBase/Player/Player.h"
#include "../../Objects/CharacterBase/EnemyBase/Kuribo/Kuribo.h"
#include "../../Objects/CharacterBase/EnemyBase/Nokonoko/Nokonoko.h"
#include "../../Objects/BlockBase/Ground/Ground.h"
#include "../../Objects/BlockBase/Hatena/Hatena.h"
#include "../../Objects/BlockBase/Brick/Brick.h"
#include "../../Objects/BlockBase/Kai/Kai.h"
#include "../../Objects/BlockBase/BlockBase.h"
#include "../../Objects/BlockBase/Pole/Pole.h"
#include "../../Objects/CharacterBase/EnemyBase/EnemyBase.h"

#include <fstream>
#include <iostream>

#define SCROLL_MAX_SPEED 500.0f
#define TOTAL_BLOCK_X 211
#define TOTAL_BLOCK_Y 30

// �J�������W�����߂Ă��琶���Ɣj�����ł����ok

InGameScene::InGameScene() 
	: player(nullptr)
	, kuribo(nullptr)
	, nokonoko(nullptr)
	, fireboll(nullptr)
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
	// �X�e�[�W�Ǎ���
	LoadStageMapCSV();
	// �I�u�W�F�N�g�Ǎ���
	LoadStageMapObject();
	// �摜�̓Ǎ���
	LoadImages();

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

	// �v���C���[��x���W��480-boxsize�ȏ�ɂȂ�����w�i�X�N���[�����J�n
	if (player->GetLocation().x >= (D_WIN_MAX_X / 2))
	{
		// �E�����ɑ��x�����鎞�̂݃X�N���[������
		if (player->velocity.x > 0)
		{
			// �v���C���[�̃X�s�[�h�ɍ��킹�ăX�N���[��
			Vector2D p_speed = player->GetVelocity();
			// �w�i�p�X�N���[��
			screen_location.x -= p_speed.x * delta_second;
			// �����̃I�u�W�F�N�g�p�X�N���[��
			for (BlockBase* block : blocks)
			{
				if (screen_end == false)
				{
					block->SetScroll(block->GetLocation().x - (p_speed.x * delta_second));
				}
			}
			for (EnemyBase* enemy : enemys)
			{
				enemy->SetScroll(enemy->GetLocation().x - (p_speed.x * delta_second));
			}
		}
	}

	// �I�u�W�F�N�g�u���b�N���̔����ŁA�������炳��ɃE�B���h�E�ɕ\���ł���u���b�N���������A�l�ɕϊ�����
	float scroll_end = -((56.0f / 2.0f) - 20.0f) * (D_OBJECT_SIZE * 2.0f);
	// �n�ʃI�u�W�F�N�g�̃X�N���[�����~�߂�
	if (ground->GetLocation().x < scroll_end)
	{
		ground->SetScroll(scroll_end);
	}

	// �X�N���[���ő�l��ݒ�
	float max_screen = -((TOTAL_BLOCK_X * (D_OBJECT_SIZE * 2)) - (D_WIN_MAX_X + D_OBJECT_SIZE));
	// �w�i�摜���E�[�܂ł��������ʓ��Ɏ��܂�悤�Ɏ~�߂�
	if (screen_location.x <= max_screen)
	{
		screen_end = true;
		screen_location.x = max_screen;
	}

	// �w�i�摜���E�[�ɒ����������v���C���[�ɒʒm
	player->SetScreenEnd(screen_end);

	// ���x�̐���
	if (player->velocity.x >= SCROLL_MAX_SPEED)
	{
		player->velocity.x = SCROLL_MAX_SPEED;
	}
	else if (player->velocity.x <= -SCROLL_MAX_SPEED)
	{
		player->velocity.x = -SCROLL_MAX_SPEED;
	}

	if (player->GetPlayerState() == ePlayerState::DESTROY)
	{
		return eSceneType::eResult;
	}

	// �}���I���S�[��������^�C�g���ɑJ��
	if (player->GetGoal() == true)
	{
		return eSceneType::eTitle;
	}

	// ���݂̃V�[�����
	return GetNowSceneType();
}

// �`�揈��
void InGameScene::Draw()
{
	// �w�i�摜�̕`��
	BackDraw();

	// �e�N���X�̕`�揈�����Ăяo��
	__super::Draw();

}

// �I��������
void InGameScene::Finalize()
{
	//�I�u�W�F�N�g�Ǘ��N���X�̏����擾
	GameObjectManager* gom = Singleton<GameObjectManager>::GetInstance();
	//�I�u�W�F�N�g�Ǘ��N���X�̏I�����������Ăяo��
	gom->Finalize();

	// �C���X�^���X�̍폜
	ResourceManager::DeleteInstance();
	GameObjectManager::DeleteInstance();
	InputManager::DeleteInstance();
}

// ���݂̃V�[�����
const eSceneType InGameScene::GetNowSceneType() const
{
	return eSceneType::eInGame;
}

// �X�e�[�W�̓Ǎ���
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

// �I�u�W�F�N�g�̐���
void InGameScene::LoadStageMapObject()
{
	//�C���X�^���X�̎擾
	GameObjectManager* obj_m = Singleton<GameObjectManager>::GetInstance();

	// �X�e�[�W�Ǎ��݂ō쐬�����I�u�W�F�N�g���̔z�񂩂�`�悷��
	for (int i = 0; i < map_object.size(); i++)
	{
		// csv����ǂݍ��񂾏��𗘗p�ł���悤�ɂ���
		const MapObjectData& object = map_object[i];

		// �I�u�W�F�N�g�̐������W
		Vector2D generate_location = Vector2D(object.spos_x * (D_OBJECT_SIZE * 2), (object.spos_y * (D_OBJECT_SIZE * 2))) - D_OBJECT_SIZE;

		// �ŏ��̕���������đ������l��ς���
		switch (object.mode)
		{
		case 'P':
			// �v���C���[�̐���
			player = obj_m->CreateObject<Player>(generate_location);
			break;
		case 'K':
			// �G�l�~�[�̐���
			kuribo = obj_m->CreateObject<Kuribo>(generate_location);
			enemys.push_back(kuribo);
			break;
		case 'H':
			// �n�e�i�u���b�N�̐���
			hatena = obj_m->CreateObject<Hatena>(generate_location);
			// �������p�ł���悤�ɔz��ŊǗ�
			blocks.push_back(hatena);
			break;
		case 'B':
			// �j��u���b�N�̐���
			brick = obj_m->CreateObject<Brick>(generate_location);
			// �������p�ł���悤�ɔz��ŊǗ�
			blocks.push_back(brick);
			break;
		//case 'I':
		//	// �j��s�u���b�N�̐���
		//	kai = obj_m->CreateObject<Kai>(generate_location);
		//	// �������p�ł���悤�ɔz��ŊǗ�
		//	blocks.push_back(kai);
		//	break;
		case 'M':
			// �|�[���g�b�v�̐���
			pole_t = obj_m->CreateObject<PoleTop>(generate_location);
			// �������p�ł���悤�ɔz��ŊǗ�
			blocks.push_back(pole_t);
			break;
		case 'L':
			// �|�[���_�E���̐���
			pole_d = obj_m->CreateObject<PoleDown>(generate_location);
			// �������p�ł���悤�ɔz��ŊǗ�
			blocks.push_back(pole_d);
			break;
		case 'G':
			// �n�ʂ�1�̃I�u�W�F�N�g�Ƃ��Đ�������
			generate_location = Vector2D((object.x_size * D_OBJECT_SIZE) + (object.spos_x * (D_OBJECT_SIZE * 2)), (object.spos_y * (D_OBJECT_SIZE * 2)));
			ground = obj_m->CreateObject<Ground>(generate_location);
			// �n�ʂ̓����蔻��̐ݒ�
			ground->SetGroundData(object.x_size, object.y_size);
			// �������p�ł���悤�ɔz��ŊǗ�
			blocks.push_back(ground);
			break;
		default:
			continue;
		}
	}
}

// �w�i�摜�̓Ǎ���
void InGameScene::LoadImages()
{
	// �w�i�摜�̓Ǎ���
	ResourceManager* rm = Singleton<ResourceManager>::GetInstance();
	back_ground_sora = rm->GetImages("Resource/Images/sora.png")[0];
	back_ground_block = rm->GetImages("Resource/Images/Block/floor.png")[0];
	back_ground_siro = rm->GetImages("Resource/Images/siro1.png")[0];
	back_ground_blocks = rm->GetImages("Resource/Images/Block/kai_block.png", 1, 1, 1, 32, 32)[0];
	// �R�̉摜�̓Ǎ���
	back_ground_mountain[0] = rm->GetImages("Resource/Images/mountain_left.png")[0];
	back_ground_mountain[1] = rm->GetImages("Resource/Images/mountain_right.png")[0];
	back_ground_mountain[2] = rm->GetImages("Resource/Images/mountain_up.png")[0];
	back_ground_mountain[5] = rm->GetImages("Resource/Images/mountain_surface2.png")[0];
	back_ground_mountain[4] = rm->GetImages("Resource/Images/mountain_surface.png")[0];
	back_ground_mountain[3] = rm->GetImages("Resource/Images/mountain_surface1.png")[0];
	// �t�̉摜�̓Ǎ���
	back_ground_ha[0] = rm->GetImages("Resource/Images/ha0.png")[0];
	back_ground_ha[1] = rm->GetImages("Resource/Images/ha1.png")[0];
	back_ground_ha[2] = rm->GetImages("Resource/Images/ha2.png")[0];
	// �_�̉摜�̓Ǎ���
	back_ground_cloud[0] = rm->GetImages("Resource/Images/cloud1.png")[0];
	back_ground_cloud[1] = rm->GetImages("Resource/Images/cloud2.png")[0];
	back_ground_cloud[2] = rm->GetImages("Resource/Images/cloud3.png")[0];
	back_ground_cloud[3] = rm->GetImages("Resource/Images/cloud6.png")[0];
	back_ground_cloud[4] = rm->GetImages("Resource/Images/cloud5.png")[0];
	back_ground_cloud[5] = rm->GetImages("Resource/Images/cloud4.png")[0];
	//�y�ǂ̉摜�̓Ǎ���
	back_ground_dokan[0] = rm->GetImages("Resource/Images/dokan_left_down.png")[0];
	back_ground_dokan[1] = rm->GetImages("Resource/Images/dokan_left_up.png")[0];
	back_ground_dokan[2] = rm->GetImages("Resource/Images/dokan_right_down.png")[0];
	back_ground_dokan[3] = rm->GetImages("Resource/Images/dokan_right_up.png")[0];
	// �|�[���̉摜�̓Ǎ���
	back_ground_pole[0] = rm->GetImages("Resource/Images/pole.png")[0];
	back_ground_pole[1] = rm->GetImages("Resource/Images/pole_down.png")[0];
	back_ground_pole[2] = rm->GetImages("Resource/Images/flag.png")[0];
}

// �w�i�摜�̐ݒ�
void InGameScene::BackDraw()
{
	// �X�e�[�W�Ǎ��݂ō쐬�����I�u�W�F�N�g���̔z�񂩂�`�悷��
	for (int i = 0; i < map_object.size(); i++)
	{
		// csv����ǂݍ��񂾏��𗘗p�ł���悤�ɂ���
		const MapObjectData& object = map_object[i];

		// �ʒu���̍Đݒ�
		screen_location.y = (object.spos_y * (D_OBJECT_SIZE * 2)) - D_OBJECT_SIZE;

		// �ŏ��̕���������đ������l��ς���
		switch (object.mode)
		{
		case 'S':
			back_ground_image = back_ground_sora;
			break;
		case '0':
			back_ground_image = back_ground_mountain[0];
			break;
		case '1':
			back_ground_image = back_ground_mountain[1];
			break;
		case '2':
			back_ground_image = back_ground_mountain[2];
			break;
		case '3':
			back_ground_image = back_ground_mountain[3];
			break;
		case '4':
			back_ground_image = back_ground_mountain[4];
			break;
		case '5':
			back_ground_image = back_ground_mountain[5];
			break;
		case '6':
			back_ground_image = back_ground_ha[0];
			break;
		case '7':
			back_ground_image = back_ground_ha[1];
			break;
		case '8':
			back_ground_image = back_ground_ha[2];
			break;
		case 'a':
			back_ground_image = back_ground_cloud[0];
			break;
		case 'b':
			back_ground_image = back_ground_cloud[1];
			break;
		case 'c':
			back_ground_image = back_ground_cloud[2];
			break;
		case 'd':
			back_ground_image = back_ground_cloud[3];
			break;
		case 'e':
			back_ground_image = back_ground_cloud[4];
			break;
		case 'f':
			back_ground_image = back_ground_cloud[5];
			break;
		//case 'I':
		//	back_ground_image = back_ground_blocks;
		//	break;
		case 'G':
			back_ground_image = back_ground_block;
			break;
		case 'D':
			back_ground_image = back_ground_dokan[0];
			break;
		case 'E':
			back_ground_image = back_ground_dokan[1];
			break;
		case 'F':
			back_ground_image = back_ground_dokan[2];
			break;
		case 'J':
			back_ground_image = back_ground_dokan[3];
			break;
		case 's':
			back_ground_image = back_ground_siro;
			break;
		case 'j':
			back_ground_image = back_ground_pole[2];
			break;
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