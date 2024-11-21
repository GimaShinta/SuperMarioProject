#include "Player.h"
#include "DxLib.h"

#include "../../../Utility/ResourceManager.h"
#include "State/Factory/PlayerStateFactory.h"

#define D_GRAVITY (9.80f)      //重力加速度(m/ss)
#define D_MAX_SPEED (10.0f)

/*でかくなったら埋まるからそれぞれで描画した方がいいかも*/


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
	now_state = ePlayerState::NONE;
	now_looks_state = ePlayerLooksState::NOMALMARIO;
	velocity = Vector2D(0, 0);
	g_velocity = 0.0f;
	is_mobility = true;
	box_size = Vector2D(D_OBJECT_SIZE);
	p_box_size[0] = box_size;
	p_box_size[1] = Vector2D(D_OBJECT_SIZE, (D_OBJECT_SIZE * 2));

	ResourceManager* rm = Singleton<ResourceManager>::GetInstance();
	nomalmario_animation = rm->GetImages("Resource/Images/Mario/mario.png", 9, 9, 1, 32, 32);
	dekamario_animation = rm->GetImages("Resource/Images/Mario/dekamario.png", 10, 10, 1, 32, 64);
	image = nomalmario_animation[0];

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
	/***********
	* 見た目の状態によって処理を変更
	* 
	*  1,判定サイズの初期化
	*  2,アニメーション制御（引数は各状態の画像配列と順序配列、ジャンプ画像の位置、しゃがみ画像の位置）
	* 
	*************/
	switch (now_looks_state)
	{
	case ePlayerLooksState::NOMALMARIO:
		box_size = p_box_size[0];
		//アニメーション制御
		AnimationControl(delta_second, nomalmario_animation, nomalmario_nums, 5, NULL);
		break;
	case ePlayerLooksState::DEKAMARIO:
		box_size = p_box_size[1];
		//アニメーション制御
		AnimationControl(delta_second, dekamario_animation, dekamario_nums, 6, 1);
		break;
	case ePlayerLooksState::FIREMARIO:
		box_size = p_box_size[1];
		break;
	case ePlayerLooksState::STARNOMALMARIO:
		box_size = p_box_size[0];
		break;
	case ePlayerLooksState::STARDEKAMARIO:
		box_size = p_box_size[1];
		break;
	case ePlayerLooksState::DESTROYMARIO:
		break;
	}

	// stateの変更処理
	if (next_state != ePlayerState::NONE && is_mobility == true)
	{
		//現在の移動状態を保管
		now_state = next_state;

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
	state->Update(delta_second);

	//移動の実行
	location += velocity;

	//y600.0f地点を地面と仮定
	if (location.y > 600.0f)
	{
		location.y = 600.0f;
		g_velocity = 0.0f;
		velocity = 0.0f;
	}

	//x0.0f地点を壁と仮定
	if (location.x < 0.0f + box_size.x)
	{
		location.x = 0.0f + box_size.x;
		velocity = 0.0f;
	}

	//背景スクロールが右端に着いたら移動範囲を拡大する
	if (screen_end == false)
	{
		//x400.0f地点を壁と仮定
		if (location.x > 480.0f - (box_size.x * 2 ))
		{
			location.x = 480.0f - (box_size.x * 2);
			velocity = 0.0f;
		}
	}
	else
	{
		//x960.0f地点を壁と仮定
		if (location.x > 960.0f - box_size.x)
		{
			location.x = 960.0f - box_size.x;
			velocity = 0.0f;
		}
	}
}

/// <summary>
/// 描画処理
/// </summary>
/// <param name="screen_offset"></param>
void Player::Draw(const Vector2D& screen_offset) const
{
	//状態別の描画処理を行う
	state->Draw();

	//親クラスの描画処理を行う
	__super::Draw(screen_offset);

	DrawString(0, 120, "プレイヤーの描画ok", GetColor(255, 255, 255), TRUE);
}

//終了時処理
void Player::Finalize()
{
	//インスタンスの取得
	PlayerStateFactory* factory = Singleton<PlayerStateFactory>::GetInstance();
	factory->Finalize();
	ResourceManager::DeleteInstance();
}

//ヒット時処理
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
		//else
		//{
		//	//めり込んだ差分だけ戻る
		//	location.x += diff.x + box_size.x;
		//}

		//// 2つのオブジェクトの距離を取得
		//Vector2D diff = location - hit_object->GetLocation();

		//// 2つのオブジェクトの当たり判定の大きさを取得
		//Vector2D pbox_size = ((box_size + hit_object->GetBoxSize()) / 2.0f);

		//// 距離より大きさが大きい場合、Hit判定をする
		//if (fabsf(diff.x) < pbox_size.x) 
		//{
		//	// めり込み量を計算
		//	float overlap = pbox_size.x - fabsf(diff.x);

		//	// 衝突方向を判定し、位置を調整
		//	if (diff.x > 0) 
		//	{
		//		// 右方向から衝突
		//		location.x -= overlap;
		//	}
		//	else 
		//	{
		//		// 左方向から衝突
		//		location.x += overlap;
		//	}
		//}

#else
		// 当たり判定情報を取得して、カプセルがある位置を求める
		BoxCollision hc = hit_object->GetCollision();
		hc.point[0] += hit_object->GetLocation() - hit_object->GetBoxSize();
		hc.point[1] += hit_object->GetLocation() + hit_object->GetBoxSize();

		Vector2D p_point[2];
		p_point[0] = location + box_size;
		p_point[0] = location - box_size;

		float diff[2];
		diff[0] = p_point[0].x - hc.point[0].x;

#endif
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
			GameObjectBase::AnimationControl(delta_second, animation_image, animation_num);
			break;
		case ePlayerState::IDLE:
			image = animation_image[0];
			break;
		case ePlayerState::JUMP:
			image = animation_image[n_jump];
			break;
		case ePlayerState::SQUAT:
			image = animation_image[n_squat];
		case ePlayerState::NONE:
			break;
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


//次のシーンに切り替え
void Player::SetNextState(ePlayerState next_state)
{
	this->next_state = next_state;
}

//プレイヤーの判定サイズを取得
Vector2D& Player::GetBoxSize()
{
	return box_size;
}

//プレイヤーの移動状態を取得
ePlayerState Player::GetPlayerState() const
{
	//現在の移動状態
	return now_state;
}

//背景スクロールが端に着いたかを設定
void Player::SetScreenEnd(bool screen_end)
{
	this->screen_end = screen_end;
}
