#pragma once
#include <list>
#include <memory>

// ゲームシーンのステータス用
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
	virtual void Init() = 0;
	virtual unique_scene Update(const char(&_keyData)[256], const char(&_keyDataOld)[256], unique_scene scene) = 0;
	virtual SCENE GetMode() = 0;
protected:
	const char(&keyData)[256];
	const char(&keyDataOld)[256];
	std::list<OBJ*>	objList;
};