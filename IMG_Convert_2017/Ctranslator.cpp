#include "pch.h"
#include "Ctranslator.h"


CTranslator::CTranslator()
{
	_Api = nullptr;
	CreateTesseract();
}

CTranslator::~CTranslator()
{
	_Api->End();
	delete _Api;
}

void CTranslator::CreateTesseract()
{
	if (_Api == nullptr)
		_Api = new tesseract::TessBaseAPI();

	TCHAR chFilePath[256] = { 0, };
	CString strpath = "./tessdata";

	//GetModuleFileName(NULL, (TCHAR *)(LPCTSTR)strpath, 256);
	CString strFolderPath(strpath);
	CString strTemp = strFolderPath;
	//strTemp.Format(_T("%s\\%s"), strFolderPath.Left(strFolderPath.ReverseFind('\\')), _T("tessdata"));

	// Initialize tesseract-ocr with English
	//if (_Api->Init((CStringA)strTemp, "kor+eng", tesseract::OEM_LSTM_ONLY) == -1)
	if (_Api->Init((CStringA)strTemp, "kor+eng"))
	{
		AfxMessageBox(_T("Tesseract Initial ERROR"), MB_OK);

		delete _Api;
		_Api = nullptr;
	}
}

void CTranslator::Translate(cv::Mat Img, CString& strOut)
{
	char *outText;

	_Api->SetPageSegMode(tesseract::PSM_AUTO);
	_Api->SetImage(Img.data, Img.cols, Img.rows, 3, Img.step);
	outText = _Api->GetUTF8Text();
	strOut = UTF8ToANSI(outText);
// 	_Api->End();
// 	delete _Api;
	delete[] outText;
//	CreateTesseract();
}


char* CTranslator::UTF8ToANSI(const char *pszCode)
{
	BSTR    bstrWide;
	char*   pszAnsi;
	int     nLength;

	// Get nLength of the Wide Char buffer
	nLength = MultiByteToWideChar(CP_UTF8, 0, pszCode, strlen(pszCode) + 1,
		NULL, NULL);
	bstrWide = SysAllocStringLen(NULL, nLength);

	// Change UTF-8 to Unicode (UTF-16)
	MultiByteToWideChar(CP_UTF8, 0, pszCode, strlen(pszCode) + 1, bstrWide, nLength);

	// Get nLength of the multi byte buffer
	nLength = WideCharToMultiByte(CP_ACP, 0, bstrWide, -1, NULL, 0, NULL, NULL);
	pszAnsi = new char[nLength];

	// Change from unicode to mult byte
	WideCharToMultiByte(CP_ACP, 0, bstrWide, -1, pszAnsi, nLength, NULL, NULL);
	SysFreeString(bstrWide);

	return pszAnsi;
}
