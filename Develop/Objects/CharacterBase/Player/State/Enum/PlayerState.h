#pragma once

// プレイヤーの移動状態の列挙型クラス
enum class ePlayerState :unsigned char
{
	IDLE,
	RUN,
	JUMP,
	SQUAT,
	DESTROY,
	NONE
};