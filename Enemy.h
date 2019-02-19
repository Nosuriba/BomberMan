#pragma once
#include "OBJ.h"

#define MOVE_TIME_CNT (60)
class Enemy :
	public OBJ
{
public:
	Enemy(const char(&_keyData)[256], const char(&_keyDataOld)[256], Vector2 offSet);
	~Enemy();
private:
	void SetMove(void);
	DRAW_DIR moveID;
	int timeCnt = MOVE_TIME_CNT;
};

