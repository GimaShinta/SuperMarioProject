#pragma once

//�C���N���[�h
#include "../Singleton.h"
#include <string>

//�}�N����`
#define	D_SUCCESS		(0)		// ����
#define	D_FAILURE		(-1)	// ���s

#define D_WIN_MAX_X		(672)	// �X�N���[���T�C�Y�i���j
#define D_WIN_MAX_Y		(864)	// �X�N���[���T�C�Y�i�����j
#define D_COLOR_BIT		(32)	// �J���[�r�b�g

//�v���g�^�C�v�錾
class Application : public Singleton<class T>
{
private:
	bool end_check;

public:
	Application();
	~Application();

	void WakeUp();
	void Run();
	void ShutDown();

private:
	void Graph()const;

public:
	void FreamControl();
	const float& GetDeltaSecond();
	int ErrorThrow(std::string error_log);
};

