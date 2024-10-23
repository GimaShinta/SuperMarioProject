#pragma once

#include "../Singleton.h"

enum eObjectType
{
	eNone,
	ePlayer,
	eFireball,
	eEnemy,
	eGround,
	eItem
};

class Collision : public Singleton<class T>
{
};

