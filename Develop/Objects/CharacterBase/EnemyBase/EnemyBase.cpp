#include "EnemyBase.h"

EnemyBase::EnemyBase()
{
}

EnemyBase::~EnemyBase()
{
}

// 初期化処理
void EnemyBase::Initialize()
{
}

// 更新処理
void EnemyBase::Update(float delata_second)
{
	__super::Update(delata_second);
}

// 描画処理
void EnemyBase::Draw(const Vector2D& screen_offset) const
{
	__super::Draw(screen_offset);
}

// 終了時処理
void EnemyBase::Finalize()
{
}

// ヒット時処理
void EnemyBase::OnHitCollision(GameObjectBase* hit_object)
{
}

// スクロールの分だけ加速させる
void EnemyBase::SetScroll(float scroll)
{
	this->location.x = scroll;
}