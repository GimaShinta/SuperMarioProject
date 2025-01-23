#include "CharacterBase.h"

CharacterBase::CharacterBase()
{
}

CharacterBase::~CharacterBase()
{
}

// 初期化処理
void CharacterBase::Initialize()
{
}

/// <summary>
/// 更新処理
/// </summary>
/// <param name="delata_second">1フレーム当たりの時間</param>
void CharacterBase::Update(float delata_second)
{
	// 親クラスの更新処理を呼び出す
	__super::Update(delata_second);
}

// 描画処理
void CharacterBase::Draw(const Vector2D& screen_offset) const
{
	// 親クラスの描画処理を呼び出す
	__super::Draw(screen_offset);
}

// 終了時処理
void CharacterBase::Finalize()
{
}

// ヒット時処理
void CharacterBase::OnHitCollision(GameObjectBase* hit_object)
{
}

/// <summary>
/// 移動処理
/// </summary>
/// <param name="delta_second">１フレーム当たりの時間</param>
void CharacterBase::Movement(float delta_second)
{
	location += velocity * delta_second;
}

/// <summary>
/// スクロールに合わせて加速させる
/// </summary>
/// <param name="velocity">thisオブジェクトの速度</param>
void CharacterBase::SetVelocity(const Vector2D& velocity)
{
	this->velocity = velocity;
}
