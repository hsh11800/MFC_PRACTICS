
// MfcCircleMoveDlg.cpp: 구현 파일
//
#include "pch.h"
#include "framework.h"
#include "MfcCircleMove.h"
#include "MfcCircleMoveDlg.h"
#include "afxdialogex.h"
#include "Process.h"
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


// CMfcCircleMoveDlg 대화 상자



CMfcCircleMoveDlg::CMfcCircleMoveDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCCIRCLEMOVE_DIALOG, pParent)
	, m_startX(0)
	, m_startY(0)
	, m_dstX(0)
	, m_dstY(0)
	, m_Radius(0)
	, m_mapHeight(INVALID_VALUE)
	, m_mapWidth(INVALID_VALUE)
	, m_openCircleCenterX(0)
	, m_openCircleCenterY(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMfcCircleMoveDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_startX);
	DDX_Text(pDX, IDC_EDIT2, m_startY);
	DDX_Text(pDX, IDC_EDIT3, m_dstX);
	DDX_Text(pDX, IDC_EDIT4, m_dstY);
	DDX_Text(pDX, IDC_EDIT6, m_openCircleCenterX);
	DDX_Text(pDX, IDC_EDIT5, m_openCircleCenterY);
}

BEGIN_MESSAGE_MAP(CMfcCircleMoveDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_DRAW, &CMfcCircleMoveDlg::OnBnClickedBtnDraw)
	ON_BN_CLICKED(IDC_BTN_ACTION, &CMfcCircleMoveDlg::OnBnClickedBtnAction)
	ON_BN_CLICKED(IDC_BTN_LOAD_IMG, &CMfcCircleMoveDlg::OnBnClickedBtnLoadImg)
END_MESSAGE_MAP()


// CMfcCircleMoveDlg 메시지 처리기

BOOL CMfcCircleMoveDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	MY_ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	MY_ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		MY_ASSERT(bNameValid);
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
	srand(static_cast<unsigned int>(time(NULL)));

	CRect rect;
	GetWindowRect(&rect);

	m_mapWidth = rect.Width() - MAP_START_X;
	m_mapHeight = rect.Height() - MAP_START_Y;

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CMfcCircleMoveDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CMfcCircleMoveDlg::OnPaint()
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
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CMfcCircleMoveDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMfcCircleMoveDlg::OnBnClickedBtnDraw()
{
	ReadEditControl();
	if (!isValidCirclePoint()) {
		MessageBox(_T("input circle Start and Dst Point"));
		return;
	}
	MakeInitImage();

	m_Radius = rand() % MAX_RADIUS;
	DrawCircle(m_startX, m_startY);

	UpdateDisplay();

}


void CMfcCircleMoveDlg::OnBnClickedBtnAction()
{
	ReadEditControl();
	static int s_centerX = m_startX;
	static int s_centerY = m_startY;

	MakeInitImage();

	const char* imgPath = ".\\image\\";

	for (int actionCount = 1; actionCount <= MOVE_COUNT; ++actionCount) {

		ResetCircle(s_centerX, s_centerY);
		s_centerX = m_startX + static_cast<int>(static_cast<double>(m_dstX - m_startX) / MOVE_COUNT * actionCount + 0.5);
		s_centerY = m_startY + static_cast<int>(static_cast<double>(m_dstY - m_startY) / MOVE_COUNT * actionCount + 0.5);
		DrawCircle(s_centerX, s_centerY);
		const bool bSaved = SaveImage(imgPath, actionCount - 1);

		MY_ASSERT(bSaved);
		Sleep(10);
	}

	ResetCircle(s_centerX, s_centerY);
	s_centerX = m_dstX;
	s_centerY = m_dstY;
	DrawCircle(s_centerX, s_centerY);
	const bool bSaved = SaveImage(imgPath, MOVE_COUNT);
	MY_ASSERT(bSaved);

}


bool CMfcCircleMoveDlg::isValidCirclePoint() const
{
	if (m_startX == INVALID_VALUE) {
		return false;
	}
	if (m_startY == INVALID_VALUE) {
		return false;
	}
	if (m_dstX == INVALID_VALUE) {
		return false;
	}
	if (m_dstY == INVALID_VALUE) {
		return false;
	}
	return true;
}





void CMfcCircleMoveDlg::MakeInitImage()
{
	if (!m_image.IsNull()) {
		m_image.Destroy();
	}


	MY_ASSERT(m_mapWidth != INVALID_VALUE);
	MY_ASSERT(m_mapHeight != INVALID_VALUE);
	MY_ASSERT(m_mapWidth > 0);
	MY_ASSERT(m_mapHeight > 0);

	m_image.Create(m_mapWidth, -m_mapHeight, MAP_BPP);
	if (MAP_BPP == 8) {
		static RGBQUAD rgb[COLOR_NUM];
		for (int i = 0; i < COLOR_NUM; ++i) {
			rgb[i].rgbRed = i;
			rgb[i].rgbBlue = i;
			rgb[i].rgbGreen = i;
		}
		m_image.SetColorTable(0, COLOR_NUM, rgb);
	}
	unsigned char* fm = static_cast<unsigned char*>(m_image.GetBits());

	const int nPitch = m_image.GetPitch();
	ASSERT(nPitch > 0);
	memset(fm, MAP_COLOR, sizeof(fm[0]) * nPitch * m_mapHeight);

}



