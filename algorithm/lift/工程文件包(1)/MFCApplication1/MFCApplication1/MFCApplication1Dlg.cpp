
// MFCApplication1Dlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "MFCApplication1.h"
#include "MFCApplication1Dlg.h"
#include "afxdialogex.h"
#include<vector>
#include<queue>
#include<iostream>
using namespace std;
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框










struct Node
{
    Node* pre = nullptr;
    Node* next = nullptr;
    __POINT value = __POINT(0);
    Node(__POINT a)
    {
        value = a;
    };
};
class Dlist
{
public:
    Node* Head = nullptr;
    Node* Tail = nullptr;
    int count_num = 0;
    void insert(Node* nd)
    {
        nd->pre = Tail;
        Tail->next = nd;
        Tail = nd;
        nd->next = Head;
        Head->pre = Tail;
        count_num++;
    };
    void insert(__POINT newnode)
    {
        Node* nd = new Node(newnode);
        nd->pre = Tail;
        Tail->next = nd;
        Tail = nd;
        nd->next = Head;
        Head->pre = Tail;
        count_num++;
    }
    Node* inlist(__POINT test) {
        if (Head->value == test) {
            return Head;
        }
        Node* temp = Head->next;
        for (temp; (temp) && (temp != Head); temp = temp->next) {
            if (temp!=nullptr&&test == temp->value) {
                return temp;
            }
        }
        return nullptr;
    }
};
class straight_line
{
public:
    double A;
    double B;
    double C;
    straight_line(int a = 0, int b = 0, int c = 0)
    {
        A = a;
        B = b;
        C = c;
    };
    straight_line(__POINT a, __POINT b)
    {
        A = (a.y - b.y);
        B = (b.x - a.x);
        C = (a.x * b.y) - (b.x * a.y);
    };
    straight_line get_parallel(__POINT target)
    {

        int NewC = -((A * (target.x)) + (B * (target.y)));
        return straight_line(A, B, NewC);
    };
    __POINT cross(straight_line another)
    {
        int x = (C * another.B - another.C * B) / (another.A * B - A * another.B);
        int y = (another.C * A - C * another.A) / (another.A * B - A * another.B);
        return __POINT(x, y);
    }
    int get_dis(__POINT target)
    {
        return (target.x * A + target.y * B + C);
    }
};
class point_set
{
public:
    vector<__POINT> set;
    int size()
    {
        return set.size();
    };
    void push(__POINT d)
    {
        set.push_back(d);
    };
    void clone(vector<__POINT> input) {
        for (int i = 0; i < input.size(); i++) {
            push(input[i]);
        };
    }
    __POINT getUconer()
    {
        int max = 0;
        for (int i = 1; i < set.size(); i++)
        {
            if (set[max].y < set[i].y)
            {
                max = i;
            };
        }
        return set[max];
    }
    __POINT getDconer()
    {
        int min = 0;
        for (int i = 1; i < set.size(); i++)
        {
            if (set[min].y > set[i].y)
            {
                min = i;
            };
        }
        return set[min];
    }
    __POINT getRconer()
    {
        int max = 0;
        for (int i = 1; i < set.size(); i++)
        {
            if (set[max].x < set[i].x)
            {
                max = i;
            };
        }
        return set[max];
    }
    __POINT getLconer()
    {
        int min = 0;
        for (int i = 1; i < set.size(); i++)
        {
            if (set[min].x > set[i].x)
            {
                min = i;
            };
        }
        return set[min];
    }
};
vector<point_set> clone2set(vector<vector<__POINT>> input) {
    vector<point_set> result;
    for (int i = 0; i < input.size(); i++) {
        point_set temp;
        temp.clone(input[i]);
        result.push_back(temp);
    };
    return result;
};
struct PCB
{
    Node* bounding_node;
    point_set base_point;
    int flag = 0;
    int generation = 0;
    PCB(Node* a, point_set b, int f = 0, int g = 0)
    {
        bounding_node = a;
        base_point = b;
        flag = f;
        generation = g;
    };
};
struct CCB
{
    PCB* control_info = nullptr;
    point_set data;
    CCB(PCB* a, point_set b)
    {
        control_info = a;
        data = b;
    };
};
queue<CCB*> bounding_initial(point_set dataset, Dlist* backlist, int G)
{
    cout << "INITIALIZING:" << endl;
    cout << "Print basic point:" << endl;
    __POINT up, down, left, right;
    up = dataset.getUconer();
    down = dataset.getDconer();
    left = dataset.getLconer();
    right = dataset.getRconer();
    cout << "up: " << up.x << " " << up.y << endl;
    cout << "down: " << down.x << " " << down.y << endl;
    cout << "left: " << left.x << " " << left.y << endl;
    cout << "right: " << right.x << " " << right.y << endl;
    point_set ba, bb, bc, bd;
    ba.push(up);
    ba.push(left);
    bb.push(left);
    bb.push(down);
    bc.push(down);
    bc.push(right);
    bd.push(right);
    bd.push(up);
    __POINT bounda(left.x, up.y);
    __POINT boundb(left.x, down.y);
    __POINT boundc(right.x, down.y);
    __POINT boundd(right.x, up.y);
    Node* bbb = new Node(boundb);
    Node* bbc = new Node(boundc);
    Node* bbd = new Node(boundd);
    backlist->Head = new Node(bounda);
    backlist->Tail = backlist->Head;
    backlist->count_num++;
    backlist->insert(bbb);
    backlist->insert(bbc);
    backlist->insert(bbd);
    PCB* pa = new PCB(backlist->Head, ba, 1, G);
    PCB* pb = new PCB(bbb, bb, -1, G);
    PCB* pc = new PCB(bbc, bc, -1, G);
    PCB* pd = new PCB(bbd, bd, 1, G);
    point_set a, b, c, d;
    queue<CCB*> result;
    __POINT temp;
    cout << "dataset's size is :" << dataset.size() << endl;
    b.push(left);
    c.push(down);
    for (int i = 0; i < dataset.size(); i++)
    {
        temp = dataset.set[i];
        cout << "Dividing a point: " << temp.x << " " << temp.y << endl;
        if (temp.y >= left.y)
        {
            if (temp.x <= up.x)
            {
                a.push(temp);
                cout << "a" << endl;
                continue;
            }
        }
        else
        {
            if (temp.x <= down.x)
            {
                b.push(temp);
                cout << "b" << endl;
                continue;
            }

        }
        if (temp.y >= right.y)
        {
            if (temp.x >= up.x)
            {
                d.push(temp);
                cout << "d" << endl;
                continue;
            }

        }
        else
        {
            if (temp.x >= down.x)
            {
                c.push(temp);
                cout << "c" << endl;
                continue;
            }

        }
    }
    c.push(right);
    d.push(up);
    CCB* ca = new CCB(pa, a);
    CCB* cb = new CCB(pb, b);
    CCB* cc = new CCB(pc, c);
    CCB* cd = new CCB(pd, d);
    cout << "Printing initialize result:" << endl;
    cout << "Data info:" << endl;

    cout << "Print a:" << endl;
    cout << "1:" << a.size() << endl;
    for (int i = 0; i < a.size(); i++) {
        cout << a.set[i].x << "," << a.set[i].y << endl;
    }

    cout << "Print b:" << endl;
    cout << "2:" << b.size() << endl;
    for (int i = 0; i < b.size(); i++) {
        cout << b.set[i].x << "," << b.set[i].y << endl;
    }

    cout << "Print c:" << endl;
    cout << "3:" << c.size() << endl;
    for (int i = 0; i < c.size(); i++) {
        cout << c.set[i].x << "," << c.set[i].y << endl;
    }

    cout << "Print d:" << endl;
    cout << "4:" << d.size() << endl;
    for (int i = 0; i < d.size(); i++) {
        cout << d.set[i].x << "," << d.set[i].y << endl;
    }
    result.push(ca);
    result.push(cb);
    result.push(cc);
    result.push(cd);
    return result;
}
pair<CCB*, CCB*> max_point_to_outside(Dlist* var, CCB* target_work)
{
    PCB* control_info = target_work->control_info;
    point_set data = target_work->data;
    cout << endl;
    cout << "now working with a CCB:" << endl;
    if (!control_info)
    {
        cout << "This CCB lost PCB,now change to end" << endl;
        return pair<CCB*, CCB*>(nullptr, nullptr);
    }
    cout << "G is: " << control_info->generation << endl;
    cout << "Flag is: " << control_info->flag << endl;
    if (control_info->generation <= 0)
    {
        cout << "This CCB generation has ron out,now change to end" << endl;
        return pair<CCB*, CCB*>(nullptr, nullptr);
    }
    if (data.set.empty()) {
        cout << "This CCB has no data,now change to end" << endl;
        return pair<CCB*, CCB*>(nullptr, nullptr);
    };
    cout << "Print Point_set:" << endl;
    for (int i = 0; i < data.size(); i++) {
        cout << "<" << data.set[i].x << "," << data.set[i].y << ">";
    }
    cout << endl;
    int max = 0;
    cout << "Print Base Point:" << endl;
    __POINT basea = control_info->base_point.set[0];
    __POINT baseb = control_info->base_point.set[1];
    cout << "<" << basea.x << "," << basea.y << ">";
    cout << "<" << baseb.x << "," << baseb.y << ">";
    cout << endl;
    if (basea == baseb) {
        cout << "Base Points went wrong" << endl;
        return pair<CCB*, CCB*>(nullptr, nullptr);
    }
    straight_line temp_line(basea, baseb);
    int targetf = 0;
    int maxf = 0;
    int f = control_info->flag;
    int g_mother = control_info->generation;
    for (int i = 0; i < data.size(); i++)
    {
        if (temp_line.B > 0)
        {
            targetf = (f) * (temp_line.get_dis(data.set[i]));
            cout << i << " " << targetf << " " << data.set[i].x << "," << data.set[i].y << endl;
            if (targetf >= maxf)
            {
                maxf = targetf;
                max = i;
            };
        }
        else
        {

            targetf = (-1) * (f) * (temp_line.get_dis(data.set[i]));
            cout << i << " " << targetf << " " << data.set[i].x << "," << data.set[i].y << endl;
            if (targetf >= maxf)
            {
                maxf = targetf;
                max = i;
            };
        }
    };

    point_set pa, pb, ba, bb;
    int bf1 = 0;
    int bf2 = 0;
    __POINT m = data.set[max];
    ba.push(basea);
    ba.push(m);
    bb.push(m);
    bb.push(baseb);
    __POINT temp;
    Node* bound = control_info->bounding_node;
    cout << "bounding node is:" << bound->value.x << " " << bound->value.y << endl;
    cout << "max is:" << max << " " << m.x << "," << m.y << endl;
    pa.push(basea);
    pa.push(baseb);
    pb.push(basea);
    pb.push(baseb);
    pa.push(m);
    for (int i = 0; i < data.size(); i++)
    {
        temp = data.set[i];
        if ((temp == basea) || (temp == baseb)) {
            continue;
        }
        if (temp.y > m.y)
        {
            pa.push(temp);
        }
        else
        {
            pb.push(temp);
        };
    };
    straight_line boundline1(bound->value, bound->pre->value);
    straight_line boundline2(bound->value, bound->next->value);
    straight_line newline = temp_line.get_parallel(m);
    cout << "Line info:" << endl;
    cout << "bound_pre" << "<" << bound->pre->value.x << "," << bound->pre->value.y << ">" << endl;
    cout << "bound" << "<" << bound->value.x << "," << bound->value.y << ">" << endl;
    cout << "bound_next" << "<" << bound->next->value.x << "," << bound->next->value.y << ">" << endl;
    if (bound == var->Tail)
    {
        bf2 = 1;
    };
    CCB* R1 = nullptr;
    CCB* R2 = nullptr;
    if (newline.A * boundline1.B != newline.B * boundline1.A) {
        cout << "New Bounding Point1: ";
        __POINT newb1 = newline.cross(boundline1);
        cout << "<" << newb1.x << "," << newb1.y << ">" << endl;
        Node* n1 = nullptr;
        Node* test = var->inlist(newb1);
        if (!test) {
            n1 = new Node(newb1);
            if (bound == var->Head)
            {
                var->Head = n1;
            };
            n1->next = bound->next;
            n1->pre = bound->pre;
            bound->pre->next = n1;
            bound->next->pre = n1;
            delete bound;
            bound = n1;
            bf1 = 1;
            PCB* r1 = new PCB(n1, ba, f, g_mother - 1);
            R1 = new CCB(r1, pa);
        }
        else {
            cout << "New Bounding Point already in Dlist,continue" << endl;
            R1 = nullptr;
        }
    }
    if (newline.A * boundline2.B != newline.B * boundline2.A) {
        cout << "New Bounding Point2: ";
        __POINT newb2 = newline.cross(boundline2);
        cout << "<" << newb2.x << "," << newb2.y << ">" << endl;
        Node* n2 = nullptr;
        Node* test = var->inlist(newb2);
        if (bf1 == 1) {
            if (!test)
            {
                n2 = new Node(newb2);
                n2->pre = bound;
                n2->next = bound->next;
                bound->next->pre = n2;
                bound->next = n2;
                
            }
            else {
                cout << "New Bounding Point already in Dlist,continue" << endl;
                bf1 = 1;
            }
        }
        else {
            if (!test) {
                n2 = new Node(newb2);
                n2->pre = bound->pre;
                n2->next = bound->next;
                bound->next->pre = n2;
                bound->pre->next = n2;
                delete bound;
                if (bound == var->Head)
                {
                    var->Head = n2;
                };

            }
            else {
                cout << "New Bounding Point already in Dlist,continue" << endl;
                bf1 = 1;
            }
        }

        if (bf1 == 1) {
            R2 = nullptr;
        }
        else {
            PCB* r2 = new PCB(n2, bb, f, g_mother - 1);
            R2 = new CCB(r2, pb);
        }
    }
    return pair<CCB*, CCB*>(R1, R2);
};
Dlist* bound(point_set original_set, int generation)
{
    int gener_counter = generation;
    Dlist* result = new Dlist;

    queue<CCB*> mia = bounding_initial(original_set, result, generation);
    cout << "End Initialize" << endl;
    cout << endl;
    while (!mia.empty())
    {
        cout << endl;
        cout << "Now " << mia.size() << " CCB left." << endl;
        CCB* temp = mia.front();
        mia.pop();
        pair<CCB*, CCB*> temp_q = max_point_to_outside(result, temp);
        //delete temp;
        if (temp_q.first)
        {
            mia.push(temp_q.first);

        }
        if (temp_q.second)
        {
            mia.push(temp_q.second);
        }
    };
    return result;
};

