#include <Windows.h>
#include "SceneState.h"
#include "ImageMng.h"
#include "MapCtl.h"
#include "Player.h"
#include "Enemy.h"
#include "Enemy2.h"
#include "DxLib.h"

MapCtl *MapCtl::s_Instance = nullptr;

MapCtl::MapCtl()
{
}

MapCtl::~MapCtl()
{
}

void MapCtl::Create(void)
{
	if (!s_Instance)
	{
		s_Instance = new MapCtl();
	}
}

void MapCtl::Destroy(void)
{
	if (s_Instance)
	{
		delete s_Instance;
		s_Instance = nullptr;
	}
}

bool MapCtl::MapReset(void)
{
	mapData.clear();					// ﾏｯﾌﾟﾃﾞｰﾀのﾒﾓﾘを消去
	// ﾏｯﾌﾟﾃﾞｰﾀのﾒﾓﾘ確保
	mapData.resize(mapSize.y);
	for (unsigned int i = 0; i < mapData.size(); i++)
	{
		mapData[i].resize(mapSize.x);	// 縦ﾏｽ1個の中に、横ﾏｽの数分ﾒﾓﾘを確保する
	}
	// ﾏｯﾌﾟIDの初期設定
	for (unsigned int y = 0; y < mapData.size(); y++)
	{
		for (unsigned int x = 0; x < mapData[y].size();x++)
		{
			mapData[y][x] = MAP_NON;
		}
	}

	fireMapData.clear();		// 爆風のﾒﾓﾘを消去

	// 爆風のﾒﾓﾘ確保
	fireMapData.resize(mapSize.y);
	for (unsigned int i = 0; i < mapData.size(); i++)
	{
		fireMapData[i].resize(mapSize.x);
	}
	for (unsigned int y = 0; y < fireMapData.size(); y++)
	{
		for (unsigned int x = 0; x < fireMapData[y].size(); x++)
		{
			fireMapData[y][x].resize(MOVE_DIR_MAX);
			for (int dir = 0; dir < MOVE_DIR_MAX; dir++)
			{
				fireMapData[y][x][dir].flag = false;
				fireMapData[y][x][dir].count = 0;
			}
		}
	}

	return true;
}

// ﾃﾞｰﾀの書き込み
bool MapCtl::MapSave(void)
{
	// DxLib openFile
	DataHeader expData = {
		BBM_ID_NAME,		// ﾌｧｲﾙのID
		BBM_VER_ID,			// ﾌｧｲﾙのﾊﾞｰｼﾞｮﾝ番号
		{ 0,0 },			// ｱﾗｲﾒﾝﾄ分の予約領域
		mapSize.x,			// ﾏｯﾌﾟのｻｲｽﾞX
		mapSize.y,			// ﾏｯﾌﾟのｻｲｽﾞY
		{ 0,0,0 },			// sum値の予約領域
		0xff				// sum値
	};

	// sum値の中にﾏｯﾌﾟﾃﾞｰﾀの中身を加算する
	for (unsigned int y = 0; y < mapData.size(); y++)
	{
		for (unsigned int x = 0; x < mapData[y].size(); x++)
		{
			expData.sum += mapData[y][x];
		}
	}
	// 特定ﾌｧｲﾙにﾃﾞｰﾀを保存する
	FILE *fp;
	// FileRead_open(BBM_ID_NAME, FALSE);
	fopen_s(&fp, "Data/mapData.map", "wb");
	fwrite(&expData, sizeof(DataHeader), 1, fp);
	for (unsigned int y = 0; y < mapData.size(); y++)
	{
		fwrite(&mapData[y][0], mapData[y].size() * sizeof(MAP_ID), 1, fp);
	}
	fclose(fp);

	return true;
}

