#pragma once

#include "../CharacterBase.h"
#include <vector>

#include "State/Enum/PlayerState.h"

//マリオの見た目の状態
enum ePlayerLooksState
{
	NOMALMARIO,
	STARNOMALMARIO,
	DEKAMARIO,
	STARDEKAMARIO,
	FIREMARIO,
	DESTROYMARIO
};

//プレイヤークラス
class Player : public CharacterBase
{
private:
	std::vector<int> nomalmario_animation;
	std::vector<int> s_nomalmario_animation;
	std::vector<int> growth_animation;
	std::vector<int> dekamario_animation;
	std::vector<int> s_dekamario_animation;
	std::vector<int> firemario_animation;

public:
	int zanki;
	int coin_count;
	bool is_star;
	bool is_destroy;
	bool screen_end;

private:
	class PlayerStateBase* state = nullptr;
	ePlayerState next_state = ePlayerState::NONE;
	ePlayerState now_state;
	ePlayerLooksState old_state;

private:
	//多分Stateで書く
	int nomalmario_num[3];
	int s_nomalmario_num[2];
	int growthmario_num[2];
	int dekamario_num[2];
	int s_dekamario_num[2];
	int firemario_num[2];

public:
	Player();
	~Player();

public:
	//初期化処理
	void Initialize() override;

	/// <summary>
	/// 更新処理
	/// </summary>
	/// <param name="delata_second"></param>
	void Update(float delata_second) override;

	/// <summary>
	/// 描画処理
	/// </summary>
	/// <param name="screen_offset"></param>
	void Draw(const Vector2D& screen_offset)const override;

	//終了時処理
	void Finalize() override;

public:
	void OnHitCollision(GameObjectBase* hit_object) override;

public:
	//残り残機の取得
	int GetZanki();
	//パワーアップ状態かを見る
	bool GetPowerUp()const;
	//パワーアップ状態の設定
	void SetPowerDown();
	//死んだ状態かを見る
	bool GetDestroy()const;
	//アニメーション制御
	void AnimationControl(float delta_second);
	//ステートの切り替え
	void SetNextState(ePlayerState next_state);

	Vector2D& GetBoxSize();
	ePlayerState GetPlayerState();
	void SetScreenEnd(bool screen_end);
};

