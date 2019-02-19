#include "Player.h"
#include "Bomb.h"
#include "GameTask.h"
#include "MapCtl.h"

Bomb::Bomb(const char(&_keyData)[256], const char(&_keyDataOld)[256], Vector2 offSet, unsigned int _range) :OBJ(_keyData, _keyDataOld, offSet)
{
	state		= BOMB_DEF;
	old_state	= BOMB_MAX;	
	range		= _range;
	for (int no = 0; no < MOVE_DIR_MAX; no++)
	{
		fireLength[no] = 0;
		fireFlag[no] = true;
	}
}

Bomb::~Bomb()
{
	LpMapCtl->SetMapData(MAP_NON, pos);
}

void Bomb::SetMove(void)
{
	old_state = state;
	expTime++;
	switch(state)
	{
	case BOMB_NON:
		break;
	case BOMB_DEF:
		if (expTime >= LIM_EXP_TIME)
		{
			state = BOMB_FIR;			
			expTime = 0;
		}
		break;
	case BOMB_FIR:
		LpMapCtl->SetFireData(MOVE_DIR_UP,		Vector2(pos.x, pos.y - fireLength[MOVE_DIR_UP] * LpGameTask.chipSize.y));
		LpMapCtl->SetFireData(MOVE_DIR_DOWN,	Vector2(pos.x, pos.y + fireLength[MOVE_DIR_DOWN] * LpGameTask.chipSize.y));
		LpMapCtl->SetFireData(MOVE_DIR_LEFT,	Vector2(pos.x - fireLength[MOVE_DIR_LEFT] * LpGameTask.chipSize.x, pos.y));
		LpMapCtl->SetFireData(MOVE_DIR_RIGHT,	Vector2(pos.x + fireLength[MOVE_DIR_RIGHT] * LpGameTask.chipSize.x, pos.y));
		if (!(expTime % BOMB_FIR_TIME))
		{
			// ”š•—‚Ìˆ—(4•ûŒü)
			for (int no = 0; no < MOVE_DIR_MAX; no++)
			{
				if (fireLength[no])
				{
					fireLength[no]++;
					if (fireLength[no] >= range)
					{
						fireLength[no] = false;
					}
				}
			}
		}
		state = BOMB_END;
		for (int no = 0; no < MOVE_DIR_MAX; no++)
		{
			// ”š•—‚ªc‚Á‚Ä‚¢‚½ê‡
			if (fireLength[no])
			{
				state = BOMB_FIR;
				break;
			}
		}
		break;
	case BOMB_END:
		active = false;
		break;
	default:
		state = BOMB_END;
		break;
	}
}

void Bomb::UpdateAnim(void)
{
	// ”š’e‚Ìó‘Ô‚ªˆá‚Á‚½ê‡
	if (state != old_state)
	{
		animCnt = 0;
	}
	else
	{
		animCnt++;
	}
	switch (state)
	{
	case BOMB_DEF:
		chipOffset.x = 0;
		chipOffset.y = ((animCnt / animSpeed) % 2);
		break;
	case BOMB_FIR:
		chipOffset.x = 1;
		chipOffset.y = (animCnt / animSpeed);
		if (chipOffset.y >= divCnt.y)
		{
			// ”š’e‚Ìíœ
			chipOffset.x = 0;
			chipOffset.y = 2;
		}
		break;
	case BOMB_NON:
	case BOMB_END:
		// ”š’e‚Ìíœ
		chipOffset.x = 0;
		chipOffset.y = 2;
		break;
	default:
		break;
	}
}
