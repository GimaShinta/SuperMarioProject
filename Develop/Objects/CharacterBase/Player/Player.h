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
	bool is_huge;
	Vector2D p_box_size[2];

private:
	class PlayerStateBase* state = nullptr;
	ePlayerState next_state = ePlayerState::NONE;
	ePlayerState now_state;
	ePlayerLooksState old_state;
	ePlayerLooksState now_looks_state;

private:
	std::vector<int> nomalmario_nums = { 0,1,2,1 };
	std::vector<int> dekamario_nums = { 2,3,4,3 };
	int firemario_num[2];
	int growthmario_num[2];
	int s_nomalmario_num[2];
	int s_dekamario_num[2];

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
	//アニメーション制御
	void AnimationControl(float delta_second, std::vector<int>& animation_image, std::vector<int>& animation_num, int n_jump, int n_squat);

public:
	//残り残機の取得
	int GetZanki();
	//パワーアップ状態かを見る
	bool GetPowerUp()const;
	//パワーアップ状態の設定
	void SetPowerDown();
	//死んだ状態かを見る
	bool GetDestroy()const;
	//ステートの切り替え
	void SetNextState(ePlayerState next_state);

	Vector2D& GetBoxSize();
	ePlayerState GetPlayerState() const;
	void SetScreenEnd(bool screen_end);
};

