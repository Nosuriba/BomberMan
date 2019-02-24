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
	virtual void Init(SCENE mode)	= 0;
	virtual unique_scene Update(unique_scene scene) = 0;
	virtual SCENE GetMode()			= 0;
	virtual Vector2 GetOffset()		= 0;
};

/// �Ƃ肠�����A�L�[����̕������C�����Ă���