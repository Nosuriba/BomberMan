#pragma once
#include "Vector2.h"
#include "OBJ.h"
#include "Bomb.h"
#include <vector>

// ׼ޱ݂̒�`
#define PAI (3.141592f)
#define DEG(X) ((X)*PAI/180.0f)

// ϯ��ID
enum MAP_ID
{
	MAP_NON,			// �����Ȃ����
	MAP_EDIT_PL,		// ��ڲ԰
	MAP_EDIT_EM1,		// �G���1
	MAP_EDIT_EM2,		// �G���2
	MAP_ITEM_FIRE,		// ����(���j�͈̔͂��L����)
	MAP_ITEM_BOMB,		// ����(���e�̐ݒu�ł������������)
	MAP_ITEM_SWITCH,	// ����(�D�������ݸނŔ��j���邱�Ƃ��ł���)
	MAP_ITEM_SHOSE,		// ����(��ڲ԰�̽�߰�ނ������Ȃ�)
	MAP_WALL1,			// �Ԃ���
	MAP_WALL2,			// ����
	MAP_BLOCK,			// �󂹂��
	MAP_FIRE,			// �\���̐ݒ�(����)
	MAP_FLOOR1,			// �Ԃ���
	MAP_FLOOR2,			// ����
	MAP_BOMB,			// �\���̐ݒ�(���e��ID)
	MAP_EDIT_CURSOR,	// ����
	MAP_ID_MAX			// ϯ��ID�̍ő�l
};

// ϯ��ID�̎w��
#define START_EDIT_CHIP MAP_NON			// ��ި��Ӱ�ނ̍ŏ�������
#define END_EDIT_CHIP	MAP_BLOCK		// ��ި��Ӱ�ނ̍Ō������
#define START_GAME_CHIP	MAP_ITEM_FIRE	// �ް�Ӱ�ނ̍ŏ�������
#define END_GAME_CHIP	MAP_FLOOR2		// �ް�Ӱ�ލŌ������
#define BLAST_TIME_MAX	(60)
// vector�̓񎟌��z��̌^��ς�������
using VEC2_MAPID = vector<vector<MAP_ID>>;

struct DataHeader {
	char fileID[13];		// ̧�ق�ID
	unsigned char verID;	// ̧�ق��ް�ޮݔԍ�
	unsigned char rez1[2];	// �ײ��ĕ��̗\��̈�
	int sizeX;				// ϯ�߂̻���X
	int sizeY;				// ϯ�߂̻���Y
	unsigned char rez2[3];	// sum�l�̗\��̈�
	unsigned char sum;		// sum�l
};

struct FireStr {
	bool flag;
	int count;
};
// typedef vector<vector<vector<FireStr>>> VEC_FIRE_ID
using VEC_FIRE_ID = vector<vector<vector<FireStr>>>;		// �����̃f�[�^�^ID([Y�̌�][X�̌�][�����̕���])

#define BBM_ID_NAME "BBM_MAP_DATA"
#define BBM_VER_ID	0x01					// ����ް�݂��ް�ޮ�ID

#define LpMapCtl MapCtl::GetInstance()		// MapCtl���ݸ��߲���

class MapCtl
{
public:
	static MapCtl & GetInstance()
	{
		return *s_Instance;
	}
	bool MapReset(void);							// ϯ���ް��̍Đݒ�
	bool MapSave(void);
	bool MapLoad(void);
	void SetPlayer(void);						// ��ڲ԰�̾�ı��ߗp
	void MapDelete(void);						// �쐬����ϯ���ް��̍폜�p
	void MapRandom(void);
	void MapDraw(void);
	bool SetMapData(MAP_ID id, Vector2& vec);		// ϯ���ް��̏��擾�p	
	bool SetFireData(BOMB_DIR dir, Vector2& vec);	// �����ް��̏��擾�p
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
	VEC2_MAPID		mapData;		// ϯ��ID�p�̕ϐ�
	VEC_FIRE_ID		fireMapData;	// ����ID�p�̕ϐ�

};
