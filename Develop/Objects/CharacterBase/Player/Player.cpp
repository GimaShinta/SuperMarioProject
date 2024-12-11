#include "Player.h"
#include "DxLib.h"

#include "../../../Utility/ResourceManager.h"
#include "../../../Objects/GameObjectManager.h"
#include "State/Factory/PlayerStateFactory.h"
#include "../../../Application/Application.h"

#include <cstdlib>

#define D_GRAVITY (9.80f)      //重力加速度(m/ss)

/*でかくなったら埋まるからそれぞれで描画した方がいいかも*/


Player::Player() :
	  zanki(0)
	, coin_count(0)
	, is_star(false)
	, screen_end(false)
	, is_huge(false)
	, flip_flag(FALSE)
{
}

Player::~Player()
{
}

//初期化処理
void Player::Initialize()
{
	// 値の初期化
	state = PlayerStateFactory::Get((*this), ePlayerState::IDLE);
	next_state = ePlayerState::NONE;
	now_state = ePlayerState::NONE;
	now_looks_state = ePlayerLooksState::NOMALMARIO;
	velocity = Vector2D(0, 0);
	g_velocity = 0.0f;
	is_mobility = true;
	box_size = Vector2D(D_OBJECT_SIZE);
	p_box_size[0] = box_size;
	p_box_size[1] = Vector2D(D_OBJECT_SIZE, (D_OBJECT_SIZE * 2));

	// マリオ画像の読込みと初期設定
	ResourceManager* rm = Singleton<ResourceManager>::GetInstance();
	nomalmario_animation = rm->GetImages("Resource/Images/Mario/mario.png", 9, 9, 1, 32, 32);
	dekamario_animation = rm->GetImages("Resource/Images/Mario/dekamario.png", 10, 10, 1, 32, 64);
	image = nomalmario_animation[0];

	// 当たり判定のオブジェクト設定
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
	// 見た目の状態によって処理を変更
	switch (now_looks_state)
	{
	case ePlayerLooksState::NOMALMARIO:
		is_huge = false;
		// アニメーション制御
		AnimationControl(delta_second, nomalmario_animation, nomalmario_nums, 5, NULL);
		break;
	case ePlayerLooksState::DEKAMARIO:
		is_huge = true;
		// アニメーション制御
		AnimationControl(delta_second, dekamario_animation, dekamario_nums, 6, 1);
		break;
	case ePlayerLooksState::FIREMARIO:
		is_huge = true;
		break;
	case ePlayerLooksState::STARNOMALMARIO:
		is_huge = false;
		break;
	case ePlayerLooksState::STARDEKAMARIO:
		is_huge = true;
		break;
	case ePlayerLooksState::DESTROYMARIO:
		break;
	}

	// 大きさによって当たり判定サイズを変更する
	if (is_huge == false)
	{
		box_size = p_box_size[0];
	}
	else
	{
		box_size = p_box_size[1];
	}

	// stateの変更処理
	if (next_state != ePlayerState::NONE && is_mobility == true)
	{
		//現在の移動状態を保管
		now_state = next_state;

		state = PlayerStateFactory::Get((*this), next_state);
		next_state = ePlayerState::NONE;
	}

	//状態別の更新処理を行う
	state->Update(delta_second);

	//重力速度の計算
	g_velocity += D_GRAVITY;
	velocity.y += g_velocity * delta_second;

	//x0.0f地点を壁と仮定
	if (location.x < 0.0f + box_size.x)
	{
		location.x = 0.0f + box_size.x;
	}

	//背景スクロールが右端に着いたらプレイヤーの移動範囲を拡大する
	if (screen_end == false)
	{
		//ウィンドウの半分の地点を壁と仮定
		if (location.x > D_WIN_MAX_X / 2)
		{
			location.x = D_WIN_MAX_X / 2;
		}
	}
	else
	{
		//ウィンドウの右端地点を壁と仮定
		if (location.x > D_WIN_MAX_X - box_size.x)
		{
			location.x = D_WIN_MAX_X - box_size.x;
		}
	}

	// 移動の実行
	__super::Movement(delta_second);

	// 画面外で削除する
	__super::Update(delta_second);
}

/// <summary>
/// 描画処理
/// </summary>
/// <param name="screen_offset"></param>
void Player::Draw(const Vector2D& screen_offset) const
{
	//状態別の描画処理を行う
	state->Draw();

	if (is_huge == false)
	{
		DrawRotaGraphF(location.x, location.y, 1.5, 0.0, image, TRUE, flip_flag);
	}
	else
	{
		DrawRotaGraphF(location.x, location.y - D_OBJECT_SIZE, 1.5, 0.0, image, TRUE, flip_flag);
	}

	//親クラスの描画処理を行う
	//__super::Draw(screen_offset);

	DrawString(0, 120, "プレイヤーの描画ok", GetColor(255, 255, 255), TRUE);
}

