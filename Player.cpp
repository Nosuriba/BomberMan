#include "Player.h"
#include "GameTask.h"
#include "MapCtl.h"
#include "Bomb.h"
#include "DxLib.h"

Player::Player(const char(&_keyData)[256],const char(&_keyDataOld)[256], Vector2 offSet) :OBJ(_keyData, _keyDataOld, offSet)
{
}

Player::~Player()
{
}

void Player::SetMove(void)
{
	// ���߻��ނ̑傫���Ŋ���؂�Ȃ��ꍇ
	if (!(pos.x % LpMapCtl.GetChipSize().x)
	&&  !(pos.y % LpMapCtl.GetChipSize().y))
	{
		if (keyData[KEY_INPUT_Z] && !keyDataOld[KEY_INPUT_Z])
		{
			OBJ *tmp;
			tmp = new Bomb (LpGameTask.keyDataPub,
							LpGameTask.keyDataOldPub,
							LpGameTask.GetOffset(),
							BombRange);
			tmp->Init("image/bomb.png", Vector2(40 / 2, 140 / 7), Vector2(2, 7), Vector2(0, 0), 2);
			tmp->setPos(pos);
			LpMapCtl.SetMapData(MAP_BOMB, pos);
			LpGameTask.AddObj(tmp);
		}
		// �E�����̈ړ�(����)
		if (keyData[KEY_INPUT_LEFT])
		{
			moveID = KEY_INPUT_LEFT;
			drawDir = DIR_LEFT;
		}
		// �������̈ړ�(����)
		else if (keyData[KEY_INPUT_RIGHT])
		{
			moveID = KEY_INPUT_RIGHT;
			drawDir = DIR_RIGHT;
		}
		else
		{
			// ������̈ړ�(����)
			if (keyData[KEY_INPUT_UP])
			{
				moveID = KEY_INPUT_UP;
				drawDir = DIR_UP;
			}
			// �������̈ړ�(����)
			else if (keyData[KEY_INPUT_DOWN])
			{
				moveID = KEY_INPUT_DOWN;
				drawDir = DIR_DOWN;
			}
			else
			{
				moveID = 0;
			}
		}
	}
	if (moveID)
	{
		switch (LpMapCtl.GetMapData(pos, drawDir))
		{
		case MAP_WALL1:
		case MAP_WALL2:
		case MAP_BLOCK:
		case MAP_BOMB:
			moveID = 0;
			break;
		case MAP_ITEM_SHOSE:
			// ����(��߰�ޱ���) [�o�O����(�E)(��)]
			LpMapCtl.SetMapData(MAP_NON, pos);
			if (pos.x % LpMapCtl.GetChipSize().x >= 0)
			{
				LpMapCtl.SetMapData(MAP_NON, Vector2(pos.x + chipOffset.x, pos.y));
			}
			else if (pos.y % LpMapCtl.GetChipSize().y >= 0)
			{
				LpMapCtl.SetMapData(MAP_NON, Vector2(pos.x, pos.y + chipOffset.y));
			}
			if (speed <= PLAYER_DEF_SPEED)
			{
				speed += 2;
				animSpeed = animSpeed / 2;
			}
			break;
		case MAP_FIRE:
			// ��ڲ԰�̎��S����
			if ((pos.x % LpMapCtl.GetChipSize().x == 0)
			&& (pos.y % LpMapCtl.GetChipSize().y == 0))
			{
				active = false;
			}
			break;
		case MAP_EDIT_EM1:
		case MAP_EDIT_EM2:
			active = false;
			break;
		default:
			break;
		}
	}
	// ��ڲ԰�̕��s��Ұ��ݗp
	state = ST_WALK;
	switch (moveID)
	{
	case KEY_INPUT_LEFT:
		pos.x -= speed;
		break;
	case KEY_INPUT_RIGHT:
		pos.x += speed;
		break;
	case KEY_INPUT_UP:
		pos.y -= speed;
		break;
	case KEY_INPUT_DOWN:
		pos.y += speed;
		break;
	default:
		state = ST_STAND;
	}
}