#pragma once
#include <iostream>
#include <vector>
#include <list>
#include "Vector2.h"
#include "SceneState.h"

class OBJ;

#define SCREEN_SIZE_X	(800)		// ｹﾞｰﾑｽｸﾘｰﾝ画面の横ｻｲｽﾞ
#define SCREEN_SIZE_Y	(600)		// ｹﾞｰﾑｽｸﾘｰﾝ画面の縦ｻｲｽﾞ
#define GAME_SCREEN_X	(40)		// ｹﾞｰﾑ画面の横ｻｲｽﾞ
#define GAME_SCREEN_Y	(75)		// ｹﾞｰﾑ画面の縦ｻｲｽﾞ
#define BLOCK_SIZE_X	(20)		// 横ﾏｽのｻｲｽﾞ
#define BLOCK_SIZE_Y	(20)		// 縦ﾏｽのｻｲｽﾞ
#define MAP_DATA_X		((SCREEN_SIZE_X / BLOCK_SIZE_X ) - 2)		// 横のﾏｯﾌﾟﾃﾞｰﾀの個数
#define MAP_DATA_Y		((SCREEN_SIZE_Y / BLOCK_SIZE_Y ) - 2)		// 縦のﾏｯﾌﾟﾃﾞｰﾀの個数

#define LpGameTask GameTask::GetInstance()	// GameTaskのﾛﾝｸﾞﾎﾟｲﾝﾀｰ
class GameTask
{
public:
	static GameTask & GetInstance()						// ｼﾝｸﾞﾙﾄﾝの実体を返すﾎﾟｲﾝﾀｰのﾒﾝﾊﾞ関数
	{
		return *s_Instance;								// ｼﾝｸﾞﾙﾄﾝにしている実態を返す
	}

	void Run();
	const Vector2 &GetOffset(void);							// 描画ｵﾌｾｯﾄの値を返すﾒﾝﾊﾞ関数
	const SCENE GetMode();
	void SetObj(OBJ * obj);
	
	const Vector2 mapSize { MAP_DATA_X,MAP_DATA_Y };		// ﾏｯﾌﾟﾞの初期化
	const Vector2 chipSize{ BLOCK_SIZE_X,BLOCK_SIZE_Y };	// ﾏｯﾌﾟﾁｯﾌﾟのｻｲｽﾞの初期化
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
	static std::unique_ptr<GameTask, GameTaskDeleter> s_Instance;					// ｼﾝｸﾞﾙﾄﾝ用のﾎﾟｲﾝﾀｰ変数
	std::unique_ptr<SceneState> scenePtr;
};
int DrawLine(const Vector2 & pos1, const Vector2 & pos2, unsigned int Color);	// 線の描画用関数
