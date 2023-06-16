
// TicTacToeDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "TicTacToe.h"
#include "TicTacToeDlg.h"
#include "afxdialogex.h"
#include<string>
#include"minmax.h"
#include<random>
using namespace std;
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
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


// CTicTacToeDlg 对话框



CTicTacToeDlg::CTicTacToeDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_TICTACTOE_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTicTacToeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, layerbox);
}

BEGIN_MESSAGE_MAP(CTicTacToeDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CTicTacToeDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CTicTacToeDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CTicTacToeDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CTicTacToeDlg::OnBnClickedButton4)
	ON_STN_CLICKED(chessboard0, &CTicTacToeDlg::OnClickedChessboard0)
	ON_STN_CLICKED(chessboard1, &CTicTacToeDlg::OnClickedChessboard1)
	ON_STN_CLICKED(chessboard2, &CTicTacToeDlg::OnClickedChessboard2)
	ON_STN_CLICKED(chessboard3, &CTicTacToeDlg::OnClickedChessboard3)
	ON_STN_CLICKED(chessboard4, &CTicTacToeDlg::OnClickedChessboard4)
	ON_STN_CLICKED(chessboard5, &CTicTacToeDlg::OnClickedChessboard5)
	ON_STN_CLICKED(chessboard6, &CTicTacToeDlg::OnClickedChessboard6)
	ON_STN_CLICKED(chessboard7, &CTicTacToeDlg::OnClickedChessboard7)
	ON_STN_CLICKED(chessboard8, &CTicTacToeDlg::OnClickedChessboard8)
END_MESSAGE_MAP()


// CTicTacToeDlg 消息处理程序

BOOL CTicTacToeDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	layerbox.SetWindowTextW(_T("5"));
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CTicTacToeDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CTicTacToeDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CTicTacToeDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}




#define computer 1
#define player -1

