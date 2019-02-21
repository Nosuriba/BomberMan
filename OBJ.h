#pragma once
#include <string>
#include "DxLib.h"
#include "Vector2.h"
#include "ImageMng.h"

// �`�悷�����
enum DRAW_DIR{
	DIR_DOWN,
	DIR_LEFT,
	DIR_RIGHT,
	DIR_UP,
	DIR_DERTH,
	DIR_MAX
};

enum STATE {
	ST_STAND,
	ST_WALK,
	ST_MAX
};

class OBJ
{
public:
	/* �׽�O�ł��g�����Ƃ��ł��� */
	OBJ(const char(&_keyData)[256],const char(&_keyDataOld)[256], Vector2 offSet);	
	virtual ~OBJ();											
	void  setPos(const Vector2& pos);				
	const Vector2& getPos(void);					
	void  setSize(const Vector2& divSize);			
	const Vector2& getSize(void);					
	virtual void Draw(void);						
	void Draw(const Vector2& pos);					
	void Update(void);
	virtual void UpdateAnim(void);
	void Init(std::string Filename, Vector2 divSize, Vector2 divCnt, Vector2 chipOffset, int speed, int animSpeed = 10, int stateAnimDiv = 2);
	bool CheckActive(void);
private:
	/* �׽���ł̂ݎg�����Ƃ��ł��� */
	virtual void SetMove(void) = 0;
protected:
	/* �e�׽�ƌp�������q�׽�̂ݎg�����Ƃ��ł��� */
	Vector2		pos;					
	Vector2		divSize;				// �`�����߂̻���
	Vector2		divCnt;					// �`�����߂����ߐ�
	Vector2		chipOffset;				// �`�����߂̲Ұ��ID�̓񎟌��z���ł̎g�p�ӏ��̊J�n�ʒu
	Vector2		drawOffset;				
	DRAW_DIR	drawDir;				
	STATE		state;
	std::string	imageName;				// �Ұ�ނ̱�����
	int			speed;					
	int			animCnt;				
	int			animSpeed;				
	int			stateAnimDiv;			// �ð�����̱�Ұ��ݺϐ�
	bool		active;					
	const char	(&keyData)[256];		// �S�Ă̷��̏��擾�p
	const char	(&keyDataOld)[256];		// �Â��S�Ă̷��̏��擾�p
};

