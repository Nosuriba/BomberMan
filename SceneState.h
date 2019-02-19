#pragma once
#include <list>
#include <memory>
#include "Vector2.h"

// �Q�[���V�[���̃X�e�[�^�X�p
enum class SCENE
{
	EDIT,
	MAIN,
	MAX
};

class OBJ;
class SceneState;

using unique_scene = std::unique_ptr<SceneState>;

class SceneState
{
public:
	virtual ~SceneState();
	virtual void Init()				= 0;
	virtual unique_scene Update(char(&_keyData)[256], char(&_keyDataOld)[256], unique_scene scene) = 0;
	virtual SCENE GetMode()			= 0;
	virtual Vector2 GetOffset()		= 0;
	virtual bool AddObj(OBJ * obj)  = 0;
protected:
	void DeleteObjList();
	const char(&keyData)[256];
	const char(&keyDataOld)[256];
	std::list<OBJ*>	objList;
	Vector2 offset;
};