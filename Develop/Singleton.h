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
	//インスタンスの取得
	static T* GetInstance();

};

//インスタンスの取得
template<class T>
inline T* Singleton<T>::GetInstance()
{
	static T* instance = nullptr;

	// インスタンスが生成されていない場合、生成する
	if (instance == nullptr)
	{
		instance = new T();
	}

	// インスタンスのポインタを返却する
	return instance;
}