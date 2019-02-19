#include "EditCursor.h"
#include "ImageMng.h"
#include "stdio.h"
#include "DxLib.h"
#include "GameTask.h"
#include "SceneState.h"

std::unique_ptr<GameTask, GameTask::GameTaskDeleter> GameTask::s_Instance(new GameTask());

GameTask::GameTask(): keyDataPub(keyData),keyDataOldPub(keyDataOld)		// �ް�Ӱ�ނ���ڲ԰�p���ݒ�
{
	SysInit();
	LpMapCtl->MapReset();
}

GameTask::~GameTask()
{
}

bool GameTask::AddObj(OBJ * obj)
{
	if (obj != nullptr)
	{
		objList.push_back(obj);			// obj�̖�����nullptr��ǉ�����
		return true;
	}
	return false;
}

void GameTask::Run()
{
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		memcpy(keyDataOld, keyData, sizeof(keyDataOld));
		GetHitKeyStateAll(keyData);
		scenePtr = scenePtr->Update(keyData, keyDataOld,std::move(scenePtr));
	}
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

//int GameTask::GameInit(void)
//{
//	LpMapCtl->MapReset();
//	SetOffset(Vector2(20, 20));
//	LpMapCtl->MapLoad();
//	return 1;
//}

void GameTask::GameDestroy(void)
{
	DeleteObjList();
}

//int GameTask::GameMain(void)
//{
//	// �ްт̏������ֈړ�
//	if (keyData[KEY_INPUT_F5] && !keyDataOld[KEY_INPUT_F5])
//	{
//		GameDestroy();
//		mode = GMODE_EDIT_INIT;
//		return 1;
//	}
//	LpMapCtl->FireUpdate();
//	for (auto itr = objList.begin(); itr != objList.end();)
//	{
//		if (!(*itr)->CheckActive())
//		{
//			delete (*itr);
//			itr = objList.erase(itr);		// �Ԃ�l�̈�������
//			continue;
//		}
//		itr++;
//	}
//	for (auto itr = objList.begin(); itr != objList.end(); itr++)
//	{
//		(*itr)->Update();
//		(*itr)->UpdateAnim();
//	}
//	ClsDrawScreen();
//	LpMapCtl->MapDraw();
//	// ��ڲ԰�̶��ق�`��
//	for (auto itr = objList.begin(); itr != objList.end(); itr++)
//	{
//		(*itr)->Draw();
//	}
//	ScreenFlip();
//	return 1;
//}
int GameTask::SysDestroy(void)
{
	DeleteObjList();
	return 1;
}

void GameTask::SetOffset(Vector2& pos)
{
	drawOffset = pos;
}

const Vector2& GameTask::GetOffset(void)
{
	return drawOffset;
}

//int GameTask::EditInit(void)
//{
//	LpMapCtl->MapReset();
//	SetOffset(Vector2(20, 20));
//	OBJ *tmp = new EditCursor(keyData,keyDataOld,GetOffset());				// �߲����ϐ��ɵ�޼ު�Ă̏�������
//	tmp->Init("image/map.png", Vector2(BLOCK_SIZE_X, BLOCK_SIZE_Y), Vector2(4,4), Vector2(3,3), 0);
//	AddObj(tmp);
//	return 1;
//}
//
//int GameTask::EditMain(void)
//{
//	// �ްт̏������ֈړ�
//	if (keyData[KEY_INPUT_F5] && !keyDataOld[KEY_INPUT_F5])
//	{
//		EditDestroy();
//		mode = GMODE_INIT;
//		return 1;
//	}
//	// ��ި���ް��̕ۑ�
//	if (keyData[KEY_INPUT_F1])
//	{
//		if (MessageBox(
//			GetMainWindowHandle(),					// ����޳������ق��擾����
//			"�G�f�B�b�g���e���Z�[�u���܂����H",		// ү�����ޯ����÷�ē��e
//			"�m�F�_�C�A���O",						// ү�����ޯ��������
//			MB_OKCANCEL) == IDOK)					// ү�����ޯ���̽���
//		{
//			LpMapCtl->MapSave();
//		}
//	}
//	// ��ި���ް��̓ǂݍ���
//	if (keyData[KEY_INPUT_F2])
//	{
//		if (MessageBox(
//			GetMainWindowHandle(),					// ����޳������ق��擾����
//			"�G�f�B�b�g���e�����[�h���܂����H",		// ү�����ޯ����÷�ē��e
//			"�m�F�_�C�A���O",						// ү�����ޯ��������
//			MB_OKCANCEL) == IDOK)					// ү�����ޯ���̽���
//		{
//			LpMapCtl->MapLoad();
//		}
//	}
//	// ���̴݂�ި�ē��e��S�Ĕj��
//	if (keyData[KEY_INPUT_DELETE])
//	{
//		if (MessageBox(
//			GetMainWindowHandle(),						// ����޳������ق��擾����
//			"���݂̃G�f�B�b�g���e��j�����܂����H",		// ү�����ޯ����÷�ē��e
//			"�m�F�_�C�A���O",							// ү�����ޯ��������
//			MB_OKCANCEL) == IDOK)						// ү�����ޯ���̽���
//		{
//			LpMapCtl->MapDelete();
//		}
//	}
//	// �ǂ�����єz�u
//	if (keyData[KEY_INPUT_SPACE])
//	{
//		if (MessageBox(
//			GetMainWindowHandle(),				// ����޳������ق��擾����
//			"�ǂ������_���ɔz�u���܂����H",		// ү�����ޯ����÷�ē��e
//			"�m�F�_�C�A���O",					// ү�����ޯ��������
//			MB_OKCANCEL) == IDOK)				// ү�����ޯ���̽���
//		{
//			LpMapCtl->MapRandom();
//		}
//	}
//	
//	for (auto itr : objList)
//	{
//		itr->Update();
//	}
//	
//	
//	ClsDrawScreen();
//	
//	for (auto itr : objList)
//	{
//		itr->Draw();
//	}
//	
//	LpMapCtl->MapDraw();			// ϯ��ID�̕`��
//	Vector2 pos1 = GetOffset();		// ���̎n�_�p�̕ϐ�
//	Vector2 pos2(0, 0);				// ���̏I�_�p�̕ϐ�
//
//	// �����̕`��
//	for (; pos1.x < SCREEN_SIZE_X; pos1.x += BLOCK_SIZE_X)
//	{
//		pos2 = Vector2(pos1.x, SCREEN_SIZE_Y - GetOffset().x);
//		DrawLine(pos1, pos2, 0x8c8c8c
//		);
//	}
//
//	pos1 = Vector2(SCREEN_SIZE_X - GetOffset().x, 0);			// ���̎n�_�̒���������������
//	// �c���̕`��
//	for (; pos1.y < SCREEN_SIZE_Y; pos1.y += BLOCK_SIZE_Y)
//	{
//		pos2 = Vector2(GetOffset().x, pos1.y);
//		DrawLine(pos1, pos2, 0x8c8c8c);
//	}
//	ScreenFlip();
//	return 1;
//}

void GameTask::EditDestroy(void)
{
	DeleteObjList();
}

void GameTask::DeleteObjList(void)
{
	for (auto itr : objList)
	{
		delete itr;
	}
	
	objList.clear();			// ϯ���ް��̏�����������
}

// ���̕`��p�֐�
int DrawLine(const Vector2& pos1, const Vector2& pos2, unsigned int Color)
{
	DrawLine(pos1.x, pos1.y, pos2.x, pos2.y, 0x8c8c8c);	// (140,140,140)
	return 0;
}