//終了時処理
void Player::Finalize()
{
	//インスタンスの取得
	PlayerStateFactory* factory = Singleton<PlayerStateFactory>::GetInstance();
	factory->Finalize();
	ResourceManager::DeleteInstance();
	PlayerStateFactory::DeleteInstance();
}

//ヒット時処理
void Player::OnHitCollision(GameObjectBase* hit_object)
{
	// インスタンスの取得
	GameObjectManager* objm = Singleton<GameObjectManager>::GetInstance();

	// めり込み量を見て比べる。xが優先されているように見える
	//２つのオブジェクトの距離を取得
	Vector2D diff = location - hit_object->GetLocation();

	// めり込み方向を計算
	Vector2D direction = diff.Normalize();

	// 衝突面に対する法線ベクトルを計算
	Vector2D normal = direction * -1.0f;

	// プレイヤーの速度ベクトル
	Vector2D p_velocity = velocity;

	// 敵かブロックに当たった時
	if (hit_object->GetCollision().object_type == eObjectType::eEnemy || hit_object->GetCollision().object_type == eObjectType::eBlock)
	{
		// 衝突方向の判定
		if (Vector2D::Dot(normal, p_velocity) < 0)
		{
			// プレイヤーは衝突面から離れる方向に動いている
			// 特に処理は不要
		}
		else
		{
			// プレイヤーは衝突面に向かって動いている
			// 衝突方向をX軸、Y軸で比較
			Vector2D x_axis(1.0f, 0.0f);
			Vector2D y_axis(0.0f, 1.0f);

			float dot_x = abs(Vector2D::Dot(normal, x_axis));
			float dot_y = abs(Vector2D::Dot(normal, y_axis));

			if (dot_x > dot_y)
			{
				// 主にX軸方向の衝突 (左または右)
				if (direction.x < 0)
				{
					// 左側から衝突
					// 左側からの衝突時の処理
					objm->DestroyGameObject(this);
				}
				else
				{
					// 右側から衝突
					// 右側からの衝突時の処理
					objm->DestroyGameObject(this);
				}
			}
			else
			{
				// 主にY軸方向の衝突 (上または下)
				if (direction.y < 0)
				{
					// 上側から衝突
					// 上側からの衝突時の処理
					velocity.y -= 1000.0f;
				}
				else
				{
					// 下側から衝突
					// 下側からの衝突時の処理
					objm->DestroyGameObject(this);
				}
			}
		}
	}

	// 当たったのが地面だったら
	if (hit_object->GetCollision().object_type == eObjectType::eGround)
	{
		float ground_location = hit_object->GetLocation().y - (hit_object->GetBoxSize().y + D_OBJECT_SIZE);
		// y600.0f地点を地面と仮定.
		if (location.y > ground_location)
		{
			location.y = ground_location;
			g_velocity = 0.0f;
		}
	}
}

/// <summary>
/// アニメーションの制御
/// </summary>
/// <param name="delta_second">1フレーム当たりの時間</param>
/// <param name="animation_image">アニメーション総画像</param>
/// <param name="animation_num">アニメーション順序</param>
/// <param name="n_jump">ジャンプ画像の位置</param>
/// <param name="n_squat">しゃがみ画像の位置</param>
void Player::AnimationControl(float delta_second, std::vector<int>& animation_image, std::vector<int>& animation_num, int n_jump, int n_squat)
{
	switch (now_state)
	{
		case ePlayerState::RUN:
			// アニメーション総画像とアニメーション順序を引数とする
			GameObjectBase::AnimationControl(delta_second, animation_image, animation_num);
			break;
		case ePlayerState::IDLE:
			// 停止している画像を代入
			image = animation_image[0];
			break;
		case ePlayerState::JUMP:
			// n_jump番目にあるジャンプ画像を代入
			image = animation_image[n_jump];
			break;
		case ePlayerState::SQUAT:
			// n_squat番目にあるしゃがみ画像を代入
			image = animation_image[n_squat];
		case ePlayerState::NONE:
			break;
	}
}

// 残り残機の取得
int Player::GetZanki()
{
	return 0;
}

// パワーアップ状態かを見る
bool Player::GetPowerUp() const
{
	return false;
}

// パワーダウンさせる
void Player::SetPowerDown()
{
}

// 死んだ状態かを見る
bool Player::GetDestroy() const
{
	return false;
}


// 次のシーンに切り替え
void Player::SetNextState(ePlayerState next_state)
{
	this->next_state = next_state;
}

// プレイヤーの判定サイズを取得
Vector2D& Player::GetBoxSize()
{
	return box_size;
}

// プレイヤーの移動状態を取得
ePlayerState Player::GetPlayerState() const
{
	//現在の移動状態
	return now_state;
}

// 背景スクロールが端に着いたかを設定
void Player::SetScreenEnd(bool screen_end)
{
	this->screen_end = screen_end;
}

Vector2D Player::GetVelocity()
{
	return velocity;
}
