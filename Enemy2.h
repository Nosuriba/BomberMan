#pragma once
#include "OBJ.h"
#include "Enemy.h"
class Enemy2 :
	public OBJ
{
public:
	Enemy2(const char(&_keyData)[256], const char(&_keyDataOld)[256], Vector2 offSet);
	~Enemy2();
private:
	void SetMove(void);
	DRAW_DIR moveID;
};

