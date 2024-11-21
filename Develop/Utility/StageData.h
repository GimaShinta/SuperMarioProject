#pragma once

#include "../Singleton.h"

class StageData : public Singleton<class T>
{
	/*
	
	オブジェクトは全てサイズ24で統一
	
	((24 * 2) * 15) = 720
	((オブジェクトサイズ) * 表示できるブロックの縦の数) = ウィンドウの縦サイズ
	
	*/
};

