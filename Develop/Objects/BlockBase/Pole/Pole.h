#pragma once

#include "../BlockBase.h"

class Pole : public BlockBase
{
public:
	Pole();
	~Pole();

public:
	virtual void Initialize() override;
	void Update(float delata_second) override;
	void Draw(const Vector2D& screen_offset)const override;
	void Finalize() override;

public:
	void OnHitCollision(GameObjectBase* hit_object) override;
};

class PoleTop : public Pole
{
	void Initialize() override;
};

class PoleDown : public Pole
{
	void Initialize() override;
};

