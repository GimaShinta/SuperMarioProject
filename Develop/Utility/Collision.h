#pragma once

#include "../Singleton.h"
#include "Vector2D.h"
#include <vector>
#include <map>

// オブジェクトのタイプ
enum eObjectType
{
	eNone,
	ePlayer,
	eFireball,
	eEnemy,
	eGround,
	eItem,
};

// 進行方向
enum eDirection
{
	UP,
	DOWN,
	LEFT,
	REGHT
};

//当たり判定クラス
class BoxCollision
{
public:
	bool						is_blocking;		// すり抜けフラグ
	eObjectType					object_type;		// 自身のオブジェクトタイプ
	std::vector<eObjectType>	hit_object_type;	// 適用するオブジェクトタイプ
	Vector2D point[2];

public:
	BoxCollision() :
		is_blocking(false),
		object_type(eObjectType::eNone),
		hit_object_type()
	{
	}
	~BoxCollision()
	{
		hit_object_type.clear();
	}

	// 当たり判定有効確認処理
	bool IsCheckHitTarget(eObjectType hit_object) const;
};

/// <summary>
/// 当たり判定確認処理
/// </summary>
/// <param name="c1">形状の情報1</param>
/// <param name="c2">形状の情報2</param>
/// <returns>当たっているなら、true</returns>
bool IsCheckCollision(const BoxCollision& c1, const BoxCollision& c2);

