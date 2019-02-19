#pragma once
#include <vector>
#include <map>
#include "Vector2.h"

using namespace std;
using VEC_INT = vector<int>;

class ImageMng
{
public:
	static void Create(void);			
	static void Destroy(void);			
	static ImageMng *GetInstance()		
	{
		return s_Instance;				
	}
	const VEC_INT& GetID(std::string f_name);
	const VEC_INT& GetID(std::string f_name, Vector2 divSize, Vector2 divCnt, Vector2 chipOffset);		// �`�悷��摜ID�������Ă�����āA����Ԃ����ފ֐�
private:
	ImageMng();
	~ImageMng();
	static ImageMng *s_Instance;				
	std::map<std::string, VEC_INT>imageMap;		// �摜�̏��擾�p

	Vector2 divSize;
	Vector2 divCnt;
	Vector2 chipOffset;
};

