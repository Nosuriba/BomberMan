#include "GameTask.h"
#include "EditCursor.h"
#include "DxLib.h"

EditCursor::EditCursor(const char(&_keyData)[256],const char(&_keyDataOld)[256], Vector2 offSet):OBJ(_keyData, _keyDataOld, offSet)
{
	keyGetRng	= EDIT_KEY_GET_RNG;		// ���̷������܂ł̊Ԋu�̏�����
	inputFlam	= EDIT_KEY_GET_RNG;		// �O�񂩂�̈ړ��Ԋu���ڰт̏�����
	blindFlam	= 0;					// ���ق̓����x�p�ڰт̏�����
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

	// �������ޯĂ̕`��
	for (int y = 1; y < LpGameTask.GetMapSize().y; y++)
	{
		// �c�����ޯĕ\��
		DrawBox(this->pos.x + (this->drawOffset.x * 2), this->pos.y + (this->drawOffset.y * 2), 
				this->pos.x + (this->drawOffset.x * 3), (y * this->drawOffset.y + this->drawOffset.y), 0x888800, true);
		for (int x = 1; x < LpGameTask.GetMapSize().x; x++)
		{
			// �������ޯĕ\��
			DrawBox(this->pos.x + this->drawOffset.x, this->pos.y + (this->drawOffset.y * 2),
					((x * this->drawOffset.x) + this->drawOffset.x), this->pos.y + (this->drawOffset.y * 3), 0x888800, true);
		}
	}
	
	// ���ق̓����x�𒲐����ĕ`�悷��
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);													// ������:OFF
	DrawGraph((this->drawOffset.x * 2) + this->pos.x, (this->drawOffset.y * 2) + this->pos.y,	
			 LpImageMng.ImgGetID(imageName)[chipOffset.x + chipOffset.y * divCnt.x], true);	
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, abs((blindFlam % (ALPHA_MAX * 2)) - ALPHA_MAX));		// ������:ON(��̧�l���Βl�ɂ���)
	DrawGraph((this->drawOffset.x * 2) + this->pos.x, (this->drawOffset.y * 2)+ this->pos.y,	
			 LpImageMng.ImgGetID(imageName)[mapChip], true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);													// ������:OFF

	blindFlam += BLIND_FLAM_CNT;			// ���ٓ����x�p�ڰт����Z����

}

void EditCursor::SetMove(void)
{
	Vector2 tmpPos(pos);		// ���ق̈ړ��p

	// �E�ړ�(����)
	if (keyData[KEY_INPUT_NUMPAD4] && pos.x >= getSize().x)
	{
		tmpPos.x -= getSize().x;
	}
	// ���ړ�(����)
	if (keyData[KEY_INPUT_NUMPAD6] && pos.x <= SCREEN_SIZE_X - (getSize().x * BLANK_BLOCK))
	{
		tmpPos.x += getSize().x;
	}
	// ��ړ�(����)
	if (keyData[KEY_INPUT_NUMPAD8] && pos.y >= getSize().y)
	{
		tmpPos.y -= getSize().y;
	}
	// ���ړ�(����)
	if (keyData[KEY_INPUT_NUMPAD2] && pos.y <= SCREEN_SIZE_Y - (getSize().y * BLANK_BLOCK))
	{
		tmpPos.y += getSize().y;
	}
	// ���ق̋����ݒ�
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
	// ���������ĂȂ��ꍇ
	else
	{
		inputFlam = EDIT_KEY_GET_RNG;			// �����������ڰѐ��̏�����
		keyGetRng = EDIT_KEY_GET_RNG;			// �ڰъԊu�̏�����
		// ϯ���ް��̐ݒu
		if (keyData[KEY_INPUT_Z])
		{
			LpMapCtl.SetMapData(mapChip, pos + LpGameTask.GetOffset());
		}
		// ϯ��ID�̉��Z
		if (keyData[KEY_INPUT_S] && !keyDataOld[KEY_INPUT_S])
		{
			mapChip = (MAP_ID)((mapChip + 1) % END_EDIT_CHIP);
		}
		// ϯ��ID�̌��Z
		if (keyData[KEY_INPUT_A] && !keyDataOld[KEY_INPUT_A])
		{
			mapChip = (MAP_ID)((mapChip + (END_EDIT_CHIP - 1)) % END_EDIT_CHIP);
		}
	}
}