default_random_engine e(time(0));
int chessboard[9] = { 0 };
int layerlimit = 5;
int allocated = 0;
int f(int play)
{
	int sum = 0;
	for (int i = 0; i < 7; i = i + 3)
	{
		if (chessboard[0+i]+chessboard[1+i]+ chessboard[2+i] == 0-2*play)
			sum = sum - 5;
		if (chessboard[0 + i] + chessboard[1 + i] + chessboard[2 + i] ==  2 * play)
			sum = sum +2;
	}
	for (int i = 0; i < 3; i++)
	{
		if (chessboard[0 + i] + chessboard[3 + i] + chessboard[6 + i] == 0 - 2 * play)
			sum = sum - 5;
		if (chessboard[0 + i] + chessboard[3 + i] + chessboard[6 + i] ==  2 * play)
			sum = sum +2;
	}
	if (chessboard[0 ] + chessboard[4] + chessboard[8] == 0 - 2 * play)
		sum = sum - 5;
	if (chessboard[2] + chessboard[4] + chessboard[6] == 0 - 2 * play)
		sum = sum - 5;
	if (chessboard[0] + chessboard[4] + chessboard[8] == 2 * play)
		sum = sum +2;
	if (chessboard[2] + chessboard[4] + chessboard[6] == 2 * play)
		sum = sum +2;
	for (int i = 0; i < 7; i = i + 3)
	{
		if (chessboard[0 + i] + chessboard[1 + i] + chessboard[2 + i] == 0 - 3 * play)
			sum = sum - 999;
		if (chessboard[0 + i] + chessboard[1 + i] + chessboard[2 + i] == 3 * play)
			sum = sum + 999;
	}
	for (int i = 0; i < 3; i++)
	{
		if (chessboard[0 + i] + chessboard[3 + i] + chessboard[6 + i] == 0 - 3 * play)
			sum = sum - 999;
		if (chessboard[0 + i] + chessboard[3 + i] + chessboard[6 + i] == 3 * play)
			sum = sum + 999;
	}
	if (chessboard[0] + chessboard[4] + chessboard[8] == 0 - 3 * play)
		sum = sum - 999;
	if (chessboard[2] + chessboard[4] + chessboard[6] == 0 - 3 * play)
		sum = sum - 999;
	if (chessboard[0] + chessboard[4] + chessboard[8] == 3 * play)
		sum = sum + 999;
	if (chessboard[2] + chessboard[4] + chessboard[6] == 3 * play)
		sum = sum + 999;
	return sum;
}
int checkwin()
{
	for (int i = 0; i < 7; i = i + 3)
	{
		if ((chessboard[0 + i] + chessboard[1 + i] + chessboard[2 + i]) == 3)
			return 1;
		if ( (chessboard[0 + i] + chessboard[1 + i] + chessboard[2 + i]) == -3)
			return -1;
	}
	for (int i = 0; i < 3; i++)
	{
		if ((chessboard[0 + i] + chessboard[3 + i] + chessboard[6 + i]) == 3 )
			return true; 
		if ((chessboard[0 + i] + chessboard[3 + i] + chessboard[6 + i]) == -3)
			return -1;
	}
	if ((chessboard[0] + chessboard[4] + chessboard[8]) ==3)
		return 1;
	if ((chessboard[2] + chessboard[4] + chessboard[6]) ==3)
		return 1;
	if ( (chessboard[0] + chessboard[4] + chessboard[8]) == -3)
		return -1;
	if ((chessboard[2] + chessboard[4] + chessboard[6]) == -3)
		return -1;
	return 0;
}
int getmax(int play, int layer, int best);
int getmin(int play, int layer,int best=-99999)
{
	if (allocated + layer < 9 && layer < layerlimit)
	{
		int curbest =99999;
		for (int i = 0; i < 9; i++)
		{		
			if (chessboard[i] == 0)
			{
				chessboard[i] = 0 - play;
				int temp;
				if (checkwin() == play)
					temp = 999;
				else if (checkwin() == 0 - play)
					temp = -999;
				else
					temp = getmax(play, layer + 1, curbest);
				if (temp < best)
				{
					chessboard[i] = 0;
					return best;
				}
				if (temp < curbest)
				{
					curbest = temp;
				}
				chessboard[i] = 0;			
			}
		}
		best = curbest;
		return best;
	}
	else
	{
		int curbest = 99999;
		for (int i = 0; i < 9; i++)
		{
			if (chessboard[i] == 0)
			{
				chessboard[i] = 0 - play;
				int temp;
				if (checkwin() == play)
					temp = 999;
				else if (checkwin() == 0 - play)
					temp = -999;
				else
					temp = f(play);
				if (temp < curbest)
				{
					curbest = temp;
				}
				chessboard[i] = 0;
			}
		}
		return curbest;
	}	
}
int getmax(int play, int layer,int best=99999)
{
	if (allocated + layer < 9 && layer < layerlimit)
	{
		int curbest =-99999;
		for (int i = 0; i < 9; i++)
		{	
			
			if (chessboard[i] == 0)
			{
				chessboard[i] = play;
				int temp;
				if (checkwin() == play)
					temp = 999;
				else if (checkwin() == 0 - play)
					temp = -999;
				else
					temp = getmin(play, layer + 1, curbest);
				if (temp > best)
				{
					chessboard[i] = 0;
					return best;
				}
				if (temp > curbest)
				{
					curbest = temp;
				}
				chessboard[i] = 0;
				
			}
		}
		best = curbest;
		return best;
	}
	else
	{
		int curbest = -99999;
		for (int i = 0; i < 9; i++)
		{
			if (chessboard[i] == 0)
			{
				chessboard[i] = 0 - play;
				int temp;
				if (checkwin() == play)
					temp = 999;
				else if (checkwin() == 0 - play)
					temp = -999;
				else
					temp = f(play);
				if (temp > curbest)
				{
					curbest = temp;
				}
				chessboard[i] = 0;
			}
		}
		return curbest;
	}
}
int CTicTacToeDlg::minmaxsearch(int play)
{
	int bestpos = -1;
	if (layerlimit == 1|| allocated ==8)
	{
		int curbest = -99999;
		for (int i = 0; i < 9; i++)
		{
			if (chessboard[i] == 0)
			{
				chessboard[i] = play;
				int temp = f(play);
				if (checkwin() == play)
					temp = 999;
				if (checkwin() == 0-play)
					temp = -999;
				if (temp > curbest)
				{
					bestpos = i;
					curbest = temp;
				}				
				chessboard[i] = 0;
			}
		}
		return bestpos;
	}
	else
	{
		int curbest = -99999;
		for (int i = 0; i < 9; i++)
		{
			if (chessboard[i] == 0)
			{
				chessboard[i] = play;
				int temp = getmin(play, 2,curbest);
				if (temp > curbest)
				{
					bestpos = i;
					curbest = temp;
				}
				chessboard[i] = 0;
			}
		}
		return bestpos;
	}
}
void CTicTacToeDlg::clear()
{
	CPen pen(0, 1, RGB(0, 0,0));
	CBrush brush(RGB(255, 255, 255));
	for (int i = 0; i < 9; i++)
	{
		CWnd* pwnd = GetDlgItem(1005+i);
		CRect rec;
		pwnd->GetWindowRect(rec);
		CDC* pdc = pwnd->GetWindowDC();
		pdc->SelectObject(pen);
		pdc->SelectObject(brush);
		pdc->Rectangle(0, 0, rec.Width(), rec.Height());
		pwnd->EnableWindow(1);
	}
}

