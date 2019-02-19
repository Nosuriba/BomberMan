#include <DxLib.h>
#include "MapCtl.h"
#include "GameScene.h"
#include "EditScene.h"
#include "EditCursor.h"

EditScene::EditScene()
{
	EditScene::Init();
}


EditScene::~EditScene()
{
}

void EditScene::Init()
{
	LpMapCtl->MapReset();
	offset = {20,20};
	OBJ *tmp = new EditCursor(keyData, keyDataOld, GetOffset());				// ﾎﾟｲﾝﾀｰ変数にｵﾌﾞｼﾞｪｸﾄの情報を入れる
	tmp->Init("image/map.png", Vector2(BLOCK_SIZE_X, BLOCK_SIZE_Y), Vector2(4, 4), Vector2(3, 3), 0);
	AddObj(tmp);
}

bool EditScene::AddObj(OBJ * obj)
{
	if (obj != nullptr)
	{
		objList.push_back(obj);			// objの末尾にnullptrを追加する
		return true;
	}
	return false;
}

unique_scene EditScene::Update(const char(&keyData)[256], const char(&keyDataOld)[256], unique_scene scene)
{
	// ｹﾞｰﾑの初期化へ移動
	if (keyData[KEY_INPUT_F5] && !keyDataOld[KEY_INPUT_F5])
	{
		return std::make_unique<GameScene>();
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
			LpMapCtl->MapSave();
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
			LpMapCtl->MapLoad();
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
			LpMapCtl->MapDelete();
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
			LpMapCtl->MapRandom();
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

	LpMapCtl->MapDraw();			// ﾏｯﾌﾟIDの描画
	Vector2 pos1 = GetOffset();		// 線の始点用の変数
	Vector2 pos2(0, 0);				// 線の終点用の変数

	// 横線の描画
	for (; pos1.x < SCREEN_SIZE_X; pos1.x += BLOCK_SIZE_X)
	{
		pos2 = Vector2(pos1.x, SCREEN_SIZE_Y - GetOffset().x);
		DrawLine(pos1, pos2, 0x8c8c8c
		);
	}

	pos1 = Vector2(SCREEN_SIZE_X - GetOffset().x, 0);			// 線の始点の長さを初期化する
	// 縦線の描画
	for (; pos1.y < SCREEN_SIZE_Y; pos1.y += BLOCK_SIZE_Y)
	{
		pos2 = Vector2(GetOffset().x, pos1.y);
		DrawLine(pos1, pos2, 0x8c8c8c);
	}
	ScreenFlip();
	return std::move(scene);
}

Vector2 EditScene::GetOffset()
{
	return offset;
}

SCENE EditScene::GetMode()
{
	return SCENE::EDIT;
}


