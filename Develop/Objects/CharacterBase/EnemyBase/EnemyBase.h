#pragma once

#include "../CharacterBase.h"

//エネミー基底クラス
class EnemyBase :public CharacterBase
{
protected:
	enum eEnemyState
	{
		NONE,
		MOVE,
		DESTROTY
	};

public:
	EnemyBase();
	~EnemyBase();

public:
	virtual void Initialize() override;
	virtual void Update(float delata_second) override;
	virtual void Draw(const Vector2D& screen_offset)const override;
	virtual void Finalize() override;

public:
	virtual void OnHitCollision(GameObjectBase* hit_object) override;

//public:
//	void Movement(float delta_second);
};

