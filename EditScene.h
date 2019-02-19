#pragma once
#include "SceneState.h"
class EditScene :
	public SceneState
{
public:
	EditScene();
	~EditScene();
	void Init();
	unique_scene Update(const char(&keyData)[256], const char(&keyDataOld)[256], unique_scene scene);
	SCENE GetMode();
};

