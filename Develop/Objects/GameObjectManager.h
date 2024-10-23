#pragma once

#include "../Singleton.h"
#include "GameObjectBase.h"

#include <vector>
#include <string>

class GameObjectManager : public Singleton<class T>
{
private:
	std::vector<GameObjectBase*> create_object;
	std::vector<GameObjectBase*> destroy_object;
	std::vector<GameObjectBase*> game_object;
	Vector2D screen_offset;

	//エラーがわからん
public:
	GameObjectManager();
	virtual ~GameObjectManager();

public:
	virtual void Initialize();

	virtual void Update(const float& delta_second);

	virtual void Draw() const;

	virtual void Finalize();

	virtual void CheckCreateObject();

	virtual void CheckDesroyObject();

	//virtual std::vector<GameObjectBase*>& CreateGameObject();

	template <class OBJECT>
	OBJECT* CreateObject(const Vector2D& generate_location)
	{
		// 生成するゲームオブジェクトクラスを動的確保
		OBJECT* new_instance = new OBJECT();
		// GameObjectBaseを継承しているか確認
		GameObjectBase* new_object = dynamic_cast<GameObjectBase*>(new_instance);
		// エラーチェック
		if (new_object == nullptr)
		{
			// 動的確保したメモリの開放
			delete new_instance;
			// 例外テキストを通知
			throw std::string("ゲームオブジェクトが生成できませんでした");
			return nullptr;
		}
		// シーン情報の設定
		new_object->SetOwnerScene(this);
		// オブジェクトの初期化
		new_object->Initialize();
		// 位置情報の設定
		new_object->SetLocation(generate_location);
		// 生成オブジェクトリストの末尾に格納する
		create_object.push_back(new_object);
		// 生成したゲームオブジェクトのポインタを返す
		return new_instance;
	}

	void DestroyGameObject(GameObjectBase* target);

public:
	virtual void CheckCollision(GameObjectBase* target, GameObjectBase* partner);

	const Vector2D GetScreenOffset() const;

private:
	void DestoryAllObject();

};
