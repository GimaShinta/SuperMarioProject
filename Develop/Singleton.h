#pragma once

template <class T>
class Singleton
{
protected:
	// �N���X�̎��̂������o�֐����ł��������ł��Ȃ��悤�ɂ���
	Singleton() = default;

	// �R�s�[�K�[�h
	Singleton(const Singleton&) = delete;
	Singleton& operator = (const Singleton&) = delete;
	// ~�R�s�[�K�[�h

	~Singleton() = default;

public:
	static T* GetInstance();
	static T* DeleteInstance();

};

template<class T>
inline T* Singleton<T>::GetInstance()
{
	// �C���X�^���X����������Ă��Ȃ��ꍇ�A��������
	if (instance == nullptr)
	{
		instance = new T();
	}

	// �C���X�^���X�̃|�C���^��ԋp����
	return instance;
}

template<class T>
inline T* Singleton<T>::DeleteInstance()
{
	// �C���X�^���X�����݂��Ă���ꍇ�A�폜����
	if (instance != nullptr)
	{
		delete instance;
		instance = nullptr;
	}
}
