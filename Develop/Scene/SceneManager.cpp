#include "SceneManager.h"

#include "TitleScene/TitleScene.h"
#include "InGameScene/InGameScene.h"
#include "ResultScene/ResultScene.h"

#include "../Application/Application.h"
#include "../Utility/InputManager.h"

#include "DxLib.h"

SceneManager::SceneManager():current_scene(nullptr)
{
}

SceneManager::~SceneManager()
{
}

//インスタンスの削除
void SceneManager::DeleteInstance()
{
	// 自クラスのポインタ（実体をアドレスの先で保有）
	static SceneManager* instance = nullptr;

	// インスタンスが存在している場合、削除する
	if (instance != nullptr)
	{
		delete instance;
		instance = nullptr;
	}
}

//初期化処理
void SceneManager::Initialize()
{
}

/// <summary>
/// 更新処理
/// </summary>
/// <param name="delta_second">1フレーム当たりの時間</param>
/// <returns></returns>
bool SceneManager::Update(float delta_second)
{
	// 入力情報を取得する
	InputManager* input = Singleton<InputManager>::GetInstance();

	// シーンの更新
	Application* app = Singleton<Application>::GetInstance();
	eSceneType next_scene_type = current_scene->Update(app->GetDeltaSecond());

	// ゲームを終了するか確認する
	if (next_scene_type == eSceneType::eXit ||
		input->GetKeyUp(KEY_INPUT_ESCAPE))
	{
		//エンドチェック（終了する）
		return true;
	}

	// 現在のシーンタイプが次のシーンタイプと違っているか？
	if (current_scene->GetNowSceneType() != next_scene_type)
	{
		// シーン切り替え処理
		ChangeScene(next_scene_type);
	}

	//エンドチェック（終了しない）
	return false;
}

//描画処理
void SceneManager::Draw()
{
	// シーンの描画処理
	current_scene->Draw();
}

//終了時処理
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

//シーンの切り替え
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

//シーンの生成
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
