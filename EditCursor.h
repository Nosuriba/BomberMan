#pragma once
#include "OBJ.h"
#include "MapCtl.h"

#define EDIT_KEY_GET_RNG (30)	// 次のｷｰ処理までのﾌﾚｰﾑ数
#define BLIND_FLAM_CNT	 (12)	// ｶｰｿﾙ描画の透明度用ﾌﾚｰﾑ
#define ALPHA_MAX		 (256)	// 透明度の最大値
#define BLANK_BLOCK		 (6)	// 空白のﾏｽ用[3ﾏｽ×2(次元)]

class EditCursor:
  public OBJ
{
public:
	EditCursor(const char(&_keyData)[256],const char(&_keyDataOld)[256], Vector2 offSet);		// ｷｰの情報と描画用ｵﾌｾｯﾄの情報が入った引数付きｺﾝｽﾄﾗｸﾀ
	~EditCursor();
	void Draw(void);
private:
	void SetMove(void);
	unsigned int keyGetRng;			// 次のｷｰ処理までの間隔
	unsigned int inputFlam;			// 前回からの移動間隔のﾌﾚｰﾑ
	MAP_ID	mapChip { MAP_WALL1 };	// ﾏｯﾌﾟIDの初期値
	int		blindFlam;				// 透明度用ﾌﾚｰﾑ
};