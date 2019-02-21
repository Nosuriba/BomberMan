#include <DxLib.h>
#include "GameScene.h"
#include "EditScene.h"
#include "EditCursor.h"
#include "MapCtl.h"
#include "GameTask.h"

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
	// ｹﾞｰﾑの初期化へ移動
	if (keyData[KEY_INPUT_F5] && !keyDataOld[KEY_INPUT_F5])
	{
		LpGameTask.SetMode(SCENE::EDIT);
		return std::make_unique<EditScene>(keyData, keyDataOld);
	}
	LpMapCtl.FireUpdate();
	/// objListの管理が上手くいっていないので、そこの修正をおこなう
	for (auto itr = LpGameTask.GetObj().begin(); itr != LpGameTask.GetObj().end();)
	{
		if (!(*itr)->CheckActive())
		{
			delete (*itr);
			itr = LpGameTask.GetObj().erase(itr);		// 返り値の一つ先を消す
			continue;
		}
		itr++;
	}

	// キャラクターの情報を更新している
	for (auto itr = LpGameTask.GetObj().begin(); itr != LpGameTask.GetObj().end(); itr++)
	{
		(*itr)->Update();
		(*itr)->UpdateAnim();
	}
	ClsDrawScreen();
	LpMapCtl.MapDraw();
	// ﾌﾟﾚｲﾔｰのｶｰｿﾙを描画
	for (auto itr = LpGameTask.GetObj().begin(); itr != LpGameTask.GetObj().end(); itr++)
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

void GameScene::DeleteObjList()
{
	for (auto itr : LpGameTask.GetObj())
	{
		delete itr;
	}
	LpGameTask.GetObj().clear();			// ﾏｯﾌﾟﾃﾞｰﾀの情報を消去する
}
