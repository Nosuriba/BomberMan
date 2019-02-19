#pragma once
#include "OBJ.h"

#define PLAYER_DEF_SPEED (2)
#define BOMB_SWITCH_CNT	 (20)
class Player :
	public OBJ
{
public:
	Player(const char(&_keyData)[256], const char(&_keyDataOld)[256], Vector2 offSet);
	~Player();
private:
	void SetMove(void);
	int expTime;
	unsigned int moveID;
	unsigned int BombRange;
};

