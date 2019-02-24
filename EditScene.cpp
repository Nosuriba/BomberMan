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
	OBJ *tmp = new EditCursor(keyData, keyDataOld, GetOffset());				// �߲����ϐ��ɵ�޼ު�Ă̏�������
	tmp->Init("image/map.png", Vector2(CHIP_SIZE, CHIP_SIZE), Vector2(4, 4), Vector2(3, 3), 0);
	LpGameTask.AddObj(tmp);
	objList = LpGameTask.GetObj();
}

unique_scene EditScene::Update(unique_scene scene)
{
	// �ްт̏������ֈړ�
	if (keyData[KEY_INPUT_F5] && !keyDataOld[KEY_INPUT_F5])
	{
		LpGameTask.DeleteObjList();
		return std::make_unique<GameScene>(keyData, keyDataOld);
	}
	// ��ި���ް��̕ۑ�
	if (keyData[KEY_INPUT_F1])
	{
		if (MessageBox(
			GetMainWindowHandle(),					// ����޳������ق��擾����
			"�G�f�B�b�g���e���Z�[�u���܂����H",		// ү�����ޯ����÷�ē��e
			"�m�F�_�C�A���O",						// ү�����ޯ��������
			MB_OKCANCEL) == IDOK)					// ү�����ޯ���̽���
		{
			LpMapCtl.MapSave();
		}
	}
	// ��ި���ް��̓ǂݍ���
	if (keyData[KEY_INPUT_F2])
	{
		if (MessageBox(
			GetMainWindowHandle(),					// ����޳������ق��擾����
			"�G�f�B�b�g���e�����[�h���܂����H",		// ү�����ޯ����÷�ē��e
			"�m�F�_�C�A���O",						// ү�����ޯ��������
			MB_OKCANCEL) == IDOK)					// ү�����ޯ���̽���
		{
			LpMapCtl.MapLoad();
		}
	}
	// ���̴݂�ި�ē��e��S�Ĕj��
	if (keyData[KEY_INPUT_DELETE])
	{
		if (MessageBox(
			GetMainWindowHandle(),						// ����޳������ق��擾����
			"���݂̃G�f�B�b�g���e��j�����܂����H",		// ү�����ޯ����÷�ē��e
			"�m�F�_�C�A���O",							// ү�����ޯ��������
			MB_OKCANCEL) == IDOK)						// ү�����ޯ���̽���
		{
			LpMapCtl.MapDelete();
		}
	}
	// �ǂ�����єz�u
	if (keyData[KEY_INPUT_SPACE])
	{
		if (MessageBox(
			GetMainWindowHandle(),				// ����޳������ق��擾����
			"�ǂ������_���ɔz�u���܂����H",		// ү�����ޯ����÷�ē��e
			"�m�F�_�C�A���O",					// ү�����ޯ��������
			MB_OKCANCEL) == IDOK)				// ү�����ޯ���̽���
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

	LpMapCtl.MapDraw();			// ϯ��ID�̕`��
	Vector2 pos1 = GetOffset();		// ���̎n�_�p�̕ϐ�
	Vector2 pos2(0, 0);				// ���̏I�_�p�̕ϐ�

	// �����̕`��
	for (; pos1.x < SCREEN_SIZE_X; pos1.x += CHIP_SIZE)
	{
		pos2 = Vector2(pos1.x, SCREEN_SIZE_Y - GetOffset().x);
		DrawLine(pos1, pos2, 0x8c8c8c);
	}

	pos1 = Vector2(SCREEN_SIZE_X - GetOffset().x, 0);			// ���̎n�_�̒���������������
	// �c���̕`��
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