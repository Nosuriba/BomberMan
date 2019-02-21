#include <DxLib.h>
#include "GameScene.h"
#include "EditScene.h"
#include "EditCursor.h"
#include "MapCtl.h"
#include "GameTask.h"

GameScene::GameScene(const char(&_keyData)[256], const char(&_keyDataOld)[256]) : 
	keyData(_keyData), keyDataOld(_keyDataOld)
{
	Init();
}


GameScene::~GameScene()
{
}

void GameScene::Init()
{
	LpMapCtl.MapReset();
	offset = {20,20};
	LpMapCtl.MapLoad();
}

unique_scene GameScene::Update(unique_scene scene)
{
	// �ްт̏������ֈړ�
	if (keyData[KEY_INPUT_F5] && !keyDataOld[KEY_INPUT_F5])
	{
		LpGameTask.SetMode(SCENE::EDIT);
		return std::make_unique<EditScene>(keyData, keyDataOld);
	}
	LpMapCtl.FireUpdate();
	/// objList�̊Ǘ�����肭�����Ă��Ȃ��̂ŁA�����̏C���������Ȃ�
	for (auto itr = LpGameTask.GetObj().begin(); itr != LpGameTask.GetObj().end();)
	{
		if (!(*itr)->CheckActive())
		{
			delete (*itr);
			itr = LpGameTask.GetObj().erase(itr);		// �Ԃ�l�̈�������
			continue;
		}
		itr++;
	}

	// �L�����N�^�[�̏����X�V���Ă���
	for (auto itr = LpGameTask.GetObj().begin(); itr != LpGameTask.GetObj().end(); itr++)
	{
		(*itr)->Update();
		(*itr)->UpdateAnim();
	}
	ClsDrawScreen();
	LpMapCtl.MapDraw();
	// ��ڲ԰�̶��ق�`��
	for (auto itr = LpGameTask.GetObj().begin(); itr != LpGameTask.GetObj().end(); itr++)
	{
		(*itr)->Draw();
	}
	ScreenFlip();
	return scene;
}

Vector2 GameScene::GetOffset()
{
	return offset;
}

void GameScene::DeleteObjList()
{
	for (auto itr : LpGameTask.GetObj())
	{
		delete itr;
	}
	LpGameTask.GetObj().clear();			// ϯ���ް��̏�����������
}
