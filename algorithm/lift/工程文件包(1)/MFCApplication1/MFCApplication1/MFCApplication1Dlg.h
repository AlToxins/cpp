
// MFCApplication1Dlg.h: 头文件
//

#pragma once
#include<vector>
#define MAX 999999

struct __POINT
{
	int  x;
	int  y;
	__POINT(int a=0, int b=0) :x(a), y(b)
	{

	}
	__POINT(POINT a)
	{
		x = a.x;
		y = a.y;
	}
	friend bool operator==(__POINT x, __POINT y)
	{
		if (x.x != y.x)
			return false;
		if (x.y != y.y)
			return false;
		return true;
	}
	POINT topoint()
	{
		POINT temp;
		temp.x = x;
		temp.y = y;
		return temp;
	}
};

struct node
{
	int id;
	__POINT n;
	node(int id1, __POINT n1)
	{
		id = id1;
		n = n1;
	}
	node()
	{

	}
};
struct edge
{
	int id1;
	int id2;
	__POINT n1;
	__POINT n2;
	double dis;
	edge(edge &m)
	{
		id1 = m.id1;
		id2 = m.id2;
		n1 = m.n1;
		n2 = m.n2;
		dis = m.dis;
	}
	edge(node nn, node mm)
	{
		n1 = nn.n;
		n2 = mm.n;
		id1 = nn.id;
		id2 = mm.id;
		dis = sqrt((n1.x - n2.x) * (n1.x - n2.x) + (n1.y - n2.y) * (n1.y - n2.y));
	}
};





// CMFCApplication1Dlg 对话框
class CMFCApplication1Dlg : public CDialogEx
{
// 构造
public:
	CMFCApplication1Dlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCAPPLICATION1_DIALOG };
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
	CMenu mymenu;
	std::vector<edge> edgelist;
	std::vector<node> allnode;
	std::vector<edge> startedgelist;
	std::vector<edge> endedgelist;
	std::vector<edge> alledge;
	std::vector<std::vector<node>> nodelist;
	node start;
	node end;
public:
	afx_msg void On32771();
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	double mult(__POINT p0, __POINT p1, __POINT p2) 
	{
		return (p0.x - p1.x) * (p0.y - p2.y) - (p0.y - p1.y) * (p0.x - p2.x);
	}
	bool Judge(__POINT aa, __POINT bb, __POINT cc, __POINT dd)
	{
		if (max(aa.x, bb.x) < min(cc.x, dd.x)) return false;
		if (max(aa.y, bb.y) < min(cc.y, dd.y)) return false;
		if (max(cc.x, dd.x) < min(aa.x, bb.x)) return false;
		if (max(cc.y, dd.y) < min(aa.y, bb.y)) return false;
		if (mult(aa, cc, bb) * mult(aa, bb, dd) < 0) return false; 
		if (mult(cc, aa, dd) * mult(cc, dd, bb) < 0) return false;
		return true;
	}

	afx_msg void On32772();
	afx_msg void On32773();
	afx_msg void On32774();
	afx_msg void On32775();
	afx_msg void On32776();
};
