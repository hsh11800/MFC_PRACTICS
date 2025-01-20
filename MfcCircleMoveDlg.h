
// MfcCircleMoveDlg.h: 헤더 파일
//

#pragma once

#include "ASSERT.h"

// CMfcCircleMoveDlg 대화 상자
class CMfcCircleMoveDlg : public CDialogEx
{
	// 생성입니다.
public:
	CMfcCircleMoveDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

	// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCCIRCLEMOVE_DIALOG };
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
private:
	CImage m_image;

	int m_startX;
	int m_startY;
	int m_dstX;
	int m_dstY;
	int m_Radius;
	int m_mapWidth;
	int m_mapHeight;
	enum {
		INVALID_VALUE = -INT_MAX,
		MAX_RADIUS = 200,

		MAP_BPP = 8,
		COLOR_NUM = 256,
		MAP_COLOR = 255,
		CIRCLE_COLOR = 140,
		MAP_START_X = 0,
		MAP_START_Y = 100,
		MOVE_COUNT = 100,

		CENTER_X_LENGTH = 8,
		CENTER_X_COLOR = 0,
	};
public:
	afx_msg void OnBnClickedBtnDraw();
	afx_msg void OnBnClickedBtnAction();
	bool isValidCirclePoint() const;
	void ReadEditControl();
	void WriteEditControl();
	void MakeInitImage();
	void UpdateDisplay();
	void DrawCircle(const int nCenterX, const int nCenterY);
	bool IsInCircle(const int x, const int y, const int nCenterX, const int nCenterY, const int nRaduis);
	void ResetCircle(const int nCenterX, const int nCenterY);
	bool SaveImage(const char* path, const int imgCount);
	afx_msg void OnBnClickedBtnLoadImg();
private:
	int m_openCircleCenterX;
	int m_openCircleCenterY;
};



inline void CMfcCircleMoveDlg::ReadEditControl()
{
	UpdateData(true);

}


inline void CMfcCircleMoveDlg::WriteEditControl()
{
	UpdateData(false);
}


inline void CMfcCircleMoveDlg::UpdateDisplay()
{
	CClientDC dc(this);

	MY_ASSERT(!m_image.IsNull());
	m_image.Draw(dc, MAP_START_X, MAP_START_Y);
}
