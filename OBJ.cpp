#include "OBJ.h"

OBJ::OBJ(const char(&_keyData)[256],const char(&_keyDataOld)[256], Vector2 offSet):keyData(_keyData), keyDataOld(_keyDataOld)
{
	// std::nullptr_t;
	
	// pos = Vector2(0, 0);		// ｷｬﾗ座標の初期化
	active = false;				// 生存ﾌﾗｸﾞしていない状態にする	
	drawOffset = offSet;		// 描画用ｵﾌｾｯﾄの初期化
}

OBJ::~OBJ()
{
	
}

// 自分自身の座標に、入力された座標を代入する
void OBJ::setPos(const Vector2 & pos)
{
	this->pos = pos;
}

// 入力された座標を出力する
const Vector2 & OBJ::getPos(void)
{
	return this->pos;
}
// 自分自身のｻｲｽﾞに、入力されたｻｲｽﾞを代入する
void OBJ::setSize(const Vector2 & divSize)
{
	this->divSize = divSize;
}

// 入力されたｻｲｽﾞを出力する
const Vector2 & OBJ::getSize(void)
{
	return this->divSize;
}

// 描画の中身を設定する
void OBJ::Draw(void)
{
	if (imageName.length() == NULL)
	{
		return;
	}
	DrawGraph(this->drawOffset.x + this->pos.x, this->drawOffset.y + this->pos.y, IMAGE_ID(imageName)[chipOffset.x + chipOffset.y * divCnt.x], true);
}

// 描画の中身を指定する
void OBJ::Draw(const Vector2 & pos)
{
	if (imageName.length() == NULL)
	{
		return;
	}
	DrawGraph(pos.x, pos.y, IMAGE_ID(imageName)[chipOffset.x + chipOffset.y * divCnt.x], true);
}
void OBJ::SetMove(void)
{
}
void OBJ::Update(void)
{
	SetMove();
}

void OBJ::UpdateAnim(void)
{
	// 描画する方向が、横のｺﾏの総数より小さかった場合
	if (drawDir < divCnt.x)
	{
		chipOffset.x = drawDir;
	}
	animCnt++;
	chipOffset.y = state * stateAnimDiv + ((animCnt / animSpeed) % stateAnimDiv);	
}

// ｵﾌﾞｼﾞｪｸﾄの初期化
void OBJ::Init(std::string Filename, Vector2 divSize, Vector2 divCnt, Vector2 chipOffset, int speed, int animSpeed, int stateAnimDiv)
{
	// 画像の分割情報
	ImageMng::GetInstance()->GetID(Filename.c_str(), divSize, divCnt, chipOffset);		
	imageName			= Filename;

	this->divSize		= divSize;
	this->divCnt		= divCnt;
	this->chipOffset	= chipOffset;
	this->speed			= speed;
	this->drawDir		= DIR_DOWN;
	this->animSpeed		= animSpeed;
	this->stateAnimDiv	= stateAnimDiv;
	animCnt				= 0;
	state				= ST_STAND;
	active				= true;
}

bool OBJ::CheckActive(void)
{
	return active;
}
