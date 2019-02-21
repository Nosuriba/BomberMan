#pragma once
#include <string>
#include "DxLib.h"
#include "Vector2.h"
#include "ImageMng.h"

// 描画する向き
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
	/* ｸﾗｽ外でも使うことができる */
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
	/* ｸﾗｽ内でのみ使うことができる */
	virtual void SetMove(void) = 0;
protected:
	/* 親ｸﾗｽと継承した子ｸﾗｽのみ使うことができる */
	Vector2		pos;					
	Vector2		divSize;				// 描画ﾁｯﾌﾟのｻｲｽﾞ
	Vector2		divCnt;					// 描画ﾁｯﾌﾟのﾁｯﾌﾟ数
	Vector2		chipOffset;				// 描画ﾁｯﾌﾟのｲﾒｰｼﾞIDの二次元配列上での使用箇所の開始位置
	Vector2		drawOffset;				
	DRAW_DIR	drawDir;				
	STATE		state;
	std::string	imageName;				// ｲﾒｰｼﾞのｱｸｾｽｷｰ
	int			speed;					
	int			animCnt;				
	int			animSpeed;				
	int			stateAnimDiv;			// ｽﾃｰﾀｽ事のｱﾆﾒｰｼｮﾝｺﾏ数
	bool		active;					
	const char	(&keyData)[256];		// 全てのｷｰの情報取得用
	const char	(&keyDataOld)[256];		// 古い全てのｷｰの情報取得用
};

