#include <DxLib.h>
#include "MapCtl.h"
#include "GameTask.h"
#include "GameScene.h"
#include "EditScene.h"
#include "EditCursor.h"

EditScene::EditScene(const char(&_keyData)[256], const char(&_keyDataOld)[256]) : 
	keyData(_keyData), keyDataOld(_keyDataOld)
{
}


EditScene::~EditScene()
{
}

void EditScene::Init(SCENE mode)
{
	LpMapCtl.MapReset();
	LpMapCtl.MapLoad();
	offset = { 20,20 };
	OBJ *tmp = new EditCursor(keyData, keyDataOld, GetOffset());				// ﾎﾟｲﾝﾀｰ変数にｵﾌﾞｼﾞｪｸﾄの情報を入れる
	tmp->Init("image/map.png", Vector2(CHIP_SIZE, CHIP_SIZE), Vector2(4, 4), Vector2(3, 3), 0);
	LpGameTask.AddObj(tmp);
	objList = LpGameTask.GetObj();
}

unique_scene EditScene::Update(unique_scene scene)
{
	// ｹﾞｰﾑの初期化へ移動
	if (keyData[KEY_INPUT_F5] && !keyDataOld[KEY_INPUT_F5])
	{
		LpGameTask.DeleteObjList();
		return std::make_unique<GameScene>(keyData, keyDataOld);
	}
	// ｴﾃﾞｨｯﾄﾃﾞｰﾀの保存
	if (keyData[KEY_INPUT_F1])
	{
		if (MessageBox(
			GetMainWindowHandle(),					// ｳｨﾝﾄﾞｳのﾊﾝﾄﾞﾙを取得する
			"エディット内容をセーブしますか？",		// ﾒｯｾｰｼﾞﾎﾞｯｸｽのﾃｷｽﾄ内容
			"確認ダイアログ",						// ﾒｯｾｰｼﾞﾎﾞｯｸｽのﾀｲﾄﾙ
			MB_OKCANCEL) == IDOK)					// ﾒｯｾｰｼﾞﾎﾞｯｸｽのｽﾀｲﾙ
		{
			LpMapCtl.MapSave();
		}
	}
	// ｴﾃﾞｨｯﾄﾃﾞｰﾀの読み込み
	if (keyData[KEY_INPUT_F2])
	{
		if (MessageBox(
			GetMainWindowHandle(),					// ｳｨﾝﾄﾞｳのﾊﾝﾄﾞﾙを取得する
			"エディット内容をロードしますか？",		// ﾒｯｾｰｼﾞﾎﾞｯｸｽのﾃｷｽﾄ内容
			"確認ダイアログ",						// ﾒｯｾｰｼﾞﾎﾞｯｸｽのﾀｲﾄﾙ
			MB_OKCANCEL) == IDOK)					// ﾒｯｾｰｼﾞﾎﾞｯｸｽのｽﾀｲﾙ
		{
			LpMapCtl.MapLoad();
		}
	}
	// 現在のｴﾃﾞｨｯﾄ内容を全て破棄
	if (keyData[KEY_INPUT_DELETE])
	{
		if (MessageBox(
			GetMainWindowHandle(),						// ｳｨﾝﾄﾞｳのﾊﾝﾄﾞﾙを取得する
			"現在のエディット内容を破棄しますか？",		// ﾒｯｾｰｼﾞﾎﾞｯｸｽのﾃｷｽﾄ内容
			"確認ダイアログ",							// ﾒｯｾｰｼﾞﾎﾞｯｸｽのﾀｲﾄﾙ
			MB_OKCANCEL) == IDOK)						// ﾒｯｾｰｼﾞﾎﾞｯｸｽのｽﾀｲﾙ
		{
			LpMapCtl.MapDelete();
		}
	}
	// 壁のﾗﾝﾀﾞﾑ配置
	if (keyData[KEY_INPUT_SPACE])
	{
		if (MessageBox(
			GetMainWindowHandle(),				// ｳｨﾝﾄﾞｳのﾊﾝﾄﾞﾙを取得する
			"壁をランダムに配置しますか？",		// ﾒｯｾｰｼﾞﾎﾞｯｸｽのﾃｷｽﾄ内容
			"確認ダイアログ",					// ﾒｯｾｰｼﾞﾎﾞｯｸｽのﾀｲﾄﾙ
			MB_OKCANCEL) == IDOK)				// ﾒｯｾｰｼﾞﾎﾞｯｸｽのｽﾀｲﾙ
		{
			LpMapCtl.MapRandom();
		}
	}

	for (auto itr : objList)
	{
		itr->Update();
	}


	ClsDrawScreen();

	for (auto itr : objList)
	{
		itr->Draw();
	}

	LpMapCtl.MapDraw();			// ﾏｯﾌﾟIDの描画
	Vector2 pos1 = GetOffset();		// 線の始点用の変数
	Vector2 pos2(0, 0);				// 線の終点用の変数

	// 横線の描画
	for (; pos1.x < SCREEN_SIZE_X; pos1.x += CHIP_SIZE)
	{
		pos2 = Vector2(pos1.x, SCREEN_SIZE_Y - GetOffset().x);
		DrawLine(pos1, pos2, 0x8c8c8c);
	}

	pos1 = Vector2(SCREEN_SIZE_X - GetOffset().x, 0);			// 線の始点の長さを初期化する
	// 縦線の描画
	for (; pos1.y < SCREEN_SIZE_Y; pos1.y += CHIP_SIZE)
	{
		pos2 = Vector2(GetOffset().x, pos1.y);
		DrawLine(pos1, pos2, 0x8c8c8c);
	}
	ScreenFlip();
	return std::move(scene);
}

SCENE EditScene::GetMode()
{
	return SCENE::EDIT;
}

Vector2 EditScene::GetOffset()
{
	return offset;
}