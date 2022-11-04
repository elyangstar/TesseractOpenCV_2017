
// IMG_Convert_2017Dlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "IMG_Convert_2017.h"
#include "IMG_Convert_2017Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CIMGConvert2017Dlg 대화 상자



CIMGConvert2017Dlg::CIMGConvert2017Dlg(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_IMG_CONVERT_2017_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CIMGConvert2017Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CIMGConvert2017Dlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_IMG_MAT_LOAD, &CIMGConvert2017Dlg::OnBnClickedImgMatLoad)
	ON_BN_CLICKED(IDC_LOAD_VIDEO, &CIMGConvert2017Dlg::OnBnClickedLoadVideo)
	ON_BN_CLICKED(IDC_LOAD_VIDEO2, &CIMGConvert2017Dlg::OnBnClickedLoadVideo2)
END_MESSAGE_MAP()


// CIMGConvert2017Dlg 메시지 처리기

BOOL CIMGConvert2017Dlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CIMGConvert2017Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CIMGConvert2017Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CIMGConvert2017Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CIMGConvert2017Dlg::OnBnClickedImgMatLoad()
{
	CFileDialog fileDlg(TRUE, NULL, NULL, OFN_READONLY, _T("image file(*.jpg;*.bmp;*.png;)|*.jpg;*.bmp;*.png;|All Files(*.*)|*.*||"));
	BOOL bflag = FALSE;

	CString path = "";
	if (fileDlg.DoModal() == IDOK)
	{
		path = fileDlg.GetPathName();

		CT2CA pszString(path);
		std::string strPath(pszString);
		bflag = ((CButton*)GetDlgItem(IDC_GRAY_USE))->GetCheck();

		Mat matImage;

		if (bflag == FALSE)
			matImage = imread(strPath, IMREAD_UNCHANGED);
		else if (bflag == TRUE)
			matImage = imread(strPath, IMREAD_GRAYSCALE);

		
		resize(matImage, m_matImage, Size(matImage.cols - matImage.cols % 4, matImage.rows - matImage.rows % 4));

		//2번 Row 참고(바로 아래)
		CreateBitmapInfo(m_matImage.cols, m_matImage.rows, m_matImage.channels() * 8);
		//Picture Control에 추가하기 위함
		DrawImage();
	}
}

void CIMGConvert2017Dlg::CreateBitmapInfo(int w, int h, int bpp)
{
	if (m_pBitmapInfo != NULL)
	{
		delete m_pBitmapInfo;
		m_pBitmapInfo = NULL;
	}

	if (bpp == 8)
		m_pBitmapInfo = (BITMAPINFO *) new BYTE[sizeof(BITMAPINFO) + 255 * sizeof(RGBQUAD)];
	else // 24 or 32bit
		m_pBitmapInfo = (BITMAPINFO *) new BYTE[sizeof(BITMAPINFO)];

	m_pBitmapInfo->bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	m_pBitmapInfo->bmiHeader.biPlanes = 1;
	m_pBitmapInfo->bmiHeader.biBitCount = bpp;
	m_pBitmapInfo->bmiHeader.biCompression = BI_RGB;
	m_pBitmapInfo->bmiHeader.biSizeImage = 0;
	m_pBitmapInfo->bmiHeader.biXPelsPerMeter = 0;
	m_pBitmapInfo->bmiHeader.biYPelsPerMeter = 0;
	m_pBitmapInfo->bmiHeader.biClrUsed = 0;
	m_pBitmapInfo->bmiHeader.biClrImportant = 0;

	if (bpp == 8)
	{
		for (int i = 0; i < 256; i++)
		{
			m_pBitmapInfo->bmiColors[i].rgbBlue = (BYTE)i;
			m_pBitmapInfo->bmiColors[i].rgbGreen = (BYTE)i;
			m_pBitmapInfo->bmiColors[i].rgbRed = (BYTE)i;
			m_pBitmapInfo->bmiColors[i].rgbReserved = 0;
		}
	}

	m_pBitmapInfo->bmiHeader.biWidth = w;
	m_pBitmapInfo->bmiHeader.biHeight = -h;
	
}

void CIMGConvert2017Dlg::DrawImage()
{
	CClientDC dc(GetDlgItem(IDC_PIC_IMG));

	CRect rect;
	GetDlgItem(IDC_PIC_IMG)->GetClientRect(&rect);
	
	// 영상 비율 계산 및 반영
// 	float fImageRatio = float(m_matImage.cols) / float(m_matImage.rows);
// 	float fRectRatio = float(rect.right) / float(rect.bottom);
// 	float fScaleFactor;
// 	if (fImageRatio < fRectRatio) {
// 		fScaleFactor = float(rect.bottom) / float(m_matImage.rows); //TRACE("%f",fScaleFactor);
// 		int rightWithRatio = m_matImage.cols * fScaleFactor;
// 		float halfOfDif = ((float)rect.right - (float)rightWithRatio) / (float)2;
// 		rect.left = halfOfDif;
// 		rect.right = rightWithRatio;
// 	}
// 	else {
// 		fScaleFactor = float(rect.right) / float(m_matImage.cols); //TRACE("%f",fScaleFactor);
// 		int bottomWithRatio = m_matImage.rows * fScaleFactor;
// 		float halfOfDif = ((float)rect.bottom - (float)bottomWithRatio) / (float)2;
// 		rect.top = halfOfDif;
// 		rect.bottom = bottomWithRatio;
// 	}
// 	

	SetStretchBltMode(dc.GetSafeHdc(), COLORONCOLOR);

	StretchDIBits(dc.GetSafeHdc(), 0, 0, rect.Width(), rect.Height(), 0, 0, m_matImage.cols, m_matImage.rows, m_matImage.data, m_pBitmapInfo, DIB_RGB_COLORS, SRCCOPY);
}

void CIMGConvert2017Dlg::OnBnClickedLoadVideo()
{
// 	CString strpath = "D:\\TEST.mp4";
// 
// 	CT2CA pszString(strpath);
// 	std::string strPath(pszString);
// 
// 	VideoCapture cap(strPath);
// 
// 	if (!cap.isOpened())
// 	{
// 		printf("Can't open the camera");
// 		return;
// 	}
// 
// 	Mat img;
// 
// 	while (1)
// 	{
// 		cap >> img;
// 
// 		if (img.empty())
// 		{
// 			printf("empty image");
// 			return;
// 		}
// 
// 		imshow("camera img", img);
// 
// 		if (waitKey(25) == 27)
// 			break;
// 	}
}


#include <tesseract/baseapi.h>
#include <leptonica/allheaders.h>

void CIMGConvert2017Dlg::OnBnClickedLoadVideo2()
{
	CString strOut = "";
	translator.Translate(m_matImage, strOut);

	SaveTxtFile(strOut);

	AfxMessageBox(strOut);
}

void CIMGConvert2017Dlg::SaveTxtFile(CString strData)
{
	CString strGlassidTxtPath = "D:\\convert.txt";

	FILE* pf = fopen(strGlassidTxtPath, "a");
	if (pf)
	{	
		char buffer[2048] = {};
		strcpy(buffer, strData);
		fputs(buffer, pf);
// 		{
// 			
// 		}
		fclose(pf);
	}
}

char* CIMGConvert2017Dlg::UTF8ToANSI(const char *pszCode)
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
