#include "stdio.h"
#include "DxLib.h"
#include "EditScene.h"
#include "EditCursor.h"
#include "ImageMng.h"
#include "GameTask.h"

std::unique_ptr<GameTask, GameTask::GameTaskDeleter> GameTask::s_Instance(new GameTask());

GameTask::GameTask(): keyDataPub(keyData),keyDataOldPub(keyDataOld)		// �ް�Ӱ�ނ���ڲ԰�p���ݒ�
{
	SysInit();
	LpMapCtl->MapReset();
}

GameTask::~GameTask()
{
}

int GameTask::SysInit(void)
{
	// ���я���
	SetGraphMode(SCREEN_SIZE_X, SCREEN_SIZE_Y, 16);		// 65536�FӰ�ނɐݒ�
	ChangeWindowMode(true);								// true:window�@false:�ٽ�ذ�
	SetWindowText("Bomberman_Cplus:GSC1_1701310_�k�� ����");
	if (DxLib_Init() == -1) return false;				// DXײ���؏���������
	SetDrawScreen(DX_SCREEN_BACK);						// �ЂƂ܂��ޯ��ޯ̧�ɕ`��

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

// ���̕`��p�֐�
int DrawLine(const Vector2& pos1, const Vector2& pos2, unsigned int Color)
{
	DrawLine(pos1.x, pos1.y, pos2.x, pos2.y, 0x8c8c8c);	// (140,140,140)
	return 0;
}