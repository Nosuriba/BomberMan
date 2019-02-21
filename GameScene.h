#pragma once
#include "SceneState.h"

class OBJ;

class GameScene :
	public SceneState
{
public:
	GameScene(const char(&keyData)[256], const char(&keyDataOld)[256]);
	~GameScene();
	void Init();
	unique_scene Update(unique_scene scene);
	Vector2 GetOffset();
private:
	void DeleteObjList();
	const char(&keyData)[256];
	const char(&keyDataOld)[256];
	Vector2 offset;
};

