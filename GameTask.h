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
#define BLOCK_SIZE_X	(20)		// ‰¡Ï½‚Ì»²½Ş
#define BLOCK_SIZE_Y	(20)		// cÏ½‚Ì»²½Ş
#define MAP_DATA_X		((SCREEN_SIZE_X / BLOCK_SIZE_X ) - 2)		// ‰¡‚ÌÏ¯ÌßÃŞ°À‚ÌŒÂ”
#define MAP_DATA_Y		((SCREEN_SIZE_Y / BLOCK_SIZE_Y ) - 2)		// c‚ÌÏ¯ÌßÃŞ°À‚ÌŒÂ”

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
	const SCENE GetMode();
	void SetObj(OBJ * obj);
	
	const Vector2 mapSize { MAP_DATA_X,MAP_DATA_Y };		// Ï¯ÌßŞ‚Ì‰Šú‰»
	const Vector2 chipSize{ BLOCK_SIZE_X,BLOCK_SIZE_Y };	// Ï¯ÌßÁ¯Ìß‚Ì»²½Ş‚Ì‰Šú‰»
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
	char		keyData[256];						
	char		keyDataOld[256];					
	static std::unique_ptr<GameTask, GameTaskDeleter> s_Instance;					// ¼İ¸ŞÙÄİ—p‚ÌÎß²İÀ°•Ï”
	std::unique_ptr<SceneState> scenePtr;
};
int DrawLine(const Vector2 & pos1, const Vector2 & pos2, unsigned int Color);	// ü‚Ì•`‰æ—pŠÖ”
