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
	OBJ *tmp = new EditCursor(keyData, keyDataOld, GetOffset());				// �߲����ϐ��ɵ�޼ު�Ă̏�������
	tmp->Init("image/map.png", Vector2(BLOCK_SIZE_X, BLOCK_SIZE_Y), Vector2(4, 4), Vector2(3, 3), 0);
	AddObj(tmp);
}

bool EditScene::AddObj(OBJ * obj)
{
	if (obj != nullptr)
	{
		objList.push_back(obj);			// obj�̖�����nullptr��ǉ�����
		return true;
	}
	return false;
}

unique_scene EditScene::Update(const char(&keyData)[256], const char(&keyDataOld)[256], unique_scene scene)
{
	// �ްт̏������ֈړ�
	if (keyData[KEY_INPUT_F5] && !keyDataOld[KEY_INPUT_F5])
	{
		return std::make_unique<GameScene>();
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
			LpMapCtl->MapSave();
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
			LpMapCtl->MapLoad();
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
			LpMapCtl->MapDelete();
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

	LpMapCtl->MapDraw();			// ϯ��ID�̕`��
	Vector2 pos1 = GetOffset();		// ���̎n�_�p�̕ϐ�
	Vector2 pos2(0, 0);				// ���̏I�_�p�̕ϐ�

	// �����̕`��
	for (; pos1.x < SCREEN_SIZE_X; pos1.x += BLOCK_SIZE_X)
	{
		pos2 = Vector2(pos1.x, SCREEN_SIZE_Y - GetOffset().x);
		DrawLine(pos1, pos2, 0x8c8c8c
		);
	}

	pos1 = Vector2(SCREEN_SIZE_X - GetOffset().x, 0);			// ���̎n�_�̒���������������
	// �c���̕`��
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


