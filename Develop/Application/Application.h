#pragma once

// インクルード
#include "../Singleton.h"
#include <string>

// マクロ定義
#define	D_SUCCESS		(0)		// 成功
#define	D_FAILURE		(-1)	// 失敗

#define D_WIN_MAX_X		(960)	// スクリーンサイズ（幅）
#define D_WIN_MAX_Y		(720)	// スクリーンサイズ（高さ）
#define D_COLOR_BIT		(32)	// カラービット

// プロトタイプ宣言
// (class Tで制限なしで使用)
class Application : public Singleton<class T>
{
private:
	bool end_check;

public:
	Application();
	~Application();

	void WakeUp();
	void Run();
	void ShutDown();

private:
	void Graph()const;

public:
	void FreamControl();
	const float& GetDeltaSecond();
	int ErrorThrow(std::string error_log);
};

