#pragma once

#include "../CharacterBase.h"
#include <vector>

#include "State/Enum/PlayerState.h"

//�}���I�̌����ڂ̏��
enum ePlayerLooksState
{
	NOMALMARIO,
	STARNOMALMARIO,
	DEKAMARIO,
	STARDEKAMARIO,
	FIREMARIO,
	DESTROYMARIO
};

//�v���C���[�N���X
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
	//����������
	void Initialize() override;

	/// <summary>
	/// �X�V����
	/// </summary>
	/// <param name="delata_second"></param>
	void Update(float delata_second) override;

	/// <summary>
	/// �`�揈��
	/// </summary>
	/// <param name="screen_offset"></param>
	void Draw(const Vector2D& screen_offset)const override;

	//�I��������
	void Finalize() override;

public:
	void OnHitCollision(GameObjectBase* hit_object) override;
	//�A�j���[�V��������
	void AnimationControl(float delta_second, std::vector<int>& animation_image, std::vector<int>& animation_num, int n_jump, int n_squat);

public:
	//�c��c�@�̎擾
	int GetZanki();
	//�p���[�A�b�v��Ԃ�������
	bool GetPowerUp()const;
	//�p���[�A�b�v��Ԃ̐ݒ�
	void SetPowerDown();
	//���񂾏�Ԃ�������
	bool GetDestroy()const;
	//�X�e�[�g�̐؂�ւ�
	void SetNextState(ePlayerState next_state);

	Vector2D& GetBoxSize();
	ePlayerState GetPlayerState() const;
	void SetScreenEnd(bool screen_end);
};

