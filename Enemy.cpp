#include "Enemy.h"
#include "GameTask.h"
#include "MapCtl.h"

Enemy::Enemy(const char(&_keyData)[256], const char(&_keyDataOld)[256], Vector2 offSet) :OBJ(_keyData, _keyDataOld, offSet)
{
	moveID = (DRAW_DIR)(MOVE_DIR_RIGHT);
}


Enemy::~Enemy()
{
}

void Enemy::SetMove(void)
{
	if (!(pos.x % LpMapCtl.GetChipSize().x)
	&&  !(pos.y % LpMapCtl.GetChipSize().y))
	{
		if (timeCnt > MOVE_TIME_CNT / 2)
		{
			moveID = (DRAW_DIR)(MOVE_DIR_RIGHT);
		}
		else
		{
			moveID = DIR_DERTH;
		}
	}
	// 状態判定処理
	switch (LpMapCtl.GetMapData(pos, moveID))
	{
	case MAP_WALL1:
	case MAP_WALL2:
	case MAP_BLOCK:
	case MAP_BOMB:
	case MAP_EDIT_EM1:
	case MAP_EDIT_EM2:
	case MAP_ITEM_BOMB:
	case MAP_ITEM_SHOSE:
	case MAP_ITEM_FIRE:
	case MAP_ITEM_SWITCH:
		moveID = (DRAW_DIR)(GetRand(DIR_MAX - 1) % DIR_DERTH);
		break;
	case MAP_FIRE:
		// 敵の死亡処理
		if ((pos.x % LpMapCtl.GetChipSize().x == 0)
		&& (pos.y % LpMapCtl.GetChipSize().y == 0))
		{
			active = false;
		}
		break;
	default:
		break;
	}
	state = ST_WALK;
	timeCnt--;
	// 移動処理
	switch (LpMapCtl.GetMapData(pos, moveID))
	{
	case MAP_FLOOR1:
	case MAP_FLOOR2:
	case MAP_NON:
		switch (moveID)
		{
		case DIR_LEFT:
			drawDir = DIR_LEFT;
			pos.x -= speed;
			break;
		case DIR_RIGHT:
			drawDir = DIR_RIGHT;
			pos.x += speed;
			break;
		case DIR_UP:

			drawDir = DIR_UP;
			pos.y -= speed;
			break;
		case DIR_DOWN:
			drawDir = DIR_DOWN;
			pos.y += speed;
			break;
		default:
			state = ST_STAND;
			break;
		}
		break;
	default:
		break;
	}
	// 移動制御
	if (timeCnt == 0)
	{
		timeCnt = MOVE_TIME_CNT;
	}
}
