#pragma once

template <class T>
class Singleton
{
protected:
	// クラスの実体をメンバ関数内でしか生成できないようにする
	Singleton() = default;

	// コピーガード
	Singleton(const Singleton&) = delete;
	Singleton& operator = (const Singleton&) = delete;
	// ~コピーガード

	~Singleton() = default;

public:
	static T* GetInstance();
	static T* DeleteInstance();

};

template<class T>
inline T* Singleton<T>::GetInstance()
{
	// インスタンスが生成されていない場合、生成する
	if (instance == nullptr)
	{
		instance = new T();
	}

	// インスタンスのポインタを返却する
	return instance;
}

template<class T>
inline T* Singleton<T>::DeleteInstance()
{
	// インスタンスが存在している場合、削除する
	if (instance != nullptr)
	{
		delete instance;
		instance = nullptr;
	}
}
