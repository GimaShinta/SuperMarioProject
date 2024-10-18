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
	// 入力情報を取得する
	InputManager* input = Singleton<InputManager>::GetInstance();

	// シーンの更新
	Application* app;
	eSceneType next_scene_type = current_scene->Update(app->GetDeltaSecond());

	// ゲームを終了するか確認する
	if ((next_scene_type == eSceneType::eXit) ||
		(input->GetButtonUp(XINPUT_BUTTON_BACK)) ||
		(input->GetKeyUp(KEY_INPUT_ESCAPE)))
	{
		return true;
	}

	// 現在のシーンタイプが次のシーンタイプと違っているか？
	if (current_scene->GetNowSceneType() != next_scene_type)
	{
		// シーン切り替え処理
		ChangeScene(next_scene_type);
	}
}

void SceneManager::Draw()
{
	// シーンの描画処理
	current_scene->Draw();
}

void SceneManager::Finalize()
{
	// シーン情報が生成されていれば、削除する
	if (current_scene != nullptr)
	{
		current_scene->Finalize();
		delete current_scene;
		current_scene = nullptr;
	}
}

void SceneManager::ChangeScene(eSceneType type)
{
	//引数で渡された情報から新しいシーンを作成する
	SceneBase* new_scene = CreateScene(type);

	//エラーチェック
	if (new_scene == nullptr)
	{
		throw("シーンが生成できませんでした\n");
	}

	//現在シーンの終了処理
	if (current_scene != nullptr)
	{
		current_scene->Finalize();
		delete current_scene;
	}

	//新しいシーンの初期化
	new_scene->Initialize();
	current_scene = new_scene;
}

SceneBase* SceneManager::CreateScene(eSceneType type)
{
	//シーン情報によって、生成するシーンを切り替える
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
