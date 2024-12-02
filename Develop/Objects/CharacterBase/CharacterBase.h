#pragma once

#include "../GameObjectBase.h"

class CharacterBase : public GameObjectBase
{
protected:
	float g_velocity;
	int hit_point;
	bool on_ground;

public:
	Vector2D velocity;
	//Vector2D box_size = (0.0f);

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
	virtual void Movement(float delta_second);
	void SetVelocity(const Vector2D& velo);
};