// ﾃﾞｰﾀの読み込み
bool MapCtl::MapLoad(void)
{
	bool rtnFlag = true;
	DataHeader expData{
		BBM_ID_NAME,		// ﾌｧｲﾙのID
		BBM_VER_ID,			// ﾌｧｲﾙのﾊﾞｰｼﾞｮﾝ番号
		{ 0,0 },			// ｱﾗｲﾒﾝﾄ分の予約領域
		mapSize.x,			// ﾏｯﾌﾟのｻｲｽﾞX
		mapSize.y,			// ﾏｯﾌﾟのｻｲｽﾞY
		{ 0,0,0 },			// sum値の予約領域
		0x00				// sum値
	};

	// 特定ﾌｧｲﾙのﾃﾞｰﾀを読み込む
	FILE *fp;
	fopen_s(&fp, "Data/mapData.map", "rb");
	fread(&expData, sizeof(DataHeader), 1, fp);
	for (unsigned int y = 0; y < mapData.size(); y++)
	{
		fread(&mapData[y][0], mapData[y].size() * sizeof(MAP_ID), 1, fp);
	}
	if (LpGameTask.GetMode() == SCENE::MAIN)
	{
		// プレイヤー又は敵のIDが見つかった時、キャラクターの設定を行う
		SetPlayer();	
	}
	fclose(fp);
	return rtnFlag;
}
void MapCtl::SetPlayer(void)
{
	OBJ *tmp;
	// ﾌﾟﾚｲﾔｰの初期化
	for (unsigned int y = 0; y < mapData.size();y++)
	{
		for (unsigned int x = 0; x < mapData[y].size(); x++)
		{
			switch (mapData[y][x])
			{
			case MAP_EDIT_PL:
				tmp = new Player(LpGameTask.keyDataPub,
					LpGameTask.keyDataOldPub,
					LpGameTask.GetOffset() + Vector2(0, -20));
				tmp->Init("image/bomberman.png", Vector2(100 / 5, 128 / 4), Vector2(5, 4), Vector2(0, 0), 2);
				tmp->setPos(Vector2(LpGameTask.chipSize.x * x, LpGameTask.chipSize.y * y));
				LpGameTask.SetObj(tmp);
				break;
			case MAP_EDIT_EM1:
				// 仮設定
				tmp = new Enemy(LpGameTask.keyDataPub,
					LpGameTask.keyDataOldPub,
					LpGameTask.GetOffset() + Vector2(0, -20));
				tmp->Init("image/enemy1.png", Vector2(100 / 5, 128 / 4), Vector2(5, 4), Vector2(0, 0), 2);
				tmp->setPos(Vector2(LpGameTask.chipSize.x * x, LpGameTask.chipSize.y * y));
				LpMapCtl->SetMapData(MAP_EDIT_EM1, Vector2(LpGameTask.chipSize.x * x, LpGameTask.chipSize.y * y));
				LpGameTask.SetObj(tmp);
				break;
			case MAP_EDIT_EM2:
				tmp = new Enemy2(LpGameTask.keyDataPub,
					LpGameTask.keyDataOldPub,
					LpGameTask.GetOffset() + Vector2(0, -20));
				tmp->Init("image/enemy2.png", Vector2(100 / 5, 128 / 4), Vector2(5, 4), Vector2(0, 0), 2);
				tmp->setPos(Vector2(LpGameTask.chipSize.x * x, LpGameTask.chipSize.y * y));
				LpGameTask.SetObj(tmp);
				break;
			default:
				break;
			}
		}
	}
}
void MapCtl::MapDelete(void)
{
	// エディット内容の削除
	for (unsigned int y = 0; y < mapData.size() - 2; y++)
	{
		for (unsigned int x = 0; x < mapData[y].size() - 2;x++)
		{
			// ﾏｯﾌﾟIDが外側の壁でない場合
			if (mapData[y + 1][x + 1] != MAP_NON)
			{
				mapData[y + 1][x + 1] = MAP_NON;
			}
		}
	}
}

void MapCtl::MapRandom(void)
{
	for (unsigned int y = 0; y < mapData.size() - 2; y += 2)
	{
		for (unsigned int x = 0; x < mapData[y].size() - 2; x += 2)
		{
			mapData[y + 1][x + 1] = MAP_WALL2;
		}
	}
}

