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
	objList.clear();			// ϯ���ް��̏�����������
}
