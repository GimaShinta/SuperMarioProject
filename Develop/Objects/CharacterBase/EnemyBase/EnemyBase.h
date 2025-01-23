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

protected:
	// 敵の画像
	std::vector<int> emove_animation;
	// 敵のアニメーションの順番
	std::vector<int> emove_nums = { 0,1 };

public:
	EnemyBase();
	~EnemyBase();

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

//public:
//	void Movement(float delta_second);

	// スクロールの分だけ加速させる
	void SetScroll(float scroll);
};

