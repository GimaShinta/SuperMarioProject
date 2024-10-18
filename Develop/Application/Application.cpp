#include "Application.h"

#include "../Utility/ResourceManager.h"
#include "../Utility/InputManager.h"
#include "../Scene/SceneManager.h"

#include "DxLib.h"

// �O���[�o���ϐ���`
LONGLONG old_time;		// �O��v���l
LONGLONG now_time;		// ���݌v���l
float delta_second;		// �P�t���[��������̎���

Application::Application():end_check(false)
{
}

Application::~Application()
{
	ShutDown();
}

void Application::WakeUp()
{
	// �E�B���h�E���[�h�ŋN������
	ChangeWindowMode(TRUE);

	// �E�B���h�E�T�C�Y�̐ݒ�
	SetGraphMode(D_WIN_MAX_X, D_WIN_MAX_Y, D_COLOR_BIT);

	// �E�B���h�E�^�C�g���̐ݒ�
	SetWindowText("Game Development Supar_Mario 2024");

	// �����������s��Ȃ�
	SetWaitVSyncFlag(FALSE);

	// Log.txt�t�@�C���̐�������iDebug���[�h�̂ݐ�������j
#if _DEBUG
	SetOutApplicationLogValidFlag(TRUE);
#else
	SetOutApplicationLogValidFlag(FALSE);
#endif // _DEBUG

	// Dx���C�u�����̏�����
	if (DxLib_Init() == D_FAILURE)
	{
		throw std::string("Dx���C�u�����̏������Ɏ��s���܂����I\n");
	}

	SceneManager* scene = Singleton<SceneManager>::GetInstance();

	// �`����\��ʂɔ��f����
	SetDrawScreen(DX_SCREEN_BACK);

	// �ŏ��̃V�[�����^�C�g����ʂɂ���
	scene->ChangeScene(eSceneType::eTitle);

	// ��A�N�e�B�u��Ԃł����삳����
	SetAlwaysRunFlag(TRUE);

}

void Application::Run()
{
	// ���͏����擾����
	InputManager* input = Singleton<InputManager>::GetInstance();

	SceneManager* scene = Singleton<SceneManager>::GetInstance();

	// ���C�����[�v
	while (ProcessMessage() == D_SUCCESS)
	{
		// ���͏��̍X�V
		input->Update();

		// �t���[�����[�g�̐���
		FreamControl();

		// �`�揈��
		Graph();

		//�V�[���̐؂�ւ��ƃQ�[���̏I���`�F�b�N
		end_check = scene->Update(delta_second);

		//�Q�[�����I�����邩�m�F����
		if (end_check == true)
		{
			break;
		}
	}
}

void Application::ShutDown()
{
	// Singleton�̃C���X�^���X���������
	InputManager::DeleteInstance();
	ResourceManager::DeleteInstance();
	SceneManager::DeleteInstance();

	// Dx���C�u�����̎g�p���I������
	DxLib_End();
}

void Application::Graph() const
{
	SceneManager* scene = Singleton<SceneManager>::GetInstance();

	// ��ʂ̏�����
	ClearDrawScreen();

	// �V�[���̕`�揈��
	scene->Draw();

	// ����ʂ̓��e��\��ʂɔ��f����
	ScreenFlip();
}

void Application::FreamControl()
{
	// ���ݎ��Ԃ̎擾�i�ʕb�j
	now_time = GetNowHiPerformanceCount();

	// �J�n���Ԃ��猻�ݎ��Ԃ܂łɌo�߂������Ԃ��v�Z����i�ʕb�j
	// ����\���ʕb���b�ɕϊ�����
	delta_second = (float)(now_time - old_time) * 1.0e-6f;

	// �v���J�n���Ԃ��X�V����
	old_time = now_time;

	// �f�B�X�v���C�̃��t���b�V�����[�g���擾����
	float refresh_rate = (float)GetRefreshRate();

	// �P�t���[��������̎��Ԃ�1/���t���b�V�����[�g�b�𒴂�����A������
	if (delta_second > (1.0f / refresh_rate))
	{
		delta_second = (1.0f / refresh_rate);
	}
}

const float& Application::GetDeltaSecond()
{
	return delta_second;
}

int Application::ErrorThrow(std::string error_log)
{
	// Log.txt�ɃG���[���e��ǉ�����
	ErrorLogFmtAdd(error_log.c_str());
	return D_FAILURE;
}