void CTicTacToeDlg::lock()
{
	for (int i = 0; i < 9; i++)
	{
		CWnd* pwnd = GetDlgItem(1005 + i);
		pwnd->EnableWindow(0);
	}
}

void CTicTacToeDlg::unlock()
{
	for (int i = 0; i < 9; i++)
	{
		if (chessboard[i] == 0)
		{
			CWnd* pwnd = GetDlgItem(1005 + i);
			pwnd->EnableWindow(1);
		}
	}
	CWnd* pwnd = GetDlgItem(1004);
	pwnd->EnableWindow(1);
}


void CTicTacToeDlg::OnBnClickedButton1()	//先手
{
	// TODO: 在此添加控件通知处理程序代码
	CPen pen(0, 1, RGB(0, 0, 0));
	CBrush brush(RGB(255, 255, 255));
	for (int i = 0; i < 9; i++)
	{
		CWnd* pwnd = GetDlgItem(1005 + i);
		CRect rec;
		pwnd->GetWindowRect(rec);
		CDC* pdc = pwnd->GetWindowDC();
		pdc->SelectObject(pen);
		pdc->SelectObject(brush);
		pdc->Rectangle(0, 0, rec.Width(), rec.Height());
		pwnd->EnableWindow(1);
	}
}


void CTicTacToeDlg::OnBnClickedButton2()	//后手
{
	// TODO: 在此添加控件通知处理程序代码
	CPen pen(0, 1, RGB(0, 0, 0));
	CBrush brush(RGB(255, 255, 255));
	for (int i = 0; i < 9; i++)
	{
		CWnd* pwnd = GetDlgItem(1005 + i);
		CRect rec;
		pwnd->GetWindowRect(rec);
		CDC* pdc = pwnd->GetWindowDC();
		pdc->SelectObject(pen);
		pdc->SelectObject(brush);
		pdc->Rectangle(0, 0, rec.Width(), rec.Height());
		pwnd->EnableWindow(0);
	}
	int next = minmaxsearch(computer);
	chessboard[next] = computer;
	CWnd* pwnd = GetDlgItem(1005+next);
	allocated++;
	pwnd->EnableWindow(0);
	drawx(pwnd);
	for (int i = 0; i < 9; i++)
	{
		if (chessboard[i] == 0) 
		{
			CWnd* pwnd = GetDlgItem(1005 + i);
			CRect rec;
			pwnd->GetWindowRect(rec);
			CDC* pdc = pwnd->GetWindowDC();
			pdc->SelectObject(pen);
			pdc->SelectObject(brush);
			pdc->Rectangle(0, 0, rec.Width(), rec.Height());
			pwnd->EnableWindow(1);
		}
	}
}


