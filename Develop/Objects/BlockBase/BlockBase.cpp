#include "BlockBase.h"

BlockBase::BlockBase() :
	  velocity(0.0f)
	, is_scroll(false)
{
}

BlockBase::~BlockBase()
{
}

// 初期化処理
void BlockBase::Initialize()
{
}

// 更新処理
void BlockBase::Update(float delata_second)
{
}

// 描画処理
void BlockBase::Draw(const Vector2D& screen_offset) const
{
	__super::Draw(screen_offset);
}

// 終了時処理
void BlockBase::Finalize()
{
}

// ヒット時処理
void BlockBase::OnHitCollision(GameObjectBase* hit_object)
{
}

void BlockBase::SetScroll(float scroll)
{
	this->location.x = scroll;
}