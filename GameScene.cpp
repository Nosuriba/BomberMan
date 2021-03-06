#include <DxLib.h>
#include "GameScene.h"
#include "EditScene.h"
#include "EditCursor.h"
#include "MapCtl.h"
#include "GameTask.h"

GameScene::GameScene(const char(&_keyData)[256], const char(&_keyDataOld)[256]) : 
	keyData(_keyData), keyDataOld(_keyDataOld)
{
}


GameScene::~GameScene()
{
}

void GameScene::Init(SCENE mode)
{
	LpMapCtl.MapReset();
	offset = { 20,20 };
	LpMapCtl.MapLoad();
	objList = LpGameTask.GetObj();
}

unique_scene GameScene::Update(unique_scene scene)
{
	objList = LpGameTask.GetObj();
	// ｹﾞｰﾑの初期化へ移動
	if (keyData[KEY_INPUT_F5] && !keyDataOld[KEY_INPUT_F5])
	{
		LpGameTask.DeleteObjList();
		return std::make_unique<EditScene>(keyData, keyDataOld);
	}

	LpMapCtl.FireUpdate();
	for (auto itr = objList.begin(); itr != objList.end();)
	{
		if (!(*itr)->CheckActive())
		{
			delete (*itr);
			itr = objList.erase(itr);
			LpGameTask.SetObj(objList);			/// objListの中身を削除した状態を更新している。
			continue;
		}
		itr++;
	}

	// キャラクターの情報を更新している
	for (auto itr : objList)
	{
		(*itr).Update();
		(*itr).UpdateAnim();
	}
	ClsDrawScreen();
	LpMapCtl.MapDraw();
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

Vector2 GameScene::GetOffset()
{
	return offset;
}
