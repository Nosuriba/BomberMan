#include "GameTask.h"
#include "EditCursor.h"
#include "DxLib.h"

EditCursor::EditCursor(const char(&_keyData)[256],const char(&_keyDataOld)[256], Vector2 offSet):OBJ(_keyData, _keyDataOld, offSet)
{
	keyGetRng	= EDIT_KEY_GET_RNG;		// 次のｷｰ処理までの間隔の初期化
	inputFlam	= EDIT_KEY_GET_RNG;		// 前回からの移動間隔のﾌﾚｰﾑの初期化
	blindFlam	= 0;					// ｶｰｿﾙの透明度用ﾌﾚｰﾑの初期化
}

EditCursor::~EditCursor()
{
}

void EditCursor::Draw(void)
{
	if (imageName.length() == 0)
	{
		return;
	}

	// ｶｰｿﾙﾀｰｹﾞｯﾄの描画
	for (int y = 1; y < LpGameTask.GetMapSize().y; y++)
	{
		// 縦のﾀｰｹﾞｯﾄ表示
		DrawBox(this->pos.x + (this->drawOffset.x * 2), this->pos.y + (this->drawOffset.y * 2), 
				this->pos.x + (this->drawOffset.x * 3), (y * this->drawOffset.y + this->drawOffset.y), 0x888800, true);
		for (int x = 1; x < LpGameTask.GetMapSize().x; x++)
		{
			// 横のﾀｰｹﾞｯﾄ表示
			DrawBox(this->pos.x + this->drawOffset.x, this->pos.y + (this->drawOffset.y * 2),
					((x * this->drawOffset.x) + this->drawOffset.x), this->pos.y + (this->drawOffset.y * 3), 0x888800, true);
		}
	}
	
	// ｶｰｿﾙの透明度を調整して描画する
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);													// 透明化:OFF
	DrawGraph((this->drawOffset.x * 2) + this->pos.x, (this->drawOffset.y * 2) + this->pos.y,	
			 LpImageMng.ImgGetID(imageName)[chipOffset.x + chipOffset.y * divCnt.x], true);	
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, abs((blindFlam % (ALPHA_MAX * 2)) - ALPHA_MAX));		// 透明化:ON(ｱﾙﾌｧ値を絶対値にする)
	DrawGraph((this->drawOffset.x * 2) + this->pos.x, (this->drawOffset.y * 2)+ this->pos.y,	
			 LpImageMng.ImgGetID(imageName)[mapChip], true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);													// 透明化:OFF

	blindFlam += BLIND_FLAM_CNT;			// ｶｰｿﾙ透明度用ﾌﾚｰﾑを加算する

}

void EditCursor::SetMove(void)
{
	Vector2 tmpPos(pos);		// ｶｰｿﾙの移動用

	// 右移動(ｶｰｿﾙ)
	if (keyData[KEY_INPUT_NUMPAD4] && pos.x >= getSize().x)
	{
		tmpPos.x -= getSize().x;
	}
	// 左移動(ｶｰｿﾙ)
	if (keyData[KEY_INPUT_NUMPAD6] && pos.x <= SCREEN_SIZE_X - (getSize().x * BLANK_BLOCK))
	{
		tmpPos.x += getSize().x;
	}
	// 上移動(ｶｰｿﾙ)
	if (keyData[KEY_INPUT_NUMPAD8] && pos.y >= getSize().y)
	{
		tmpPos.y -= getSize().y;
	}
	// 下移動(ｶｰｿﾙ)
	if (keyData[KEY_INPUT_NUMPAD2] && pos.y <= SCREEN_SIZE_Y - (getSize().y * BLANK_BLOCK))
	{
		tmpPos.y += getSize().y;
	}
	// ｶｰｿﾙの挙動設定
	if (tmpPos != pos)
	{
		inputFlam++; 
		if (inputFlam >= keyGetRng)			
		{
			pos			= tmpPos;				
			inputFlam	= 0;					
			keyGetRng	= (keyGetRng < 5 ? keyGetRng = 5: keyGetRng / 2);	
		}
	}
	// ｷｰを押してない場合
	else
	{
		inputFlam = EDIT_KEY_GET_RNG;			// 押した時のﾌﾚｰﾑ数の初期化
		keyGetRng = EDIT_KEY_GET_RNG;			// ﾌﾚｰﾑ間隔の初期化
		// ﾏｯﾌﾟﾃﾞｰﾀの設置
		if (keyData[KEY_INPUT_Z])
		{
			LpMapCtl.SetMapData(mapChip, pos + LpGameTask.GetOffset());
		}
		// ﾏｯﾌﾟIDの加算
		if (keyData[KEY_INPUT_S] && !keyDataOld[KEY_INPUT_S])
		{
			mapChip = (MAP_ID)((mapChip + 1) % END_EDIT_CHIP);
		}
		// ﾏｯﾌﾟIDの減算
		if (keyData[KEY_INPUT_A] && !keyDataOld[KEY_INPUT_A])
		{
			mapChip = (MAP_ID)((mapChip + (END_EDIT_CHIP - 1)) % END_EDIT_CHIP);
		}
	}
}
