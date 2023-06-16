
// TicTacToeDlg.h: 头文件
//

#pragma once


// CTicTacToeDlg 对话框
class CTicTacToeDlg : public CDialogEx
{
// 构造
public:
	CTicTacToeDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TICTACTOE_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CEdit layerbox;
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
	int minmaxsearch(int play);
	void clear();
	void lock();
	void unlock();
	void drawcircle(CWnd* pwnd);
	void drawx(CWnd* pwnd);
	afx_msg void OnClickedChessboard0();
	afx_msg void OnClickedChessboard1();
	afx_msg void OnClickedChessboard2();
	afx_msg void OnClickedChessboard3();
	afx_msg void OnClickedChessboard4();
	afx_msg void OnClickedChessboard5();
	afx_msg void OnClickedChessboard6();
	afx_msg void OnClickedChessboard7();
	afx_msg void OnClickedChessboard8();
};
