#pragma once
#include <iostream>
#include <vector>
#include <list>
#include "Vector2.h"
class OBJ;
class SceneState;

using namespace std;

#define SCREEN_SIZE_X	(800)		// �ްѽ�ذ݉�ʂ̉�����
#define SCREEN_SIZE_Y	(600)		// �ްѽ�ذ݉�ʂ̏c����
#define GAME_SCREEN_X	(40)		// �ްщ�ʂ̉�����
#define GAME_SCREEN_Y	(75)		// �ްщ�ʂ̏c����
#define BLOCK_SIZE_X	(20)		// ��Ͻ�̻���
#define BLOCK_SIZE_Y	(20)		// �cϽ�̻���
#define MAP_DATA_X		((SCREEN_SIZE_X / BLOCK_SIZE_X ) - 2)		// ����ϯ���ް��̌�
#define MAP_DATA_Y		((SCREEN_SIZE_Y / BLOCK_SIZE_Y ) - 2)		// �c��ϯ���ް��̌�

#define LpGameTask GameTask::GetInstance()	// GameTask���ݸ��߲���
class GameTask
{
public:
	static GameTask & GetInstance()						// �ݸ���݂̎��̂�Ԃ��߲��������ފ֐�
	{
		return *s_Instance;								// �ݸ���݂ɂ��Ă�����Ԃ�Ԃ�
	}

	bool AddObj(OBJ *obj);
	void Run();
	void SetOffset(Vector2& pos);							// �`��̾�Ă̒l��n�����ފ֐�
	const Vector2 &GetOffset(void);							// �`��̾�Ă̒l��Ԃ����ފ֐�
	
	const Vector2 mapSize { MAP_DATA_X,MAP_DATA_Y };		// ϯ��ނ̏�����
	const Vector2 chipSize{ BLOCK_SIZE_X,BLOCK_SIZE_Y };	// ϯ�����߂̻��ނ̏�����
	const char	 (&keyDataPub)[256];
	const char	 (&keyDataOldPub)[256];
private:
	struct GameTaskDeleter
	{
		void operator ()(GameTask* gameTask) const
		{
			delete gameTask;
		}
	};

	GameTask();						
	~GameTask();
	int SysInit(void);				
	int SysDestroy(void);	
	void EditDestroy(void);			
	void DeleteObjList(void);
	void GameDestroy(void);			// �ް�Ӱ�ނ���؊J���p

	Vector2		drawOffset;							
	list<OBJ*>	objList;						
	char		keyData[256];						
	char		keyDataOld[256];					
	static std::unique_ptr<GameTask, GameTaskDeleter> s_Instance;					// �ݸ���ݗp���߲����ϐ�
	std::unique_ptr<SceneState> scenePtr;
};
int DrawLine(const Vector2 & pos1, const Vector2 & pos2, unsigned int Color);	// ���̕`��p�֐�
