#pragma once
#include <list>
#include <memory>
#include "Vector2.h"

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

	virtual void Init()				= 0;
	virtual unique_scene Update(unique_scene scene) = 0;
	virtual Vector2 GetOffset()		= 0;
};

/// とりあえず、キー操作の部分を修正していく