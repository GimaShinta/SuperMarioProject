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

//�v���C���[�N���X�i�����o�֐��̃I�[�o�[���C�h�K�{�j
class Player : public CharacterBase
{
private:
	// �}���I�摜�p�A��Ԃ̐�����
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
	bool screen_end;
	bool is_huge;
	bool flip_flag;
	bool goal;
	Vector2D p_box_size[2];

private:
	class PlayerStateBase* state = nullptr;

public:
	ePlayerState next_state = ePlayerState::NONE;
	ePlayerState now_state;
	ePlayerLooksState old_state;
	ePlayerLooksState now_looks_state;

private:
	std::vector<int> nomalmario_nums = { 1,2,3,2 };
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
	void AnimationControl(float delta_second, std::vector<int>& animation_image, std::vector<int>& animation_num, int n_jump, int n_squat, int n_destroy);

public:
	//�c��c�@�̎擾
	int GetZanki();
	//�p���[�A�b�v��Ԃ�������
	bool GetPowerUp()const;
	//�p���[�A�b�v��Ԃ̐ݒ�
	void SetPowerDown();
	//���񂾏�Ԃ�������
	bool GetDestroy()const;
	// �S�[�����Ă��邩
	bool GetGoal();
	//�X�e�[�g�̐؂�ւ�
	void SetNextState(ePlayerState next_state);

	Vector2D& GetBoxSize();
	ePlayerState GetPlayerState() const;
	void SetScreenEnd(bool screen_end);
	Vector2D GetVelocity();
	void SetObjectType(eObjectType type);
};

