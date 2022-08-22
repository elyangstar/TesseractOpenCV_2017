#pragma once
#include "tesseract/baseapi.h"
#include "leptonica/allheaders.h"
#include "opencv2/opencv.hpp"

class CTranslator
{
private:
	tesseract::TessBaseAPI* _Api;
	tesseract::Tesseract* m_API;

public:
	CTranslator();
	~CTranslator();

	void CreateTesseract();
	void Translate(cv::Mat Img, CString& strOut);
	char* UTF8ToANSI(const char *pszCode);
};