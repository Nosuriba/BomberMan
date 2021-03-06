#pragma once
#include "SceneState.h"
class EditScene :
	public SceneState
{
public:
	EditScene(const char(&keyData)[256], const char(&keyDataOld)[256]);
	~EditScene();
	void Init(SCENE mode);
	unique_scene Update(unique_scene scene);
	SCENE GetMode();
	Vector2 GetOffset();
private:
	const char(&keyData)[256];
	const char(&keyDataOld)[256];
	Vector2 offset;
	std::list<OBJ*> objList;
};

