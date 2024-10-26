#pragma once

#include "../Singleton.h"
#include "Vector2D.h"
#include <vector>
#include <map>

enum eObjectType
{
	eNone,
	ePlayer,
	eFireball,
	eEnemy,
	eGround,
	eItem,
};

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
	float point;

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

	float SetPoint(const eDirection direction, const Vector2D& location, const Vector2D& size);
};

