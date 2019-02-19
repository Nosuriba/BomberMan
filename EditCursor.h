#pragma once
#include "OBJ.h"
#include "MapCtl.h"

#define EDIT_KEY_GET_RNG (30)	// ���̷������܂ł��ڰѐ�
#define BLIND_FLAM_CNT	 (12)	// ���ٕ`��̓����x�p�ڰ�
#define ALPHA_MAX		 (256)	// �����x�̍ő�l
#define BLANK_BLOCK		 (6)	// �󔒂�Ͻ�p[3Ͻ�~2(����)]

class EditCursor:
  public OBJ
{
public:
	EditCursor(const char(&_keyData)[256],const char(&_keyDataOld)[256], Vector2 offSet);		// ���̏��ƕ`��p�̾�Ă̏�񂪓����������t���ݽ�׸�
	~EditCursor();
	void Draw(void);
private:
	void SetMove(void);
	unsigned int keyGetRng;			// ���̷������܂ł̊Ԋu
	unsigned int inputFlam;			// �O�񂩂�̈ړ��Ԋu���ڰ�
	MAP_ID	mapChip { MAP_WALL1 };	// ϯ��ID�̏����l
	int		blindFlam;				// �����x�p�ڰ�
};