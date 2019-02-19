#include <DxLib.h>
#include "GameScene.h"
#include "EditScene.h"
#include "EditCursor.h"
#include "MapCtl.h"

GameScene::GameScene()
{

}


GameScene::~GameScene()
{
}

void GameScene::Init()
{
	LpMapCtl->MapReset();
	SetOffset(Vector2(20, 20));
	LpMapCtl->MapLoad();
}

unique_scene GameScene::Update(const char(&keyData)[256], const char(&keyDataOld)[256], unique_scene scene)
{
	// ¹Ş°Ñ‚Ì‰Šú‰»‚ÖˆÚ“®
	if (keyData[KEY_INPUT_F5] && !keyDataOld[KEY_INPUT_F5])
	{
		GameDestroy();
		return std::make_unique<EditScene>();
		return 1;
	}
	LpMapCtl->FireUpdate();
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
	LpMapCtl->MapDraw();
	// ÌßÚ²Ô°‚Ì¶°¿Ù‚ğ•`‰æ
	for (auto itr = objList.begin(); itr != objList.end(); itr++)
	{
		(*itr)->Draw();
	}
	ScreenFlip();
	return scene;
}

SCENE GameScene::GetMode()
{
	return SCENE::MAIN;
}
