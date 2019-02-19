#include "ImageMng.h"
#include "DxLib.h"

ImageMng *ImageMng::s_Instance = nullptr;		// �ݸ���݂̎��̂�������޼ު��

ImageMng::ImageMng()
{
}

ImageMng::~ImageMng()
{
}

void ImageMng::Create(void)
{
	if (!s_Instance)
	{
		s_Instance = new ImageMng();
	}
}

void ImageMng::Destroy(void)
{
	// ��؂̒��g�ɉ��������Ă�����
	if (s_Instance)
	{
		delete s_Instance;
		s_Instance = nullptr;
	}
}

const VEC_INT & ImageMng::GetID(std::string f_name)
{
	if (imageMap.find(f_name) == imageMap.end())
	{
		imageMap[f_name].resize(1);
		imageMap[f_name][0] = LoadGraph(f_name.c_str());
	}
	return imageMap[f_name];
}

const VEC_INT & ImageMng::GetID(string f_name, Vector2 divSize, Vector2 divCnt, Vector2 chipOffset)
{
	if (imageMap.find(f_name) == imageMap.end())
	{
		imageMap[f_name].resize(divCnt.x * divCnt.y);
		LoadDivGraph(f_name.c_str(), divCnt.x * divCnt.y, divCnt.x, divCnt.y,
			divSize.x, divSize.y, &imageMap[f_name][0], true);
	}
	return imageMap[f_name];
}