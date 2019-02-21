#pragma once
#include "Vector2.h"
#include "OBJ.h"
#include "Bomb.h"
#include <vector>

// ﾗｼﾞｱﾝの定義
#define PAI (3.141592f)
#define DEG(X) ((X)*PAI/180.0f)

// ﾏｯﾌﾟID
enum MAP_ID
{
	MAP_NON,			// 何もない状態
	MAP_EDIT_PL,		// ﾌﾟﾚｲﾔｰ
	MAP_EDIT_EM1,		// 敵ｷｬﾗ1
	MAP_EDIT_EM2,		// 敵ｷｬﾗ2
	MAP_ITEM_FIRE,		// ｱｲﾃﾑ(爆破の範囲が広がる)
	MAP_ITEM_BOMB,		// ｱｲﾃﾑ(爆弾の設置できる個数が増える)
	MAP_ITEM_SWITCH,	// ｱｲﾃﾑ(好きなﾀｲﾐﾝｸﾞで爆破することができる)
	MAP_ITEM_SHOSE,		// ｱｲﾃﾑ(ﾌﾟﾚｲﾔｰのｽﾋﾟｰﾄﾞが早くなる)
	MAP_WALL1,			// 赤い壁
	MAP_WALL2,			// 青い壁
	MAP_BLOCK,			// 壊せる壁
	MAP_FIRE,			// 予備の設定(爆風)
	MAP_FLOOR1,			// 赤い床
	MAP_FLOOR2,			// 青い床
	MAP_BOMB,			// 予備の設定(爆弾のID)
	MAP_EDIT_CURSOR,	// ｶｰｿﾙ
	MAP_ID_MAX			// ﾏｯﾌﾟIDの最大値
};

// ﾏｯﾌﾟIDの指定
#define START_EDIT_CHIP MAP_NON			// ｴﾃﾞｨｯﾄﾓｰﾄﾞの最初のﾁｯﾌﾟ
#define END_EDIT_CHIP	MAP_BLOCK		// ｴﾃﾞｨｯﾄﾓｰﾄﾞの最後のﾁｯﾌﾟ
#define START_GAME_CHIP	MAP_ITEM_FIRE	// ｹﾞｰﾑﾓｰﾄﾞの最初のﾁｯﾌﾟ
#define END_GAME_CHIP	MAP_FLOOR2		// ｹﾞｰﾑﾓｰﾄﾞ最後のﾁｯﾌﾟ
#define BLAST_TIME_MAX	(60)
// vectorの二次元配列の型を変えたもの
using VEC2_MAPID = vector<vector<MAP_ID>>;

struct DataHeader {
	char fileID[13];		// ﾌｧｲﾙのID
	unsigned char verID;	// ﾌｧｲﾙのﾊﾞｰｼﾞｮﾝ番号
	unsigned char rez1[2];	// ｱﾗｲﾒﾝﾄ分の予約領域
	int sizeX;				// ﾏｯﾌﾟのｻｲｽﾞX
	int sizeY;				// ﾏｯﾌﾟのｻｲｽﾞY
	unsigned char rez2[3];	// sum値の予約領域
	unsigned char sum;		// sum値
};

struct FireStr {
	bool flag;
	int count;
};
// typedef vector<vector<vector<FireStr>>> VEC_FIRE_ID
using VEC_FIRE_ID = vector<vector<vector<FireStr>>>;		// 爆風のデータ型ID([Yの個数][Xの個数][爆風の方向])

#define BBM_ID_NAME "BBM_MAP_DATA"
#define BBM_VER_ID	0x01					// ﾎﾞﾝﾊﾞｰﾏﾝのﾊﾞｰｼﾞｮﾝID

#define LpMapCtl MapCtl::GetInstance()		// MapCtlのﾛﾝｸﾞﾎﾟｲﾝﾀｰ

class MapCtl
{
public:
	static MapCtl & GetInstance()
	{
		return *s_Instance;
	}
	bool MapReset(void);							// ﾏｯﾌﾟﾃﾞｰﾀの再設定
	bool MapSave(void);
	bool MapLoad(void);
	void SetPlayer(void);						// ﾌﾟﾚｲﾔｰのｾｯﾄｱｯﾌﾟ用
	void MapDelete(void);						// 作成中のﾏｯﾌﾟﾃﾞｰﾀの削除用
	void MapRandom(void);
	void MapDraw(void);
	bool SetMapData(MAP_ID id, Vector2& vec);		// ﾏｯﾌﾟﾃﾞｰﾀの情報取得用	
	bool SetFireData(BOMB_DIR dir, Vector2& vec);	// 爆風ﾃﾞｰﾀの情報取得用
	void FireUpdate(void);
	MAP_ID GetMapData(Vector2& vec);
	MAP_ID GetMapData(Vector2 & vec, DRAW_DIR dir);
	const Vector2 GetChipSize();
	
private:
	MapCtl();
	~MapCtl();
	struct MapCtlDeleter
	{
		void operator()(MapCtl * mapctl) const 
		{
			delete mapctl;
		}
	};
	static std::unique_ptr<MapCtl, MapCtlDeleter> s_Instance;
	const double	deg[MOVE_DIR_MAX] = { DEG(270), DEG(180) , DEG(0), DEG(90) };
	const Vector2	chipSize;
	VEC2_MAPID		mapData;		// ﾏｯﾌﾟID用の変数
	VEC_FIRE_ID		fireMapData;	// 爆風ID用の変数

};
