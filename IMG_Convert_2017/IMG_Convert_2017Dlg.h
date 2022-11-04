
// IMG_Convert_2017Dlg.h: 헤더 파일
//

#pragma once
#include <opencv2/opencv.hpp>
#include "Ctranslator.h"

using namespace cv;

// CIMGConvert2017Dlg 대화 상자
class CIMGConvert2017Dlg : public CDialog
{
// 생성입니다.
public:
	CIMGConvert2017Dlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_IMG_CONVERT_2017_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnBnClickedImgMatLoad();
	
	Mat m_matImage;
	BITMAPINFO *m_pBitmapInfo; // Bitmap 정보를 담고 있는 구조체.
	void	CreateBitmapInfo(int w, int h, int bpp);
	void	DrawImage();
	afx_msg void OnBnClickedLoadVideo();
	afx_msg void OnBnClickedLoadVideo2();

	void SaveTxtFile(CString strData);
	char* UTF8ToANSI(const char *pszCode);
	CTranslator translator;
};
