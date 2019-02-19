#include "OBJ.h"

OBJ::OBJ(const char(&_keyData)[256],const char(&_keyDataOld)[256], Vector2 offSet):keyData(_keyData), keyDataOld(_keyDataOld)
{
	// std::nullptr_t;
	
	// pos = Vector2(0, 0);		// ��׍��W�̏�����
	active = false;				// �����׸ނ��Ă��Ȃ���Ԃɂ���	
	drawOffset = offSet;		// �`��p�̾�Ă̏�����
}

OBJ::~OBJ()
{
	
}

// �������g�̍��W�ɁA���͂��ꂽ���W��������
void OBJ::setPos(const Vector2 & pos)
{
	this->pos = pos;
}

// ���͂��ꂽ���W���o�͂���
const Vector2 & OBJ::getPos(void)
{
	return this->pos;
}
// �������g�̻��ނɁA���͂��ꂽ���ނ�������
void OBJ::setSize(const Vector2 & divSize)
{
	this->divSize = divSize;
}

// ���͂��ꂽ���ނ��o�͂���
const Vector2 & OBJ::getSize(void)
{
	return this->divSize;
}

// �`��̒��g��ݒ肷��
void OBJ::Draw(void)
{
	if (imageName.length() == NULL)
	{
		return;
	}
	DrawGraph(this->drawOffset.x + this->pos.x, this->drawOffset.y + this->pos.y, IMAGE_ID(imageName)[chipOffset.x + chipOffset.y * divCnt.x], true);
}

// �`��̒��g���w�肷��
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
	// �`�悷��������A���̺ς̑�����菬���������ꍇ
	if (drawDir < divCnt.x)
	{
		chipOffset.x = drawDir;
	}
	animCnt++;
	chipOffset.y = state * stateAnimDiv + ((animCnt / animSpeed) % stateAnimDiv);	
}

// ��޼ު�Ă̏�����
void OBJ::Init(std::string Filename, Vector2 divSize, Vector2 divCnt, Vector2 chipOffset, int speed, int animSpeed, int stateAnimDiv)
{
	// �摜�̕������
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
