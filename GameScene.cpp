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
	// ｹﾞｰﾑの初期化へ移動
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
			itr = objList.erase(itr);		// 返り値の一つ先を消す
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
	// ﾌﾟﾚｲﾔｰのｶｰｿﾙを描画
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
