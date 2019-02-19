#include "EditCursor.h"
#include "ImageMng.h"
#include "stdio.h"
#include "DxLib.h"
#include "GameTask.h"
#include "SceneState.h"

std::unique_ptr<GameTask, GameTask::GameTaskDeleter> GameTask::s_Instance(new GameTask());

GameTask::GameTask(): keyDataPub(keyData),keyDataOldPub(keyDataOld)		// ｹﾞｰﾑﾓｰﾄﾞのﾌﾟﾚｲﾔｰ用ｷｰ設定
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
		objList.push_back(obj);			// objの末尾にnullptrを追加する
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
	// ｼｽﾃﾑ処理
	SetGraphMode(SCREEN_SIZE_X, SCREEN_SIZE_Y, 16);		// 65536色ﾓｰﾄﾞに設定
	ChangeWindowMode(true);								// true:window　false:ﾌﾙｽｸﾘｰﾝ
	SetWindowText("Bomberman_Cplus:GSC1_1701310_北川 潤一");
	if (DxLib_Init() == -1) return false;				// DXﾗｲﾌﾞﾗﾘ初期化処理
	SetDrawScreen(DX_SCREEN_BACK);						// ひとまずﾊﾞｯｸﾊﾞｯﾌｧに描画

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
//	// ｹﾞｰﾑの初期化へ移動
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
//			itr = objList.erase(itr);		// 返り値の一つ先を消す
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
//	// ﾌﾟﾚｲﾔｰのｶｰｿﾙを描画
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
//	OBJ *tmp = new EditCursor(keyData,keyDataOld,GetOffset());				// ﾎﾟｲﾝﾀｰ変数にｵﾌﾞｼﾞｪｸﾄの情報を入れる
//	tmp->Init("image/map.png", Vector2(BLOCK_SIZE_X, BLOCK_SIZE_Y), Vector2(4,4), Vector2(3,3), 0);
//	AddObj(tmp);
//	return 1;
//}
//
//int GameTask::EditMain(void)
//{
//	// ｹﾞｰﾑの初期化へ移動
//	if (keyData[KEY_INPUT_F5] && !keyDataOld[KEY_INPUT_F5])
//	{
//		EditDestroy();
//		mode = GMODE_INIT;
//		return 1;
//	}
//	// ｴﾃﾞｨｯﾄﾃﾞｰﾀの保存
//	if (keyData[KEY_INPUT_F1])
//	{
//		if (MessageBox(
//			GetMainWindowHandle(),					// ｳｨﾝﾄﾞｳのﾊﾝﾄﾞﾙを取得する
//			"エディット内容をセーブしますか？",		// ﾒｯｾｰｼﾞﾎﾞｯｸｽのﾃｷｽﾄ内容
//			"確認ダイアログ",						// ﾒｯｾｰｼﾞﾎﾞｯｸｽのﾀｲﾄﾙ
//			MB_OKCANCEL) == IDOK)					// ﾒｯｾｰｼﾞﾎﾞｯｸｽのｽﾀｲﾙ
//		{
//			LpMapCtl->MapSave();
//		}
//	}
//	// ｴﾃﾞｨｯﾄﾃﾞｰﾀの読み込み
//	if (keyData[KEY_INPUT_F2])
//	{
//		if (MessageBox(
//			GetMainWindowHandle(),					// ｳｨﾝﾄﾞｳのﾊﾝﾄﾞﾙを取得する
//			"エディット内容をロードしますか？",		// ﾒｯｾｰｼﾞﾎﾞｯｸｽのﾃｷｽﾄ内容
//			"確認ダイアログ",						// ﾒｯｾｰｼﾞﾎﾞｯｸｽのﾀｲﾄﾙ
//			MB_OKCANCEL) == IDOK)					// ﾒｯｾｰｼﾞﾎﾞｯｸｽのｽﾀｲﾙ
//		{
//			LpMapCtl->MapLoad();
//		}
//	}
//	// 現在のｴﾃﾞｨｯﾄ内容を全て破棄
//	if (keyData[KEY_INPUT_DELETE])
//	{
//		if (MessageBox(
//			GetMainWindowHandle(),						// ｳｨﾝﾄﾞｳのﾊﾝﾄﾞﾙを取得する
//			"現在のエディット内容を破棄しますか？",		// ﾒｯｾｰｼﾞﾎﾞｯｸｽのﾃｷｽﾄ内容
//			"確認ダイアログ",							// ﾒｯｾｰｼﾞﾎﾞｯｸｽのﾀｲﾄﾙ
//			MB_OKCANCEL) == IDOK)						// ﾒｯｾｰｼﾞﾎﾞｯｸｽのｽﾀｲﾙ
//		{
//			LpMapCtl->MapDelete();
//		}
//	}
//	// 壁のﾗﾝﾀﾞﾑ配置
//	if (keyData[KEY_INPUT_SPACE])
//	{
//		if (MessageBox(
//			GetMainWindowHandle(),				// ｳｨﾝﾄﾞｳのﾊﾝﾄﾞﾙを取得する
//			"壁をランダムに配置しますか？",		// ﾒｯｾｰｼﾞﾎﾞｯｸｽのﾃｷｽﾄ内容
//			"確認ダイアログ",					// ﾒｯｾｰｼﾞﾎﾞｯｸｽのﾀｲﾄﾙ
//			MB_OKCANCEL) == IDOK)				// ﾒｯｾｰｼﾞﾎﾞｯｸｽのｽﾀｲﾙ
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
//	LpMapCtl->MapDraw();			// ﾏｯﾌﾟIDの描画
//	Vector2 pos1 = GetOffset();		// 線の始点用の変数
//	Vector2 pos2(0, 0);				// 線の終点用の変数
//
//	// 横線の描画
//	for (; pos1.x < SCREEN_SIZE_X; pos1.x += BLOCK_SIZE_X)
//	{
//		pos2 = Vector2(pos1.x, SCREEN_SIZE_Y - GetOffset().x);
//		DrawLine(pos1, pos2, 0x8c8c8c
//		);
//	}
//
//	pos1 = Vector2(SCREEN_SIZE_X - GetOffset().x, 0);			// 線の始点の長さを初期化する
//	// 縦線の描画
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
	
	objList.clear();			// ﾏｯﾌﾟﾃﾞｰﾀの情報を消去する
}

// 線の描画用関数
int DrawLine(const Vector2& pos1, const Vector2& pos2, unsigned int Color)
{
	DrawLine(pos1.x, pos1.y, pos2.x, pos2.y, 0x8c8c8c);	// (140,140,140)
	return 0;
}