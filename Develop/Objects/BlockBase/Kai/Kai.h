#pragma once
#include "../BlockBase.h"

class Kai : public BlockBase
{
public:
	Kai();
	~Kai();

public:
	void Initialize() override;
	void Update(float delata_second) override;
	void Draw(const Vector2D& screen_offset)const override;
	void Finalize() override;

public:
	void OnHitCollision(GameObjectBase* hit_object) override;
	void SetGroundData(int x_size, int y_size);
};

