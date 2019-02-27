//////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////// 「ゲーム制作」 基本ｿｰｽ
//////////////////////////////////////////////////////////////////////
using namespace std;
#include <stdlib.h>
#include <iostream>			// C++を使用する
#include "Dxlib.h"			// DxLibﾗｲﾌﾞﾗﾘを使用する
#include "GameTask.h"		// ｹﾞｰﾑ全体の設定用ﾍｯﾀﾞｰ

// ---------- WinMain関数
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	LpGameTask.Run();
	DxLib_End();	// DXﾗｲﾌﾞﾗﾘの終了処理
	return 0;
}
