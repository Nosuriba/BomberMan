#include "Fire.h"
#include "mapCtl.h"


Fire::Fire(const char(&_keyData)[256], const char(&_keyDataOld)[256], VECTOR2 offSet) :OBJ(_keyData, _keyDataOld, offSet)
{
}

Fire::~Fire()
{
}

void Fire::setMove(void)
{
	if (expTime > 0)
	{
		expTime--;
	}
	else
	{
		active = false;
		lpMapCtl->setMapData(MAP_NON, pos);
	}
}