void CTicTacToeDlg::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	clear();
	for (int i = 0; i < 9; i++)
	{
		chessboard[i] = 0;
	}
	allocated = 0;
	unlock();
}


void CTicTacToeDlg::OnBnClickedButton4()
{
	// TODO: 在此添加控件通知处理程序代码
	CString s;
	layerbox.GetWindowTextW(s);
	layerlimit = _ttoi(s);
}


void CTicTacToeDlg::OnClickedChessboard0()
{
	// TODO: 在此添加控件通知处理程序代码
	CWnd* pwnd = GetDlgItem(1005);
	pwnd->EnableWindow(0);
	drawcircle(pwnd);
	lock();
	chessboard[0] = player;
	allocated++;
	if (checkwin())
	{
		MessageBox(_T("Game over!"));
		return;
	}
	int next = minmaxsearch(computer);
	chessboard[next] = computer;
	pwnd = GetDlgItem(1005+next);
	pwnd->EnableWindow(0);
	drawx(pwnd);
	allocated++;
	if (checkwin())
	{
		MessageBox(_T("Game over!"));
		return;
	}
	unlock();
}


void CTicTacToeDlg::OnClickedChessboard1()
{
	// TODO: 在此添加控件通知处理程序代码
	CWnd* pwnd = GetDlgItem(1006);
	pwnd->EnableWindow(0);
	drawcircle(pwnd);
	lock();
	chessboard[1] = player;
	allocated++;
	if (checkwin())
	{
		MessageBox(_T("Game over!")); return;
	}
	int next = minmaxsearch(computer);
	chessboard[next] = computer;
	pwnd = GetDlgItem(1005 + next);
	pwnd->EnableWindow(0);
	drawx(pwnd);
	allocated++;
	if (checkwin())
	{
		MessageBox(_T("Game over!")); return;
	}
	unlock();
}


void CTicTacToeDlg::OnClickedChessboard2()
{
	// TODO: 在此添加控件通知处理程序代码
	CWnd* pwnd = GetDlgItem(1007);
	pwnd->EnableWindow(0);
	drawcircle(pwnd);
	lock();
	chessboard[2] = player;
	allocated++;
	if (checkwin())
	{
		MessageBox(_T("Game over!")); return;
	}
	int next = minmaxsearch(computer);
	chessboard[next] = computer;
	pwnd = GetDlgItem(1005 + next);
	pwnd->EnableWindow(0);
	drawx(pwnd);
	allocated++;
	if (checkwin())
	{
		MessageBox(_T("Game over!")); return;
	}
	unlock();
}


void CTicTacToeDlg::OnClickedChessboard3()
{
	// TODO: 在此添加控件通知处理程序代码
	CWnd* pwnd = GetDlgItem(1008);
	pwnd->EnableWindow(0);
	drawcircle(pwnd);
	lock();
	chessboard[3] = player;
	allocated++;
	if (checkwin())
	{
		MessageBox(_T("Game over!")); return;
	}
	int next = minmaxsearch(computer);
	chessboard[next] = computer;
	pwnd = GetDlgItem(1005 + next);
	pwnd->EnableWindow(0);
	drawx(pwnd);
	allocated++;
	if (checkwin())
	{
		MessageBox(_T("Game over!")); return;
	}
	unlock();
}


void CTicTacToeDlg::OnClickedChessboard4()
{
	// TODO: 在此添加控件通知处理程序代码
	CWnd* pwnd = GetDlgItem(1009);
	pwnd->EnableWindow(0);
	drawcircle(pwnd);
	lock();
	chessboard[4] = player;
	allocated++;
	if (checkwin())
	{
		MessageBox(_T("Game over!")); return;
	}
	int next = minmaxsearch(computer);
	chessboard[next] = computer;
	pwnd = GetDlgItem(1005 + next);
	pwnd->EnableWindow(0);
	drawx(pwnd);
	allocated++;
	if (checkwin())
	{
		MessageBox(_T("Game over!")); return;
	}
	unlock();
}


