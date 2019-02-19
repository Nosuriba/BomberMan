#pragma once
#include "SceneState.h"

class GameScene :
	public SceneState
{
public:
	GameScene();
	~GameScene();
	void Init();
	unique_scene Update(const char(&keyData)[256], const char(&keyDataOld)[256], unique_scene scene);
	SCENE GetMode();
};

