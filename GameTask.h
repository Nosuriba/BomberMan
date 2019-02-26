#pragma once
#include <iostream>
#include <memory>
#include <list>
#include "Vector2.h"
#include "SceneState.h"

class OBJ;

#define SCREEN_SIZE_X	(800)		// ¹Ş°Ñ½¸Ø°İ‰æ–Ê‚Ì‰¡»²½Ş
#define SCREEN_SIZE_Y	(600)		// ¹Ş°Ñ½¸Ø°İ‰æ–Ê‚Ìc»²½Ş
#define GAME_SCREEN_X	(40)		// ¹Ş°Ñ‰æ–Ê‚Ì‰¡»²½Ş
#define GAME_SCREEN_Y	(75)		// ¹Ş°Ñ‰æ–Ê‚Ìc»²½Ş
#define CHIP_SIZE		(20)

#define LpGameTask GameTask::GetInstance()	// GameTask‚ÌÛİ¸ŞÎß²İÀ°

class GameTask
{
public:
	static GameTask & GetInstance()						// ¼İ¸ŞÙÄİ‚ÌÀ‘Ì‚ğ•Ô‚·Îß²İÀ°‚ÌÒİÊŞŠÖ”
	{
		return *s_Instance;								// ¼İ¸ŞÙÄİ‚É‚µ‚Ä‚¢‚éÀ‘Ô‚ğ•Ô‚·
	}

	void Run();
	const Vector2 &GetOffset(void);							// •`‰æµÌ¾¯Ä‚Ì’l‚ğ•Ô‚·ÒİÊŞŠÖ”
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
	static std::unique_ptr<GameTask, GameTaskDeleter> s_Instance;					// ¼İ¸ŞÙÄİ—p‚ÌÎß²İÀ°•Ï”
	std::list<OBJ*> objList;
	std::unique_ptr<SceneState> scenePtr;

	Vector2 offset;
	SCENE mode;
	const Vector2 mapSize;
};
int DrawLine(const Vector2 & pos1, const Vector2 & pos2, unsigned int Color);	// ü‚Ì•`‰æ—pŠÖ”
