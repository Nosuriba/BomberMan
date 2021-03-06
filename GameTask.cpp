#include "stdio.h"
#include "DxLib.h"
#include "EditScene.h"
#include "EditCursor.h"
#include "ImageMng.h"
#include "GameTask.h"

std::unique_ptr<GameTask, GameTask::GameTaskDeleter> GameTask::s_Instance(new GameTask());

GameTask::GameTask(): keyDataPub(keyData),keyDataOldPub(keyDataOld), 
mapSize((SCREEN_SIZE_X / CHIP_SIZE) - 2, (SCREEN_SIZE_Y / CHIP_SIZE) - 2)
{
	SysInit();
}

GameTask::~GameTask()
{
}

int GameTask::SysInit(void)
{
	// ｼｽﾃﾑ処理
	SetGraphMode(SCREEN_SIZE_X, SCREEN_SIZE_Y, 16);		// 65536色ﾓｰﾄﾞに設定
	ChangeWindowMode(true);								// true:window　false:ﾌﾙｽｸﾘｰﾝ
	SetWindowText("Bomberman_Cplus:GSC1_1701310_北川 潤一");
	if (DxLib_Init() == -1) return false;				// DXﾗｲﾌﾞﾗﾘ初期化処理
	SetDrawScreen(DX_SCREEN_BACK);						// ひとまずﾊﾞｯｸﾊﾞｯﾌｧに描画

	return true;
}

void GameTask::Run()
{
	mode = SCENE::EDIT;
	scenePtr = std::make_unique<EditScene>(keyData, keyDataOld);
	scenePtr->Init(mode);
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		if (mode != scenePtr->GetMode())
		{
			mode = scenePtr->GetMode();
			scenePtr->Init(mode);
		}
		memcpy(keyDataOld, keyData, sizeof(keyDataOld));
		GetHitKeyStateAll(keyData);
		offset = scenePtr->GetOffset();
		scenePtr = scenePtr->Update(std::move(scenePtr));
	}
}

const Vector2& GameTask::GetOffset(void)
{
	return offset;
}

void GameTask::SetMode(const SCENE mode)
{
	this->mode = mode;
}

const SCENE GameTask::GetMode()
{
	return mode;
}

const Vector2 GameTask::GetMapSize()
{
	return mapSize;
}

bool GameTask::AddObj(OBJ * obj)
{
	if (obj != nullptr)
	{
		objList.push_back(obj);			// objの末尾にnullptrを追加する
		return true;
	}
	return false;
}

std::list<OBJ*> GameTask::GetObj()
{
	return objList;
}

void GameTask::SetObj(std::list<OBJ*> objList)
{
	this->objList = objList;
}

void GameTask::DeleteObjList()
{
	for (auto itr : objList)
	{
		delete itr;
	}
	objList.clear();
}

// 線の描画用関数
int DrawLine(const Vector2& pos1, const Vector2& pos2, unsigned int Color)
{
	DrawLine(pos1.x, pos1.y, pos2.x, pos2.y, 0x8c8c8c);	// (140,140,140)
	return 0;
}