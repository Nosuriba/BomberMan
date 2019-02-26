#pragma once
#include <iostream>
#include <memory>
#include <list>
#include "Vector2.h"
#include "SceneState.h"

class OBJ;

#define SCREEN_SIZE_X	(800)		// �ްѽ�ذ݉�ʂ̉�����
#define SCREEN_SIZE_Y	(600)		// �ްѽ�ذ݉�ʂ̏c����
#define GAME_SCREEN_X	(40)		// �ްщ�ʂ̉�����
#define GAME_SCREEN_Y	(75)		// �ްщ�ʂ̏c����
#define CHIP_SIZE		(20)

#define LpGameTask GameTask::GetInstance()	// GameTask���ݸ��߲���

class GameTask
{
public:
	static GameTask & GetInstance()						// �ݸ���݂̎��̂�Ԃ��߲��������ފ֐�
	{
		return *s_Instance;								// �ݸ���݂ɂ��Ă�����Ԃ�Ԃ�
	}

	void Run();
	const Vector2 &GetOffset(void);							// �`��̾�Ă̒l��Ԃ����ފ֐�
	void SetMode(const SCENE mode);
	const SCENE GetMode();
	const Vector2 GetMapSize();
	bool AddObj(OBJ * obj);
	std::list<OBJ*> GetObj();
	void SetObj(std::list<OBJ*> objList);
	void DeleteObjList();
	
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
	char keyData[256];						
	char keyDataOld[256];					
	static std::unique_ptr<GameTask, GameTaskDeleter> s_Instance;					// �ݸ���ݗp���߲����ϐ�
	std::list<OBJ*> objList;
	std::unique_ptr<SceneState> scenePtr;

	Vector2 offset;
	SCENE mode;
	const Vector2 mapSize;
};
int DrawLine(const Vector2 & pos1, const Vector2 & pos2, unsigned int Color);	// ���̕`��p�֐�
