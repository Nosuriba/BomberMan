#include "SceneState.h"

SceneState::~SceneState()
{
}

void SceneState::DeleteObjList()
{
	for (auto itr : objList)
	{
		delete itr;
	}
	objList.clear();			// Ï¯ÌßÃŞ°À‚Ìî•ñ‚ğÁ‹‚·‚é
}