void round(vector<vector<__POINT>> input, vector<vector<__POINT>>& output)
{
    output.clear();
    vector<point_set> processor = clone2set(input);
    for (int i = 0; i < processor.size(); i++) {
        if (i == 8)
            continue;
        Dlist* backlist = bound(processor[i], 1);
        vector<__POINT> tempv;
        tempv.push_back(backlist->Head->value);
        for (Node* temp = backlist->Head->next; temp != backlist->Head; temp = temp->next) {
            if (temp) {
                tempv.push_back(temp->value);
            };
        };
        delete backlist;
        output.push_back(tempv);
    };
}











































































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


// CMFCApplication1Dlg 对话框



CMFCApplication1Dlg::CMFCApplication1Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCAPPLICATION1_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCApplication1Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMFCApplication1Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//ON_BN_CLICKED(IDC_BUTTON1, &CMFCApplication1Dlg::OnBnClickedButton1)
	ON_COMMAND(ID_32771, &CMFCApplication1Dlg::On32771)
	ON_WM_LBUTTONDBLCLK()
	ON_WM_LBUTTONDOWN()
	ON_COMMAND(ID_32772, &CMFCApplication1Dlg::On32772)
	ON_COMMAND(ID_32773, &CMFCApplication1Dlg::On32773)
	ON_COMMAND(ID_32774, &CMFCApplication1Dlg::On32774)
	ON_COMMAND(ID_32775, &CMFCApplication1Dlg::On32775)
	ON_COMMAND(ID_32776, &CMFCApplication1Dlg::On32776)