void MapCtl::MapDraw(void)
{
	// ﾏｯﾌﾟのﾏｽの数分描画する
	for (int y = 0; y < mapSize.y; y++)
	{
		for (int x = 0; x < mapSize.x; x++)
		{
			if ((LpGameTask.GetMode() == SCENE::EDIT && mapData[y][x] >= START_EDIT_CHIP && mapData[y][x] <= END_EDIT_CHIP)
		    || (LpGameTask.GetMode() == SCENE::MAIN && mapData[y][x] >= START_GAME_CHIP && mapData[y][x] <= END_GAME_CHIP))
			{
				DrawGraph(x * LpGameTask.chipSize.x + LpGameTask.GetOffset().x,
					y * LpGameTask.chipSize.y + LpGameTask.GetOffset().y,
					IMAGE_ID("image/map.png")[mapData[y][x]], true);
			}
		}
	}
	// 外側の壁を描画
	for (unsigned int y = 0; y < (int)mapData.size(); y++)
	{
		mapData[y][0] = MAP_WALL2;
		mapData[y][MAP_DATA_X - 1] = MAP_WALL2;
		for (unsigned int x = 0; x < (int)mapData[y].size();x++)
		{
			mapData[0][x] = MAP_WALL2;
			mapData[MAP_DATA_Y - 1][x] = MAP_WALL2;
		}
	}
	// 爆風の描画
	for (unsigned int y = 0; y < fireMapData.size(); y++)
	{
		for (unsigned int x = 0; x < fireMapData[y].size(); x++)
		{
			// 爆風がｸﾛｽした場合
			if ((fireMapData[y][x][MOVE_DIR_DOWN].flag || fireMapData[y][x][MOVE_DIR_UP].flag)
			&&  (fireMapData[y][x][MOVE_DIR_LEFT].flag || fireMapData[y][x][MOVE_DIR_RIGHT].flag))
			{
				DrawGraph(x * LpGameTask.chipSize.x + LpGameTask.GetOffset().x,
					y * LpGameTask.chipSize.y + LpGameTask.GetOffset().y,
					IMAGE_ID("image/fire.png")[0], true);
			}
			else
			{
				// 爆風がｸﾛｽしなかった場合
				for (unsigned int dir = 0; dir < MOVE_DIR_MAX; dir++)
				{
					if (fireMapData[y][x][dir].flag)
					{
						Vector2 firPos = Vector2(
						x * LpGameTask.chipSize.x + LpGameTask.GetOffset().x + LpGameTask.chipSize.x / 2,
						y * LpGameTask.chipSize.y + LpGameTask.GetOffset().y + LpGameTask.chipSize.y / 2 
						);

						DrawRotaGraph(firPos.x, firPos.y, 1.0f, deg[dir], IMAGE_ID("image/fire.png")[1], true);
					}
				}
			}
		}
	}
}

bool MapCtl::SetMapData(MAP_ID id, Vector2 & vec)
{
	Vector2 tmp(vec.x / LpGameTask.chipSize.x, vec.y / LpGameTask.chipSize.y);
	// ﾏｯﾌﾟIDの範囲指定
	if ((tmp.y >= 0 && tmp.y < (int)mapData.size())
		&& (tmp.x >= 0 && tmp.y < (int)mapData[tmp.y].size()))
	{
		mapData[tmp.y][tmp.x] = id;
		return true;
	}
	return false;
}

bool MapCtl::SetFireData(BOMB_DIR dir, Vector2 & vec)
{
	Vector2 tmp(vec.x / LpGameTask.chipSize.x, vec.y / LpGameTask.chipSize.y);

	if ((tmp.y >= 0 && (unsigned int)tmp.y < fireMapData.size())
		&& (tmp.x >= 0 && (unsigned int)tmp.x < fireMapData[tmp.y].size()))
	{
		fireMapData[tmp.y][tmp.x][dir].flag = true;
		fireMapData[tmp.y][tmp.x][dir].count = 0;
		return true;
	}
	return false;
}

void MapCtl::FireUpdate(void)
{
	for (int y = 0; y < mapSize.y; y++)
	{
		for (int x = 0; x < mapSize.x; x++)
		{
			for (int dir = 0; dir < MOVE_DIR_MAX; dir++)
			{
				if (fireMapData[y][x][dir].flag)
				{
					fireMapData[y][x][dir].count++;
					if (fireMapData[y][x][dir].count >= BLAST_TIME_MAX)
					{
						fireMapData[y][x][dir].flag = false;

					}
				}
			}
		}
	}
}

MAP_ID MapCtl::GetMapData(Vector2 & vec)
{
	Vector2 tmp(vec.x, vec.y);
	// ﾏｯﾌﾟIDの範囲指定
	if ((tmp.y >= 0 && tmp.y < (int)mapData.size())
		&& (tmp.x >= 0 && tmp.x < (int)mapData[tmp.y].size()))
	{
		return mapData[tmp.y + 1][tmp.x + 1];
	}
	return MAP_NON;
}

MAP_ID MapCtl::GetMapData(Vector2 & vec, DRAW_DIR dir)
{
	Vector2 tmp(vec.x, vec.y);
	switch (dir)
	{
	case DIR_DOWN:
		tmp.y += LpGameTask.chipSize.y + 1;
		break;
	case DIR_LEFT:
		tmp.x--;
		break;
	case DIR_RIGHT:
		tmp.x += LpGameTask.chipSize.x + 1;
		break;
	case DIR_UP:
		tmp.y--;
		break;
	default:
		break;
	}
	tmp.x /= LpGameTask.chipSize.x;
	tmp.y /= LpGameTask.chipSize.y;

	// ﾏｯﾌﾟIDの範囲指定
	if ((tmp.y >= 0 && tmp.y < (int)mapData.size())
		&& (tmp.x >= 0 && tmp.x < (int)mapData[tmp.y].size()))
	{
		return mapData[tmp.y][tmp.x];
	}
	return MAP_NON;
}
