#pragma once

#include "../SceneBase.h"

class TitleScene : public SceneBase
{
private:
	int back_ground;

public:
	TitleScene();
	~TitleScene();

public:
	void Initialize()override;
	eSceneType Update(float delta_second)override;
	void Draw()override;
	void Finalize()override;

	// ���݂̃V�[���^�C�v�����擾����
	const eSceneType GetNowSceneType() const override;
};