END_MESSAGE_MAP()


// CMFCApplication1Dlg 消息处理程序

BOOL CMFCApplication1Dlg::OnInitDialog()
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

	mymenu.LoadMenuW(IDR_MENU1);
	this->SetMenu(&mymenu);
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CMFCApplication1Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CMFCApplication1Dlg::OnPaint()
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
HCURSOR CMFCApplication1Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


COLORREF mycolor(RGB(0,0,0));
std::vector<node> pointlist;




int flag = 0;
int ccount = 0;
void CMFCApplication1Dlg::On32771()
{
	// TODO: 在此添加命令处理程序代码
	CColorDialog dlg;
	if (dlg.DoModal() == IDOK)
		mycolor = dlg.GetColor();
}


void CMFCApplication1Dlg::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CClientDC dc(this);
	CPen pen;
	nodelist.push_back(pointlist);
	pen.CreatePen(0, 1, mycolor);
	dc.SelectObject(pen);
	dc.MoveTo(pointlist[0].n.topoint());
	dc.LineTo(pointlist[pointlist.size() - 1].n.topoint());
	edgelist.push_back(edge(pointlist[0], pointlist[pointlist.size() - 1]));
	for (int i = 0; i < pointlist.size() - 1; i++)
	{
		dc.MoveTo(pointlist[i].n.topoint());
		dc.LineTo(pointlist[i + 1].n.topoint());
		edgelist.push_back(edge(pointlist[i], pointlist[i + 1]));
	}
	pointlist.clear();
	CDialogEx::OnLButtonDblClk(nFlags, point);
}


