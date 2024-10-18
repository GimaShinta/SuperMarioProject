#pragma once

#include "../GameObjectBase.h"

class CharacterBase : public GameObjectBase
{
protected:
	Vector2D velocity;
	float g_velocity;
	int hit_point;
	bool on_ground;

public:
	virtual void OnHitCollision(GameObjectBase* object);
	void Movement(float delta_second);
};

