#pragma once
#include "../GameObjectBase.h"

class BlockBase : public GameObjectBase
{
protected:
	bool is_scroll;
	Vector2D velocity;
public:
	BlockBase();
	~BlockBase();

public:
	virtual void Initialize() override;
	virtual void Update(float delata_second) override;
	virtual void Draw(const Vector2D& screen_offset)const override;
	virtual void Finalize() override;

public:
	virtual void OnHitCollision(GameObjectBase* hit_object) override;

public:
	void SetScroll(float velo);
};

