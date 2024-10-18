#pragma once

#include "../SceneBase.h"

class ResultScene : public SceneBase
{
private:
	class Player* player_zanki;

private:
	int back_ground;
	int player_zanki;

public:
	ResultScene();
	~ResultScene();

public:
	void Initialize();
	eSceneType Update(const float& delta_second);
	void Draw();
	void Finalize();

	// ���݂̃V�[���^�C�v�����擾����
	const eSceneType GetNowSceneType() const override;
};
