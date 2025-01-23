#pragma once

#include "../GameObjectBase.h"

// キャラクターベースクラス（メンバ関数のオーバーライド必須）
class CharacterBase : public GameObjectBase
{
protected:
	// 重力
	float g_velocity;
	int hit_point;
	// 地面の上にいるか
	bool on_ground;

public:
	// 速度
	Vector2D velocity;

public:
	CharacterBase();
	~CharacterBase();

public:
	// 初期化処理
	virtual void Initialize() override;
	// 更新処理
	virtual void Update(float delata_second) override;
	// 描画処理
	virtual void Draw(const Vector2D& screen_offset)const override;
	// 終了時処理
	virtual void Finalize() override;

public:
	// ヒット時処理
	virtual void OnHitCollision(GameObjectBase* hit_object) override;

public:
	// 移動処理
	virtual void Movement(float delta_second);
	// スクロール速さに合わせて加速させる
	void SetVelocity(const Vector2D& velocity);
};

