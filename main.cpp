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
	DxLib_End();	// DXײ���؂̏I������
	return 0;
}
