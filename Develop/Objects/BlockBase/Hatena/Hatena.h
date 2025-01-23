#pragma once
#include "../BlockBase.h"

class Hatena : public BlockBase
{
private:
	class Mushroom* mush;
	bool is_kara;
	int kara_image;
	std::vector<int> hatena_animation;
	std::vector<int> hatena_num = { 0, 1, 2, 3, 2, 1 };

public:
	Hatena();
	~Hatena();

public:
	void Initialize() override;
	void Update(float delata_second) override;
	void Draw(const Vector2D& screen_offset)const override;
	void Finalize() override;

public:
	void OnHitCollision(GameObjectBase* hit_object) override;

private:
	void AnimationControl(float delta_second);
};

