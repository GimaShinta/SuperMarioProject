#pragma once

#include "../Utility/Vector2D.h"
#include "../Utility/Collision.h"

#define D_OBJECT_SIZE	(24.0f)			// オブジェクトサイズ

//オブジェクトベースクラス
class GameObjectBase
{
protected:
	class GameObjectManager* owner_scene;   //
	Vector2D location;              //
	BoxCollision collision;            //
	unsigned char z_layer;          //

public:
	Vector2D box_size;

protected:
	int image;                      //
	int animation_count;            //
	float animation_time;           //

public:
	bool is_mobility;               //

public:
	GameObjectBase();
	virtual ~GameObjectBase();

public:
	virtual void Initialize();
	virtual void Update(float delata_second);
	virtual void Draw(const Vector2D& screen_offset)const;
	virtual void Finalize();

public:
	virtual void OnHitCollision(GameObjectBase* hit_object);

	//複数枚アニメーションの制御
	virtual void AnimationControl(float delta_second, std::vector<int>& animation_image, std::vector<int>& animation_num);
	//一枚アニメーションの制御
	virtual void AnimationControl(float delta_second, int animation_image);

public:
	void SetOwnerScene(class GameObjectManager* scene);
	void SetLocation(const Vector2D& location);
	Vector2D& GetLocation();
	Vector2D& GetBoxSize();
	const BoxCollision& GetCollision()const;
	const unsigned char GetZLayer()const;
	const bool& GetMobility()const;
};