void CMfcCircleMoveDlg::DrawCircle(const int nCenterX, const int nCenterY)
{
	const int nWidth = m_image.GetWidth();
	const int nHeight = m_image.GetHeight();
	const int nPitch = m_image.GetPitch();

	const int drawStartX = max(nCenterX - m_Radius, 0);
	const int drawStartY = max(nCenterY - m_Radius, 0);

	const int drawEndX = min(nCenterX + m_Radius, nWidth);
	const int drawEndY = min(nCenterY + m_Radius, nHeight);

	unsigned char* fm = static_cast<unsigned char*>(m_image.GetBits());




	for (int y = drawStartY; y < drawEndY; ++y) {
		bool bLastInCircle = false;
		for (int x = drawStartX; x < drawEndX; ++x) {
			if (!IsInCircle(x, y, nCenterX, nCenterY, m_Radius)) {
				if (bLastInCircle) {
					break;
				}
				continue;
			}
			bLastInCircle = true;
			fm[y * nPitch + x] = CIRCLE_COLOR;

		}
	}


	UpdateDisplay();

}

bool CMfcCircleMoveDlg::IsInCircle(const int x, const int y, const int nCenterX, const int nCenterY, const int nRaduis)
{
	if ((x - nCenterX) * (x - nCenterX) + (y - nCenterY) * (y - nCenterY) <= nRaduis * nRaduis) {
		return true;
	}
	return false;
}




void CMfcCircleMoveDlg::ResetCircle(const int nCenterX, const int nCenterY)
{
	const int nWidth = m_image.GetWidth();
	const int nHeight = m_image.GetHeight();
	const int nPitch = m_image.GetPitch();

	const int drawStartX = max(nCenterX - m_Radius, 0);
	const int drawStartY = max(nCenterY - m_Radius, 0);

	const int drawEndX = min(nCenterX + m_Radius, nWidth);
	const int drawEndY = min(nCenterY + m_Radius, nHeight);

	unsigned char* fm = static_cast<unsigned char*>(m_image.GetBits());


	const int nXLen = drawEndX - drawStartX;
	for (int y = drawStartY; y < drawEndY; ++y) {
		memset(fm + y * nPitch + drawStartX, MAP_COLOR, sizeof(fm[0]) * nXLen);
	}
}


bool CMfcCircleMoveDlg::SaveImage(const char* path, const int imgNum)
{
	CString directoryPath;
	directoryPath = path;

	CreateDirectory(directoryPath, NULL);

	char nImgPath[128];
	sprintf(nImgPath, "%s%d.bmp", path, imgNum);
	CString nPathString;
	nPathString = nImgPath;
	HRESULT hr = m_image.Save(nPathString);
	return SUCCEEDED(hr);
}


void CMfcCircleMoveDlg::OnBnClickedBtnLoadImg()
{
	CString dirdir;
	CString imgDir;

	CFileDialog fileDlg(TRUE, NULL, NULL, OFN_EXPLORER | OFN_HIDEREADONLY,
		L"모든파일(*.*)|*.*|bmp파일(*.bmp)|*.bmp||");

	if (fileDlg.DoModal() == IDOK)
	{
		imgDir = fileDlg.GetPathName(); // 경로 받기
#ifdef _DEBUG
		MessageBox(imgDir.GetString(), _T("fileDir"), MB_OK);
#endif
	}
	if (imgDir.IsEmpty()) {
		return;
	}

	if (!m_image.IsNull()) {
		m_image.Destroy();
	}

	HRESULT hr = m_image.Load(imgDir);
	MY_ASSERT(SUCCEEDED(hr));


	Process::GetCircleCenter(&m_image, MAP_COLOR, CIRCLE_COLOR, &m_openCircleCenterX, &m_openCircleCenterY);

	WriteEditControl();
	//draw 'X' on center


	const int nWidth = m_image.GetWidth();
	const int nHeight = m_image.GetHeight();
	const int nPitch = m_image.GetPitch();

	const int drawMinX = max(m_openCircleCenterX - CENTER_X_LENGTH / 2, 0);
	const int drawMinY = max(m_openCircleCenterY - CENTER_X_LENGTH / 2, 0);

	const int drawMaxX = min(m_openCircleCenterX + CENTER_X_LENGTH / 2, nWidth - 1);
	const int drawMaxY = min(m_openCircleCenterY + CENTER_X_LENGTH / 2, nHeight - 1);


	unsigned char* const fm = static_cast<unsigned char*>(m_image.GetBits());

	int x = m_openCircleCenterX;
	int y = m_openCircleCenterY;
	while (x >= drawMinX && y >= drawMinY) {
		fm[y * nPitch + x] = CENTER_X_COLOR;
		--y;
		--x;
	}
	x = m_openCircleCenterX;
	y = m_openCircleCenterY;
	while (x >= drawMinX && y <= drawMaxY) {
		fm[y * nPitch + x] = CENTER_X_COLOR;
		++y;
		--x;
	}
	x = m_openCircleCenterX;
	y = m_openCircleCenterY;
	while (x <= drawMaxX && y <= drawMaxY) {
		fm[y * nPitch + x] = CENTER_X_COLOR;
		++y;
		++x;
	}
	x = m_openCircleCenterX;
	y = m_openCircleCenterY;
	while (x <= drawMaxX && y >= drawMinY) {
		fm[y * nPitch + x] = CENTER_X_COLOR;
		--y;
		++x;
	}

	UpdateDisplay();

}
