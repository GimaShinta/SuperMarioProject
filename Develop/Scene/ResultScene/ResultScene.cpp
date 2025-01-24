#include "ResultScene.h"
#include "../../Application/Application.h"
#include "DxLib.h"

#include "../../Utility/InputManager.h"
#include "../../Utility/ResourceManager.h"

int player_zanki = 3;

ResultScene::ResultScene():
	mario_image(NULL),
	gameover_sound(NULL)
{
}

ResultScene::~ResultScene()
{
}

//����������
void ResultScene::Initialize()
{
	// �}���I�摜�̓Ǎ��݂Ə����ݒ�
	ResourceManager* rm = Singleton<ResourceManager>::GetInstance();
	mario_image = rm->GetImages("Resource/Images/Mario/mario.png", 9, 9, 1, 32, 32)[0];
	gameover_sound = rm->GetSounds("Resource/Sounds/SE_GameOver.wav");
	destroy_sound[0] = rm->GetSounds("Resource/Sounds/SE_Touch.wav");
	destroy_sound[1] = rm->GetSounds("Resource/Sounds/SE_Death.wav");

	if (player_zanki > 0)
	{
		// ���ʉ��Đ�
		PlaySoundMem(destroy_sound[0], DX_PLAYTYPE_NORMAL);
		PlaySoundMem(destroy_sound[1], DX_PLAYTYPE_NORMAL);
	}

}

/// <summary>
/// �X�V����
/// </summary>
/// <param name="delta_second">1�t���[��������̎���</param>
/// <returns>���݂̃V�[�����</returns>
eSceneType ResultScene::Update(float delta_second)
{
	//���͋@�\�̎擾
	InputManager* input = Singleton<InputManager>::GetInstance();

	// �c�@��0�ł͂Ȃ��Ƃ�
	if (player_zanki > 0)
	{
		//SPACE�L�[�Ń^�C�g����ʂɑJ�ڂ���
		if (input->GetKeyDown(KEY_INPUT_SPACE))
		{
			// �c�@�����炷
			player_zanki--;
			return eSceneType::eInGame;
		}
	}
	else
	{
		PlaySoundMem(gameover_sound, DX_PLAYTYPE_NORMAL);
		// �c�@��0�ɂȂ�����^�C�g���֑J��
		player_zanki = 3;
		return eSceneType::eTitle;
	}

	//���݂̃V�[�������擾
	return GetNowSceneType();
}

//�`�揈��
void ResultScene::Draw()
{
	DrawRotaGraph(D_WIN_MAX_X / 2 - ((D_OBJECT_SIZE * 2) * 1.5), D_WIN_MAX_Y / 2, 1.2, 0.0, mario_image, TRUE);
	SetFontSize(32);
	DrawFormatString(D_WIN_MAX_X / 2 - ((D_OBJECT_SIZE * 2) * 1), D_WIN_MAX_Y / 2 - (D_OBJECT_SIZE / 2), GetColor(255, 255, 255), " �~ %d", player_zanki, TRUE);
	DrawString(340,450, "SPACE TO START", GetColor(255, 255, 255), TRUE);
	SetFontSize(16);
}

//�I��������
void ResultScene::Finalize()
{
	// �C���X�^���X�̍폜
	InputManager::DeleteInstance();
}

//���݂̃V�[�������擾
const eSceneType ResultScene::GetNowSceneType() const
{
	return eSceneType::eResult;
}