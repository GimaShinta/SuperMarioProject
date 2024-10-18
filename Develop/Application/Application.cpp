#include "Application.h"

#include "../Utility/ResourceManager.h"
#include "../Utility/InputManager.h"
#include "../Scene/SceneManager.h"

#include "DxLib.h"

// グローバル変数定義
LONGLONG old_time;		// 前回計測値
LONGLONG now_time;		// 現在計測値
float delta_second;		// １フレームあたりの時間

Application::Application():end_check(false)
{
}

Application::~Application()
{
	ShutDown();
}

void Application::WakeUp()
{
	// ウィンドウモードで起動する
	ChangeWindowMode(TRUE);

	// ウィンドウサイズの設定
	SetGraphMode(D_WIN_MAX_X, D_WIN_MAX_Y, D_COLOR_BIT);

	// ウィンドウタイトルの設定
	SetWindowText("Game Development Supar_Mario 2024");

	// 垂直同期を行わない
	SetWaitVSyncFlag(FALSE);

	// Log.txtファイルの生成制御（Debugモードのみ生成する）
#if _DEBUG
	SetOutApplicationLogValidFlag(TRUE);
#else
	SetOutApplicationLogValidFlag(FALSE);
#endif // _DEBUG

	// Dxライブラリの初期化
	if (DxLib_Init() == D_FAILURE)
	{
		throw std::string("Dxライブラリの初期化に失敗しました！\n");
	}

	SceneManager* scene = Singleton<SceneManager>::GetInstance();

	// 描画先を表画面に反映する
	SetDrawScreen(DX_SCREEN_BACK);

	// 最初のシーンをタイトル画面にする
	scene->ChangeScene(eSceneType::eTitle);

	// 非アクティブ状態でも動作させる
	SetAlwaysRunFlag(TRUE);

}

void Application::Run()
{
	// 入力情報を取得する
	InputManager* input = Singleton<InputManager>::GetInstance();

	SceneManager* scene = Singleton<SceneManager>::GetInstance();

	// メインループ
	while (ProcessMessage() == D_SUCCESS)
	{
		// 入力情報の更新
		input->Update();

		// フレームレートの制御
		FreamControl();

		// 描画処理
		Graph();

		//シーンの切り替えとゲームの終了チェック
		end_check = scene->Update(delta_second);

		//ゲームを終了するか確認する
		if (end_check == true)
		{
			break;
		}
	}
}

void Application::ShutDown()
{
	// Singletonのインスタンスを解放する
	InputManager::DeleteInstance();
	ResourceManager::DeleteInstance();
	SceneManager::DeleteInstance();

	// Dxライブラリの使用を終了する
	DxLib_End();
}

void Application::Graph() const
{
	SceneManager* scene = Singleton<SceneManager>::GetInstance();

	// 画面の初期化
	ClearDrawScreen();

	// シーンの描画処理
	scene->Draw();

	// 裏画面の内容を表画面に反映する
	ScreenFlip();
}

void Application::FreamControl()
{
	// 現在時間の取得（μ秒）
	now_time = GetNowHiPerformanceCount();

	// 開始時間から現在時間までに経過した時間を計算する（μ秒）
	// 分解能をμ秒→秒に変換する
	delta_second = (float)(now_time - old_time) * 1.0e-6f;

	// 計測開始時間を更新する
	old_time = now_time;

	// ディスプレイのリフレッシュレートを取得する
	float refresh_rate = (float)GetRefreshRate();

	// １フレーム当たりの時間が1/リフレッシュレート秒を超えたら、整える
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
	// Log.txtにエラー内容を追加する
	ErrorLogFmtAdd(error_log.c_str());
	return D_FAILURE;
}
