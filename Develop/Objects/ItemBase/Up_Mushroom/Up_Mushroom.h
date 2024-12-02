#pragma once
#include "../ItemBase.h"

class Up_Mushroom : public ItemBase
{
public:
	Up_Mushroom();
	~Up_Mushroom();

public:
	void Initialize() override;
	void Update(float delata_second) override;
	void Draw(const Vector2D& screen_offset)const override;
	void Finalize() override;

public:
	void OnHitCollision(GameObjectBase* hit_object) override;

};

