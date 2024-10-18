#include "SceneManager.h"

#include "TitleScene/TitleScene.h"
#include "InGameScene/InGameScene.h"
#include "ResultScene/ResultScene.h"

#include "../Application/Application.h"
#include "../Utility/InputManager.h"

#include "DxLib.h"

SceneManager::SceneManager()
{
}

SceneManager::~SceneManager()
{
}

void SceneManager::Initialize()
{
}

bool SceneManager::Update(float delta_second)
{
	// ���͏����擾����
	InputManager* input = Singleton<InputManager>::GetInstance();

	// �V�[���̍X�V
	Application* app;
	eSceneType next_scene_type = current_scene->Update(app->GetDeltaSecond());

	// �Q�[�����I�����邩�m�F����
	if ((next_scene_type == eSceneType::eXit) ||
		(input->GetButtonUp(XINPUT_BUTTON_BACK)) ||
		(input->GetKeyUp(KEY_INPUT_ESCAPE)))
	{
		return true;
	}

	// ���݂̃V�[���^�C�v�����̃V�[���^�C�v�ƈ���Ă��邩�H
	if (current_scene->GetNowSceneType() != next_scene_type)
	{
		// �V�[���؂�ւ�����
		ChangeScene(next_scene_type);
	}
}

void SceneManager::Draw()
{
	// �V�[���̕`�揈��
	current_scene->Draw();
}

void SceneManager::Finalize()
{
	// �V�[����񂪐�������Ă���΁A�폜����
	if (current_scene != nullptr)
	{
		current_scene->Finalize();
		delete current_scene;
		current_scene = nullptr;
	}
}

void SceneManager::ChangeScene(eSceneType type)
{
	//�����œn���ꂽ��񂩂�V�����V�[�����쐬����
	SceneBase* new_scene = CreateScene(type);

	//�G���[�`�F�b�N
	if (new_scene == nullptr)
	{
		throw("�V�[���������ł��܂���ł���\n");
	}

	//���݃V�[���̏I������
	if (current_scene != nullptr)
	{
		current_scene->Finalize();
		delete current_scene;
	}

	//�V�����V�[���̏�����
	new_scene->Initialize();
	current_scene = new_scene;
}

SceneBase* SceneManager::CreateScene(eSceneType type)
{
	//�V�[�����ɂ���āA��������V�[����؂�ւ���
	switch (type)
	{
	case eSceneType::eTitle:
		return dynamic_cast<SceneBase*>(new TitleScene());
	case eSceneType::eInGame:
		return dynamic_cast<SceneBase*>(new InGameScene());
	case eSceneType::eResult:
		return dynamic_cast<SceneBase*>(new ResultScene());
	case eSceneType::eXit:
	default:
		return nullptr;
	}
}
