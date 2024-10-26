#include "Collision.h"

/// <summary>
/// �K�p�I�u�W�F�N�g���m�F���鏈��
/// </summary>
/// <param name="hit_object">����̃I�u�W�F�N�g�^�C�v</param>
/// <returns>�K�p����I�u�W�F�N�g�Ȃ�Atrue</returns>
bool BoxCollision::IsCheckHitTarget(eObjectType hit_object) const
{
	// �K�p����I�u�W�F�N�g�^�C�v�Ȃ�Atrue
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
