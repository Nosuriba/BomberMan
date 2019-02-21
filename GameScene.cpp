#include <DxLib.h>
#include "GameScene.h"
#include "EditScene.h"
#include "EditCursor.h"
#include "MapCtl.h"

GameScene::GameScene()
{
	Init();
}


GameScene::~GameScene()
{
}

void GameScene::Init()
{
	LpMapCtl.MapReset();
	offset = {20,20};
	LpMapCtl.MapLoad();
}

unique_scene GameScene::Update(const char(&keyData)[256], const char(&keyDataOld)[256], unique_scene scene)
{
	// �ްт̏������ֈړ�
	if (keyData[KEY_INPUT_F5] && !keyDataOld[KEY_INPUT_F5])
	{
		DeleteObjList();
		return std::make_unique<EditScene>();
	}
	LpMapCtl.FireUpdate();
	for (auto itr = objList.begin(); itr != objList.end();)
	{
		if (!(*itr)->CheckActive())
		{
			delete (*itr);
			itr = objList.erase(itr);		// �Ԃ�l�̈�������
			continue;
		}
		itr++;
	}
	for (auto itr = objList.begin(); itr != objList.end(); itr++)
	{
		(*itr)->Update();
		(*itr)->UpdateAnim();
	}
	ClsDrawScreen();
	LpMapCtl.MapDraw();
	// ��ڲ԰�̶��ق�`��
	for (auto itr = objList.begin(); itr != objList.end(); itr++)
	{
		(*itr)->Draw();
	}
	ScreenFlip();
	return scene;
}

Vector2 GameScene::GetOffset()
{
	return offset;
}

SCENE GameScene::GetMode()
{
	return SCENE::MAIN;
}

bool GameScene::AddObj(OBJ * obj)
{
	if (obj != nullptr)
	{
		objList.push_back(obj);			// obj�̖�����nullptr��ǉ�����
		return true;
	}
	return false;
}

void GameScene::DeleteObjList()
{
	for (auto itr : objList)
	{
		delete itr;
	}
	objList.clear();			// ϯ���ް��̏�����������
}
