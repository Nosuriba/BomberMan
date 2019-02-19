#include "stdio.h"
#include "DxLib.h"
#include "EditScene.h"
#include "EditCursor.h"
#include "ImageMng.h"
#include "GameTask.h"

std::unique_ptr<GameTask, GameTask::GameTaskDeleter> GameTask::s_Instance(new GameTask());

GameTask::GameTask(): keyDataPub(keyData),keyDataOldPub(keyDataOld)		// ¹Ş°ÑÓ°ÄŞ‚ÌÌßÚ²Ô°—p·°İ’è
{
	SysInit();
	LpMapCtl->MapReset();
}

GameTask::~GameTask()
{
}

int GameTask::SysInit(void)
{
	// ¼½ÃÑˆ—
	SetGraphMode(SCREEN_SIZE_X, SCREEN_SIZE_Y, 16);		// 65536FÓ°ÄŞ‚Éİ’è
	ChangeWindowMode(true);								// true:window@false:ÌÙ½¸Ø°İ
	SetWindowText("Bomberman_Cplus:GSC1_1701310_–kì ˆê");
	if (DxLib_Init() == -1) return false;				// DX×²ÌŞ×Ø‰Šú‰»ˆ—
	SetDrawScreen(DX_SCREEN_BACK);						// ‚Ğ‚Æ‚Ü‚¸ÊŞ¯¸ÊŞ¯Ì§‚É•`‰æ

	return true;
}

void GameTask::Run()
{
	scenePtr = std::make_unique<EditScene>();
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		memcpy(keyDataOld, keyData, sizeof(keyDataOld));
		GetHitKeyStateAll(keyData);
		scenePtr = scenePtr->Update(keyData, keyDataOld,std::move(scenePtr));
	}
}

const Vector2& GameTask::GetOffset(void)
{
	return scenePtr->GetOffset();
}

const SCENE GameTask::GetMode()
{
	return scenePtr->GetMode();
}

void GameTask::SetObj(OBJ * obj)
{
	scenePtr->AddObj(obj);
}

// ü‚Ì•`‰æ—pŠÖ”
int DrawLine(const Vector2& pos1, const Vector2& pos2, unsigned int Color)
{
	DrawLine(pos1.x, pos1.y, pos2.x, pos2.y, 0x8c8c8c);	// (140,140,140)
	return 0;
}