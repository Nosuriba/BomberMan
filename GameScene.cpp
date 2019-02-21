#include <DxLib.h>
#include "GameScene.h"
#include "EditScene.h"
#include "EditCursor.h"
#include "MapCtl.h"

GameScene::GameScene(const char(&_keyData)[256], const char(&_keyDataOld)[256]) : 
	keyData(_keyData), keyDataOld(_keyDataOld)
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

unique_scene GameScene::Update(unique_scene scene)
{
	// ¹Ş°Ñ‚Ì‰Šú‰»‚ÖˆÚ“®
	if (keyData[KEY_INPUT_F5] && !keyDataOld[KEY_INPUT_F5])
	{
		DeleteObjList();
		return std::make_unique<EditScene>(keyData, keyDataOld);
	}
	LpMapCtl.FireUpdate();
	for (auto itr = objList.begin(); itr != objList.end();)
	{
		if (!(*itr)->CheckActive())
		{
			delete (*itr);
			itr = objList.erase(itr);		// •Ô‚è’l‚Ìˆê‚Âæ‚ğÁ‚·
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
	// ÌßÚ²Ô°‚Ì¶°¿Ù‚ğ•`‰æ
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
		objList.push_back(obj);			// obj‚Ì––”ö‚Énullptr‚ğ’Ç‰Á‚·‚é
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
	objList.clear();			// Ï¯ÌßÃŞ°À‚Ìî•ñ‚ğÁ‹‚·‚é
}