void CTicTacToeDlg::OnClickedChessboard5()
{
	// TODO: 在此添加控件通知处理程序代码
	CWnd* pwnd = GetDlgItem(1010);
	pwnd->EnableWindow(0);
	drawcircle(pwnd);
	lock();
	chessboard[5] = player;
	allocated++;
	if (checkwin())
	{
		MessageBox(_T("Game over!")); return;
	}
	int next = minmaxsearch(computer);
	chessboard[next] = computer;
	pwnd = GetDlgItem(1005 + next);
	pwnd->EnableWindow(0);
	drawx(pwnd);
	allocated++;
	if (checkwin())
	{
		MessageBox(_T("Game over!")); return;
	}
	unlock();
}


void CTicTacToeDlg::OnClickedChessboard6()
{
	// TODO: 在此添加控件通知处理程序代码
	CWnd* pwnd = GetDlgItem(1011);
	pwnd->EnableWindow(0);
	drawcircle(pwnd);
	lock();
	chessboard[6] = player;
	allocated++;
	if (checkwin())
	{
		MessageBox(_T("Game over!")); return;
	}
	int next = minmaxsearch(computer);
	chessboard[next] = computer;
	pwnd = GetDlgItem(1005 + next);
	pwnd->EnableWindow(0);
	drawx(pwnd);
	allocated++;
	if (checkwin())
	{
		MessageBox(_T("Game over!")); return;
	}
	unlock();
}


void CTicTacToeDlg::OnClickedChessboard7()
{
	// TODO: 在此添加控件通知处理程序代码
	CWnd* pwnd = GetDlgItem(1012);
	pwnd->EnableWindow(0);
	drawcircle(pwnd);
	lock();
	chessboard[7] = player;
	allocated++;
	if (checkwin())
	{
		MessageBox(_T("Game over!")); return;
	}
	int next = minmaxsearch(computer);
	chessboard[next] = computer;
	pwnd = GetDlgItem(1005 + next);
	pwnd->EnableWindow(0);
	drawx(pwnd);
	allocated++;
	if (checkwin())
	{
		MessageBox(_T("Game over!")); return;
	}
	unlock();
}


void CTicTacToeDlg::OnClickedChessboard8()
{
	// TODO: 在此添加控件通知处理程序代码
	CWnd* pwnd = GetDlgItem(1013);
	pwnd->EnableWindow(0);
	drawcircle(pwnd);
	lock();
	chessboard[8] = player;
	allocated++;
	if (checkwin())
	{
		MessageBox(_T("Game over!")); return;
	}
	int next = minmaxsearch(computer);
	chessboard[next] = computer;
	pwnd = GetDlgItem(1005 + next);
	pwnd->EnableWindow(0);
	drawx(pwnd);
	allocated++;
	if (checkwin())
	{
		MessageBox(_T("Game over!")); return;
	}
	unlock();
}

void CTicTacToeDlg::drawcircle(CWnd* pwnd) 
{
	CPen pen(0, 5, RGB(0, 0, 0));
	CBrush brush(RGB(255, 255, 255));
	CRect rec;
	pwnd->GetWindowRect(rec);
	CDC* pdc = pwnd->GetWindowDC();
	pdc->SelectObject(pen);
	pdc->SelectObject(brush);
	pdc->Ellipse(0, 0, rec.Width(), rec.Height());
}

void CTicTacToeDlg::drawx(CWnd* pwnd)
{
	CPen pen(0, 5, RGB(0, 0, 0));
	CBrush brush(RGB(255, 255, 255));
	CRect rec;
	pwnd->GetWindowRect(rec);
	CDC* pdc = pwnd->GetWindowDC();
	pdc->SelectObject(pen);
	pdc->SelectObject(brush);
	pdc->MoveTo(0, 0);
	pdc->LineTo(rec.Width(), rec.Height());
	pdc->MoveTo(rec.Width(), 0);
	pdc->LineTo(0, rec.Height());
}
