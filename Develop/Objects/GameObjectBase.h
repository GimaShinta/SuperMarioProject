#pragma once

#include "../Utility/Vector2D.h"
#include "../Utility/Collision.h"

#define D_OBJECT_SIZE	(24.0f)			// オブジェクトサイズ

//オブジェクトベースクラス
class GameObjectBase
{
protected:
	class GameObjectManager* owner_scene;   //
	Vector2D location;              // 位置座標
	BoxCollision collision;            //
	unsigned char z_layer;          //

public:
	// 当たり判定サイズ
	Vector2D box_size;

protected:
	int image;                      // 画像用
	int animation_count;            // 一定時間の到達数のカウント
	float animation_time;           // アニメーションの間隔

public:
	bool is_mobility;               //
	// 死んでいるかどうか
	bool is_destroy;

public:
	GameObjectBase();
	virtual ~GameObjectBase();

public:
	// 初期化処理
	virtual void Initialize();
	// 更新処理
	virtual void Update(float delata_second);
	// 描画処理
	virtual void Draw(const Vector2D& screen_offset)const;
	// 終了時処理
	virtual void Finalize();

public:
	// ヒット時処理
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

