#include "Player.h"
#include "DxLib.h"

#include "../../../Utility/ResourceManager.h"
#include "State/Factory/PlayerStateFactory.h"

#define D_GRAVITY (9.80f)      //重力加速度(m/ss)
#define D_MAX_SPEED (10.0f)

Player::Player()
{
}

Player::~Player()
{
}

//初期化処理
void Player::Initialize()
{
	state = PlayerStateFactory::Get((*this), ePlayerState::IDLE);
	next_state = ePlayerState::NONE;
	velocity = Vector2D(0, 0);
	g_velocity = 0.0f;
	is_mobility = true;

	ResourceManager* rm = Singleton<ResourceManager>::GetInstance();
	image = rm->GetImages("Resource/Images/Mario/mario.png", 9, 9, 1, 32, 32)[0];

	collision.is_blocking = true;
	collision.object_type = eObjectType::ePlayer;
	collision.hit_object_type.push_back(eObjectType::eEnemy);
}

/// <summary>
/// 更新処理
/// </summary>
/// <param name="delta_second">1フレーム当たりの時間</param>
void Player::Update(float delta_second)
{
	// stateの変更処理
	if (next_state != ePlayerState::NONE)
	{
		state = PlayerStateFactory::Get((*this), next_state);
		next_state = ePlayerState::NONE;
	}

#if 1
	//重力速度の計算
	g_velocity += D_GRAVITY / 444.0f;
	velocity.y += g_velocity;

	//最大重力の設定
	if (velocity.y > D_MAX_SPEED)
	{
		velocity.y = D_MAX_SPEED;
	}
#endif

	//状態別の更新処理を行う
	state->Update();

	//移動の実行
	location += velocity;

	//y600.0f地点を地面と仮定
	if (600.0f < location.y)
	{
		location.y = 600.0f;
		g_velocity = 0.0f;
		velocity = 0.0f;
	}

	//x0.0f地点を壁と仮定
	if (0.0f + box_size.x > location.x)
	{
		location.x = 0.0f + box_size.x;
		velocity = 0.0f;
	}
	//x1280.0f地点を壁と仮定
	if (1280.0f - box_size.x < location.x)
	{
		location.x = 1280.0f - box_size.x;
		velocity = 0.0f;
	}
}

/// <summary>
/// 描画処理
/// </summary>
/// <param name="screen_offset"></param>
void Player::Draw(const Vector2D& screen_offset) const
{
	__super::Draw(screen_offset);

	DrawString(0, 120, "プレイヤーの描画ok", GetColor(255, 255, 255), TRUE);

	//状態別の描画処理を行う
	state->Draw();
}

//終了時処理
void Player::Finalize()
{
	//インスタンスの取得
	PlayerStateFactory* factory = Singleton<PlayerStateFactory>::GetInstance();
	factory->Finalize();
}

void Player::OnHitCollision(GameObjectBase* hit_object)
{
	if (hit_object->GetCollision().object_type == eObjectType::eEnemy)
	{
#if 1
		//２つのオブジェクトの距離を取得
		Vector2D diff = location - hit_object->GetLocation();

		//２つのオブジェクトの当たり判定の大きさを取得
		Vector2D pbox_size = ((box_size + hit_object->GetBoxSize()) / 2.0f);

		//距離より大きさが大きい場合、Hit判定をする
		if ((fabsf(diff.x) < box_size.x))
		{
			//めり込んだ差分だけ戻る
			location.x -= diff.x + box_size.x;
		}
		if ((fabsf(diff.y) < box_size.y))
		{
			//めり込んだ差分だけ戻る
			location.y -= diff.y + box_size.y;
			velocity.y -= 15;
		}
#endif
	}
}

//残り残機の取得
int Player::GetZanki()
{
	return 0;
}

//パワーアップ状態かを見る
bool Player::GetPowerUp() const
{
	return false;
}

//パワーダウンさせる
void Player::SetPowerDown()
{
}

//死んだ状態かを見る
bool Player::GetDestroy() const
{
	return false;
}

//アニメーション制御
void Player::AnimationControl(float delta_second)
{
}

//次のシーンに切り替え
void Player::SetNextState(ePlayerState next_state)
{
	this->next_state = next_state;
}

Vector2D& Player::GetBoxSize()
{
	return box_size;
}
