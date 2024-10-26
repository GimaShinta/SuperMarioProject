#include "Collision.h"

/// <summary>
/// 適用オブジェクトか確認する処理
/// </summary>
/// <param name="hit_object">相手のオブジェクトタイプ</param>
/// <returns>適用するオブジェクトなら、true</returns>
bool BoxCollision::IsCheckHitTarget(eObjectType hit_object) const
{
	// 適用するオブジェクトタイプなら、true
	for (eObjectType type : hit_object_type)
	{
		if (type == hit_object)
		{
			return true;
		}
	}

	return false;
}

float BoxCollision::SetPoint(const eDirection direction, const Vector2D& location, const Vector2D& size)
{
	switch (direction)
	{
		case eDirection::UP:
		point = location.y + size.y;
		break;

		case eDirection::DOWN:
		point = location.y + size.y;
		break;

		case eDirection::LEFT:
		point = location.x + size.x;
		break;

		case eDirection::REGHT:
		point = location.x - size.x;
		break;
	}

	return point;
}
