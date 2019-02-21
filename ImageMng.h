#pragma once
#include <vector>
#include <memory>
#include <map>
#include "Vector2.h"

#define LpImageMng (ImageMng::GetInstance())

using namespace std;
using VEC_INT = vector<int>;

class ImageMng
{
public:		
	static ImageMng & GetInstance()		
	{
		return *s_Instance;				
	}
	const VEC_INT& ImgGetID(std::string f_name);
	const VEC_INT& ImgGetID(std::string f_name, Vector2 divSize, Vector2 divCnt, Vector2 chipOffset);		// �`�悷��摜ID�������Ă�����āA����Ԃ����ފ֐�
private:
	ImageMng();
	~ImageMng();

	struct ImageMngDeleter
	{
		void operator() (ImageMng * image)
		{
			delete image;
		}
	};

	static std::unique_ptr<ImageMng, ImageMngDeleter> s_Instance;			
	std::map<std::string, VEC_INT>imageMap;		// �摜�̏��擾�p

	Vector2 divSize;
	Vector2 divCnt;
	Vector2 chipOffset;
};

