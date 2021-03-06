#pragma once
#include "OBJ.h"

#define LIM_EXP_TIME	(60*3)
#define LIM_STAY_TIME	(60*3)
#define BOMB_FIR_TIME	(20)

// Μϋό
enum BOMB_DIR
{
	MOVE_DIR_DOWN,
	MOVE_DIR_LEFT,
	MOVE_DIR_RIGHT,
	MOVE_DIR_UP,
	MOVE_DIR_MAX
};

// eΜσΤ
enum BOMB_ST {
	BOMB_NON,		// e(Θ΅)
	BOMB_DEF,		// Κν
	BOMB_FIR,		// j
	BOMB_END,		// e(jIΉ)
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
	unsigned int range;						// eΜΠΝ
	unsigned int fireLength[MOVE_DIR_MAX];	// ΜΝΝ
	bool fireFlag[MOVE_DIR_MAX];			// ΜΜΧΈή
};

