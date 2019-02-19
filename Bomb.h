#pragma once
#include "OBJ.h"

#define LIM_EXP_TIME	(60*3)
#define LIM_STAY_TIME	(60*3)
#define BOMB_FIR_TIME	(20)

// ”š•—‚Ì•ûŒü
enum BOMB_DIR
{
	MOVE_DIR_DOWN,
	MOVE_DIR_LEFT,
	MOVE_DIR_RIGHT,
	MOVE_DIR_UP,
	MOVE_DIR_MAX
};

// ”š’e‚Ìó‘Ô
enum BOMB_ST {
	BOMB_NON,		// ”š’e(‚È‚µ)
	BOMB_DEF,		// ’Êí
	BOMB_FIR,		// ”š”j’†
	BOMB_END,		// ”š’e(”š”jI—¹)
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
	unsigned int range;						// ”š’e‚ÌˆĞ—Í
	unsigned int fireLength[MOVE_DIR_MAX];	// ”š•—‚Ì”ÍˆÍ
	bool fireFlag[MOVE_DIR_MAX];			// ”š•—‚ÌÌ×¸Ş
};

