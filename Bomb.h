#pragma once
#include "OBJ.h"

#define LIM_EXP_TIME	(60*3)
#define LIM_STAY_TIME	(60*3)
#define BOMB_FIR_TIME	(20)

// �����̕���
enum BOMB_DIR
{
	MOVE_DIR_DOWN,
	MOVE_DIR_LEFT,
	MOVE_DIR_RIGHT,
	MOVE_DIR_UP,
	MOVE_DIR_MAX
};

// ���e�̏��
enum BOMB_ST {
	BOMB_NON,		// ���e(�Ȃ�)
	BOMB_DEF,		// �ʏ�
	BOMB_FIR,		// ���j��
	BOMB_END,		// ���e(���j�I��)
	BOMB_MAX
};
class Bomb :
	public OBJ
{
public:
	Bomb(const char(&_keyDataPub)[256], const char(&_keyDataOldPub)[256], Vector2 offSet, unsigned int _range);
	~Bomb();
private:
	// void SetRange(unsigned int _range);
	void SetMove(void);
	void UpdateAnim(void);
	BOMB_ST state;
	BOMB_ST old_state;
	int expTime = 0;
	unsigned int range;						// ���e�̈З�
	unsigned int fireLength[MOVE_DIR_MAX];	// �����͈̔�
	bool fireFlag[MOVE_DIR_MAX];			// �������׸�
};

