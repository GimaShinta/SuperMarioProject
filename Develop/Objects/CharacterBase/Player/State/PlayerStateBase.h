#pragma once

#include "../../../../Utility/Vector2D.h"

#include "../Player.h"
#include "Enum/PlayerState.h"

/// <summary>
/// �v���C���[��ԊǗ��p�̃x�[�X�N���X
/// </summary>
class PlayerStateBase
{
protected:
	//�v���C���[���
	class Player* player;
	Vector2D old_location;

public:
	PlayerStateBase(class Player* p) :player(p)
	{
	}

	virtual ~PlayerStateBase() = default;

public:
	virtual void Initialize() = 0;
	virtual void Finalize() = 0;
	virtual void Update() = 0;
	virtual void Draw() const = 0;

public:
	virtual ePlayerLooksState GetLooksState() const = 0;
	virtual ePlayerState GetState() const = 0;
};