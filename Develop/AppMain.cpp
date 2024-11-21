#include "DxLib.h"
#include "Application/Application.h"

//メイン関数
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd)
{
    //アプリケーションを生成する
	Application app;

	try
	{
		//初期化処理
		//Initialize
		app.WakeUp();

		//実行処理
		//Update
		app.Run();

		//終了時処理
		//Finalize
		app.ShutDown();
	}
	catch (std::string error_log)
	{
		//エラー内容を出力する
		return app.ErrorThrow(error_log);
	}

	//終了状態を通知する
	return D_SUCCESS;
}