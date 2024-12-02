#pragma once
#include "../ItemBase.h"

class Coin : public ItemBase
{
public:
	Coin();
	~Coin();

public:
	void Initialize() override;
	void Update(float delata_second) override;
	void Draw(const Vector2D& screen_offset)const override;
	void Finalize() override;

public:
	void OnHitCollision(GameObjectBase* hit_object) override;

};

