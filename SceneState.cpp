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
	objList.clear();			// ﾏｯﾌﾟﾃﾞｰﾀの情報を消去する
}
