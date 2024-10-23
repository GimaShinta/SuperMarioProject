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
	CharacterBase();
	~CharacterBase();

public:
	virtual void Initialize() override;
	virtual void Update(float delata_second) override;
	virtual void Draw(const Vector2D& screen_offset)const override;
	virtual void Finalize() override;

public:
	virtual void OnHitCollision(GameObjectBase* hit_object) override;

public:
	void Movement(float delta_second);
};