void CMFCApplication1Dlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (flag == 0)
	{
		node temp(ccount++, point);
		pointlist.push_back(temp);
		allnode.push_back(temp);
	}
	else if (flag == 1)
	{
		start.id = 998;
		start.n = point;
		
	}
	else if (flag == 2)
	{
		end.id = 999;
		end.n = point;		
		
	}
	flag = 0;
	CDialogEx::OnLButtonDown(nFlags, point);
}


void CMFCApplication1Dlg::On32772()
{
	// TODO: 在此添加命令处理程序代码
	flag = 1;
}


void CMFCApplication1Dlg::On32773()
{
	// TODO: 在此添加命令处理程序代码
	flag = 2;
}


void CMFCApplication1Dlg::On32774()
{
	// TODO: 在此添加命令处理程序代码
	bool direct = false;
	for (int i = 0; i < edgelist.size(); i++)
	{
		if (Judge(start.n, end.n, edgelist[i].n1, edgelist[i].n2))
			direct = true;
	}	
	if (!direct)
	{
		CClientDC dc(this);
		CPen pennn(0, 2, RGB(0, 255, 0));
		dc.SelectObject(pennn);
		dc.MoveTo(start.n.topoint());
		dc.LineTo(end.n.topoint());
		return;
	}
	endedgelist.clear();
	for (int j = 0; j < allnode.size(); j++)
	{
		bool flagg = false;
		for (int i = 0; i < edgelist.size(); i++)
		{
			if (Judge(end.n, allnode[j].n, edgelist[i].n1, edgelist[i].n2) && !(allnode[j].n == edgelist[i].n1) && !(allnode[j].n == edgelist[i].n2))
			{
				flagg = true;
			}
		}
		if (flagg == false)
		{
			endedgelist.push_back(edge(end, allnode[j]));
		}
	}
	alledge.clear();
	for (int i = 0; i < nodelist.size(); i++)
	{
		for (int j = 0; j < nodelist.size(); j++)
		{
			if (i == j)continue;
			for (int k = 0; k < nodelist[i].size(); k++)
			{
				for (int s = 0; s < nodelist[j].size(); s++)
				{
					bool flagg = false;
					for (int aa = 0; aa < edgelist.size(); aa++)
					{
						if (Judge(nodelist[i][k].n, nodelist[j][s].n, edgelist[aa].n1, edgelist[aa].n2)&&!(nodelist[i][k].n== edgelist[aa].n1) && !(nodelist[i][k].n == edgelist[aa].n2) && !(nodelist[j][s].n == edgelist[aa].n1) && !(nodelist[j][s].n == edgelist[aa].n2))
							flagg = true;
					}
					if (flagg == false)
					{
						alledge.push_back(edge(nodelist[i][k], nodelist[j][s]));
					}
				}
			}
		}
	}
	startedgelist.clear();
	for (int j = 0; j < allnode.size(); j++)
	{
		bool flagg = false;
		for (int i = 0; i < edgelist.size(); i++)
		{
			if (Judge(start.n, allnode[j].n, edgelist[i].n1, edgelist[i].n2) && !(allnode[j].n == edgelist[i].n1) && !(allnode[j].n == edgelist[i].n2))
			{
				flagg = true;
			}
		}
		if (flagg == false)
		{
			startedgelist.push_back(edge(start, allnode[j]));
		}
	}
	double** arr = new double* [allnode.size() + 1];
	int* visit = new int [allnode.size() + 1];
	int* src = new int[allnode.size() + 1];
	double*dis1= new double[allnode.size() + 1];
	double* dis2 = new double[allnode.size() + 1];
	for (int i = 0; i < allnode.size() + 2; i++)
	{
		arr[i]= new double [allnode.size() + 1];
		src[i] = allnode.size();
		dis1[i] = MAX;
		dis2[i] = MAX;
		visit[i] = 0;
	}
	for (int i = 0; i < allnode.size() + 2; i++)
	{		
		for (int j = 0; j < allnode.size() + 2; j++)
		{
			arr[i][j] = MAX;
		}
		arr[i][i] = 0;
	}
	for (int i = 0; i < edgelist.size(); i++)
	{
		arr[edgelist[i].id1][edgelist[i].id2] = edgelist[i].dis;
		arr[edgelist[i].id2][edgelist[i].id1] = edgelist[i].dis;
	}
	for (int i = 0; i < alledge.size(); i++)
	{
		arr[alledge[i].id1][alledge[i].id2] = alledge[i].dis;
		arr[alledge[i].id2][alledge[i].id1] = alledge[i].dis;
	}
	for (int i = 0; i < startedgelist.size(); i++)
	{
		arr[allnode.size()][startedgelist[i].id2] = startedgelist[i].dis;
		arr[startedgelist[i].id2][allnode.size()] = startedgelist[i].dis;
	}
	for (int i = 0; i < endedgelist.size(); i++)
	{
		arr[allnode.size()+1][endedgelist[i].id2] = endedgelist[i].dis;
		arr[endedgelist[i].id2][allnode.size()+1] = endedgelist[i].dis;
	}
	int cur = allnode.size();
	visit[cur] = 1;
	dis1[cur] = 0;
	//dis2[cur] = 0;
	while (visit[allnode.size() + 1] != 1)
	{
		for (int i = 0; i < allnode.size() + 2; i++)
		{
			if (visit[i]==0&&abs(arr[cur][i]-MAX)>0.001 && dis1[i] > dis1[cur] + arr[cur][i])
			{
				dis1[i] = dis1[cur] + arr[cur][i];
				src[i] = cur;
			}
		}
		double min = 99999;
		int next = -1;
		for (int i = 0; i < allnode.size() + 2; i++)
		{
			if (visit[i]==0&&dis1[i]<min)
			{
				min = dis1[i];
				next = i;
			}
		}
		cur = next;
		visit[cur] = 1;
	}
	CClientDC dc(this);
	CPen pennn(0, 2, RGB(0, 255, 0));
	dc.SelectObject(pennn);
	dc.MoveTo(end.n.topoint());
	dc.LineTo(allnode[src[allnode.size() + 1]].n.topoint());
	cur = src[allnode.size() + 1];
	while (1)
	{
		if (src[cur] == allnode.size())
		{
			dc.MoveTo(start.n.topoint());
			dc.LineTo(allnode[cur].n.topoint());
			break;
		}
		dc.MoveTo(allnode[cur].n.topoint());
		dc.LineTo(allnode[src[cur]].n.topoint());
		
		cur = src[cur];
	}
	/*
	for (int i = 0; i < allnode.size() + 2; i++)
	{
		delete[] arr[i];
	}
	delete[] arr;
	
	delete[]visit;
	*/
}


