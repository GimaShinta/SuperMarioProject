#pragma once

#include "../BlockBase.h"

class Ground : public BlockBase
{
public:
	Ground();
	~Ground();

public:
	void Initialize() override;
	void Update(float delata_second) override;
	void Draw(const Vector2D& screen_offset)const override;

public:
	void OnHitCollision(GameObjectBase* hit_object) override;
	void SetGroundData(int x_size, int y_size);
};

