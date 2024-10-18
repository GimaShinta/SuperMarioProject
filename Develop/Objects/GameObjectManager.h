#pragma once

#include "../Singleton.h"
#include "GameObjectBase.h"
#include <vector>

class GameObjectManager : public Singleton
{
private:
	std::vector<GameObjectBase*> create_object;
	std::vector<GameObjectBase*> destroy_object;
	std::vector<GameObjectBase*> game_object;

public:
	void Initialize();
	void Update();
	void Finalize();
	void CheckCreateObject();
	void CheckDesroyObject();
	std::vector<GameObjectBase*> CreateGameObject();

private:
	void DestroyGameObject(GameObjectBase*);;
	void CheckCollision(GameObjectBase* a, GameObjectBase* b);
};

