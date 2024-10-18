#pragma once

#include "../Utility/Vector2D.h"
#include "../Utility/Collision.h"
#include "GameObjectManager.h"

class GameObjectBase
{
protected:
	Vector2D location;
	Collision collision;
	unsigned char z_layer;

protected:
	int image;
	int animation_count;
	float animation_time;

public:
	bool is_mobility;

public:
	virtual void Initialize();
	virtual void Update(float delata_second);
	virtual void Draw(const Vector2D location)const;
	virtual void Finalize();

public:
	virtual void OnHitCollision(GameObjectBase* object);

public:
	const Vector2D& GetLocation();
	void SetLocation(const Vector2D&);
	const Collision& GetCollision()const;
	const unsigned char GetZlayer()const;
	const bool GetMobility()const;
};