void CMFCApplication1Dlg::On32775()
{
	// TODO: 在此添加命令处理程序代码
	CDC* pdc = this->GetDC();
	CRect rec;
	this->GetWindowRect(rec);
	CBrush br(RGB(255, 255, 255));
	CPen pennn(0,1,RGB(255, 255, 255));
	pdc->SelectObject(br);
	pdc->SelectObject(pennn);
	pdc->Rectangle(0,0,rec.Width(),rec.Height());
	ReleaseDC(pdc);
	CClientDC dc(this);
	for (int i = 0; i < edgelist.size(); i++)
	{
		dc.MoveTo(edgelist[i].n1.topoint());
		dc.LineTo(edgelist[i].n2.topoint());
	}
}


void CMFCApplication1Dlg::On32776()
{
	// TODO: 在此添加命令处理程序代码
	CString path;
	CFileDialog fdlg(TRUE);
	if (fdlg.DoModal() == IDOK)
	{
		path = fdlg.GetPathName();
	}
	vector<vector<__POINT>> pointset;
	vector<vector<int>> visit;
	vector<int>temp;
	CImage p1;
	p1.Load(path);
	for (int i = 0; i < p1.GetHeight(); i++)
	{
		temp.push_back(0);
	}
	for (int i = 0; i < p1.GetWidth(); i++)
	{
		visit.push_back(temp);
	}
	for (int i = 0; i < p1.GetWidth(); i++)
	{
		for (int j = 0; j < p1.GetHeight(); j++)
		{

			if (visit[i][j])
				continue;
			if (p1.GetPixel(i, j) == RGB(255, 255, 255))
			{
				visit[i][j] = 1;
				continue;
			}
			vector<__POINT> curset;
			queue<__POINT> list;
			list.push(__POINT(i, j));
			while (!list.empty())
			{
				auto arrange = RGB(10, 10,15);
				int addflag = 0;
				__POINT cur = list.front();
				list.pop();
				if (visit[cur.x][cur.y])
					continue;
				visit[cur.x][cur.y] = 1;
				if (p1.GetPixel(cur.x + 1, cur.y ) != CLR_INVALID && p1.GetPixel(cur.x + 1, cur.y ) - RGB(0, 0, 0) < arrange)
				{
					list.push(__POINT(cur.x + 1, cur.y));
				}
				else if (addflag == 0)
				{
					curset.push_back(cur);
					addflag = 1;
				}
				if (cur.x>=1&&p1.GetPixel(cur.x - 1, cur.y ) != CLR_INVALID && p1.GetPixel(cur.x - 1, cur.y ) - RGB(0, 0, 0) < arrange)
				{
					list.push(__POINT(cur.x - 1, cur.y));
				}
				else if (addflag == 0)
				{
					curset.push_back(cur);
					addflag = 1;
				}
				if (p1.GetPixel(cur.x , cur.y + 1) != CLR_INVALID && p1.GetPixel(cur.x , cur.y + 1) - RGB(0, 0, 0) < arrange)
				{
					list.push(__POINT(cur.x , cur.y + 1));
				}
				else if (addflag == 0)
				{
					curset.push_back(cur);
					addflag = 1;
				}
				if (cur.y>=1&&p1.GetPixel(cur.x , cur.y - 1) != CLR_INVALID && p1.GetPixel(cur.x , cur.y - 1) - RGB(0, 0, 0) < arrange)
				{
					list.push(__POINT(cur.x , cur.y - 1));
				}
				else if (addflag == 0)
				{
					curset.push_back(cur);
					addflag = 1;
				}
			}
			if (curset.size() > 50)
				pointset.push_back(curset);
		}
	}
	CClientDC dc(this);
	for (int i = 0; i < pointset.size(); i++)
	{
		for (int j = 0; j < pointset[i].size(); j++)
		{
			dc.SetPixel(pointset[i][j].x, pointset[i][j].y, RGB(255, 0, 0));
		}
	}

    CBrush bru(RGB(0, 0, 255));
    dc.SelectObject(bru);
	vector<vector<__POINT>> pictureset;
    vector<vector<__POINT>> pictureset1;
    for (int i = 0; i < pointset.size(); i+=2)
    {
        pictureset1.push_back(pointset[i]);
    }
    round(pointset, pictureset);

	pointlist.clear();
	for (int i = 0; i < pictureset.size(); i++)
	{
		for (int j = 0; j < pictureset[i].size(); j++)
		{
			node temp(ccount++, pictureset[i][j]);
			pointlist.push_back(temp);
			allnode.push_back(temp);
		}
		CPen pen;
		nodelist.push_back(pointlist);
		pen.CreatePen(0, 1, mycolor);
		dc.SelectObject(pen);
		dc.MoveTo(pointlist[0].n.topoint());
		dc.LineTo(pointlist[pointlist.size() - 1].n.topoint());
		edgelist.push_back(edge(pointlist[0], pointlist[pointlist.size() - 1]));
		for (int i = 0; i < pointlist.size() - 1; i++)
		{
			dc.MoveTo(pointlist[i].n.topoint());
			dc.LineTo(pointlist[i + 1].n.topoint());
			edgelist.push_back(edge(pointlist[i], pointlist[i + 1]));
		}
		pointlist.clear();
	}
}
