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

//�����蔻��N���X
class BoxCollision
{
public:
	bool						is_blocking;		// ���蔲���t���O
	eObjectType					object_type;		// ���g�̃I�u�W�F�N�g�^�C�v
	std::vector<eObjectType>	hit_object_type;	// �K�p����I�u�W�F�N�g�^�C�v
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

	// �����蔻��L���m�F����
	bool IsCheckHitTarget(eObjectType hit_object) const;

	float SetPoint(const eDirection direction, const Vector2D& location, const Vector2D& size);
};

