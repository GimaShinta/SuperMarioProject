#pragma once

#include "../EnemyBase.h"

class Kuribo :public EnemyBase
{
public:
	Kuribo();
	~Kuribo();

public:
	void Initialize() override;
	void Update(float delata_second) override;
	void Draw(const Vector2D& screen_offset)const override;
	void Finalize() override;

public:
	void OnHitCollision(GameObjectBase* hit_object) override;
};

