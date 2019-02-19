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
	const VEC_INT& GetID(std::string f_name, Vector2 divSize, Vector2 divCnt, Vector2 chipOffset);		// •`‰æ‚·‚é‰æ‘œID‚ğ‹³‚¦‚Ä‚à‚ç‚Á‚ÄAî•ñ‚ğ•Ô‚·ÒİÊŞŠÖ”
private:
	ImageMng();
	~ImageMng();
	static ImageMng *s_Instance;				
	std::map<std::string, VEC_INT>imageMap;		// ‰æ‘œ‚Ìî•ñæ“¾—p

	Vector2 divSize;
	Vector2 divCnt;
	Vector2 chipOffset;
};

