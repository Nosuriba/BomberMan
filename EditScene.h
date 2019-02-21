#pragma once
#include "SceneState.h"
class EditScene :
	public SceneState
{
public:
	EditScene(const char(&keyData)[256], const char(&keyDataOld)[256]);
	~EditScene();
	void Init();
	unique_scene Update(unique_scene scene);
	Vector2 GetOffset();
private:
	void DeleteObjList();
	const char(&keyData)[256];
	const char(&keyDataOld)[256];
	Vector2 offset;
};

