#pragma once
#include "OBJ.h"

#define  F_LIM_EXP_TIME (60*3)
class Fire :
	public OBJ
{
public:
	Fire(const char(&_keyData)[256], const char(&_keyDataOld)[256], VECTOR2 offSet);
	~Fire();
private:
	void setMove(void);
	int expTime		= F_LIM_EXP_TIME;
	int animSpeed	= 0;
	int animCnt		= 2;
};

