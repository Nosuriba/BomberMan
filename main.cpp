//////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////// �u�Q�[������v ��{���
//////////////////////////////////////////////////////////////////////
using namespace std;
#include <stdlib.h>
#include <iostream>			// C++���g�p����
#include "Dxlib.h"			// DxLibײ���؂��g�p����
#include "GameTask.h"		// �ްёS�̂̐ݒ�pͯ�ް

// ---------- WinMain�֐�
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	LpGameTask.Run();
	// ---------- �ް�ٰ��
	//while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	//{
	//	LpGameTask.Update();		// �ްёS�̂̏�������ްт̍X�V������֐����ԐڎQ�Ƃ���
	//}
	DxLib_End();	// DXײ���؂̏I������
	return 0;
}
