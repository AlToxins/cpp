#include <iostream>
#include <vector>
#include <queue>
using namespace std;

struct __POINT
{
    int x;
    int y;
    __POINT(int a = 0, int b = 0)
    {
        x = a;
        y = b;
    };
    friend bool operator==(__POINT A, __POINT B) {
        if (A.x != B.x) {
            return false;
        }
        else {
            if (A.y != B.y) {
                return false;
            }
        };
        return true;
    }
};
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
    double get_dis(__POINT target)
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
    cout << "up: "<<up.x << " " << up.y << endl;
    cout << "down: "<<down.x << " " << down.y << endl;
    cout << "left: "<<left.x << " " << left.y << endl;
    cout << "right: "<<right.x << " " << right.y << endl;
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
    cout << "Data info:"<<endl;
    
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
pair<CCB*, CCB*> max_point_to_outside(Dlist* var,CCB* target_work)
{
    PCB* control_info = target_work->control_info;
    point_set data= target_work->data;
    cout << endl;
    cout << "now working with a CCB:" << endl;
    if (!control_info)
    {
        cout << "This CCB lost PCB,now change to end" << endl;
        return pair<CCB*, CCB*>(nullptr, nullptr);
    }
    cout << "G is: " << control_info->generation << endl;
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
        cout <<"<"<<data.set[i].x << ","<<data.set[i].y<<">";
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
    for (int i = 1; i < data.size(); i++)
    {
        if (temp_line.B > 0)
        {
            targetf = (f) * (temp_line.get_dis(data.set[i]));
            if (targetf > maxf)
            {
                maxf = targetf;
                max = i;
            };
        }
        else
        {
            targetf = (-1) * (f) * (temp_line.get_dis(data.set[i]));
            if (targetf > maxf)
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
    cout << "max is:" << max <<" "<<m.x<<" "<<m.y<< endl;
    pa.push(basea);
    pa.push(baseb);
    pb.push(basea);
    pb.push(baseb);
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
    cout << "baseline:" << " A:" << temp_line.A << " B:" << temp_line.B << " C:" << temp_line.C << endl;
    cout << "boundline1:" << " A:" << boundline1.A << " B:" << boundline1.B << " C:" << boundline1.C << endl;
    cout << "boundline2:" << " A:" << boundline2.A << " B:" << boundline2.B << " C:" << boundline2.C << endl;
    cout << "newline:" << " A:" << newline.A << " B:" << newline.B << " C:" << newline.C << endl;
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
        __POINT temp1 = bound->pre->value;
        __POINT temp2 = bound->next->value;
        if ((!(newb1 == temp1) && !(newb1 == temp2))) {
            n1 = new Node(newb1);
            if (bound == var->Head)
            {
                var->Head = n1;
            };
            if (bf2 == 1) {
                var->Tail = n1;
            }
            n1->next = bound->next;
            n1->pre = bound->pre;
            bound->pre->next = n1;
            bound->next->pre = n1;
            //delete bound;
            bound = n1;
            bf1 = 1;
            PCB* r1 = new PCB(n1, ba, f, g_mother - 1);
            R1 = new CCB(r1, pa);
        }
        else if (newb1 == temp1) {
            n1 = bound->pre;
            PCB* r1 = new PCB(n1, ba, f, g_mother - 1);
            R1 = new CCB(r1, pa);
            bound->pre->next = bound->next;
            bound->next->pre = bound->pre;
            //delete bound;
            bound = n1;
        }
        else {
            n1 = bound->next;
            PCB* r1 = new PCB(n1, ba, f, g_mother - 1);
            R1 = new CCB(r1, pa);
            bound->pre->next = bound->next;
            bound->next->pre = bound->pre;
            //delete bound;
            bound = n1->pre;
        };
        if (bound == var->Head)
        {
            var->Head = n1;
        };
        if (bf2 == 1) {
            var->Tail = n1;
        }
    }
    if (newline.A * boundline2.B != newline.B * boundline2.A) {
        cout << "New Bounding Point2: ";
        __POINT newb2 = newline.cross(boundline2);
        cout << "<" << newb2.x << "," << newb2.y << ">" << endl;
        Node* n2 = nullptr;
        __POINT temp1 = bound->value;
        __POINT temp2 = bound->next->value;
        if (bf1 == 1) {
            if ((!(newb2 == temp1) && !(newb2 == temp2)))
            {
                n2 = new Node(newb2);
                n2->pre = bound;
                n2->next = bound->next;
                bound->next->pre = n2;
                bound->next = n2;
            }
            else if (newb2 == temp1) {
                n2 = bound;
            }
            else {
                n2 = bound->next;
            }
        }
        else {
            if ((!(newb2 == temp1) && !(newb2 == temp2))) {
                n2 = new Node(newb2);
                n2->pre = bound;
                n2->next = bound->next;
                bound->next->pre = n2;
                bound->next = n2;
            }
            else if (newb2 == temp1) {
                n2 = bound;
            }
            else {
                n2 = bound->next;
            }
        }
        if (bf2 == 1) {
            var->Tail = n2;
        }
        PCB* r2 = new PCB(n2, bb, f, g_mother - 1);
        R2 = new CCB(r2, pb);
    }
    return pair<CCB*, CCB*>(R1, R2);
};
Dlist* bound(point_set original_set, int generation)
{
    int gener_counter = generation;
    Dlist* result = new Dlist;

    queue<CCB*> mia = bounding_initial(original_set, result, generation);
    cout<<"End Initialize"<<endl;
    cout << endl;
    while (!mia.empty())
    {
        cout<< endl;
        cout << "Now " << mia.size() << " CCB left." << endl;
        CCB* temp = mia.front();
        mia.pop();
        pair<CCB*, CCB*> temp_q = max_point_to_outside(result,temp);
        delete temp;
        if (temp_q.first)
        {
            mia.push(temp_q.first);
        }
        else {
            cout << "New CCB is None" << endl;
        };
        if (temp_q.second)
        {
            mia.push(temp_q.second);
        }
        else {
            cout << "New CCB is None" << endl;
        }
    };
    return result;
};
int main()
{
    __POINT* testp = new __POINT[10];
    for (int i = 0; i < 10; i++)
    {
        testp[i] = __POINT(i, i - 1);
    }
    point_set test_set;
    int G = 4;
    test_set.push(__POINT(1, 5));
    test_set.push(__POINT(3, 5));
    test_set.push(__POINT(2, 3));
    test_set.push(__POINT(0, 3));
    test_set.push(__POINT(1, 1));
    test_set.push(__POINT(2, 1));
    test_set.push(__POINT(5, 3));
    test_set.push(__POINT(3, 1));

    Dlist* result = bound(test_set, G);
    
    cout << "reult:" << endl;
    for (Node* temp = result->Head; temp != result->Tail; temp = temp->next) {
        if (temp) {
            cout << temp->value.x << " " << temp->value.y << endl;
        }
    }
    cout << result->Tail->value.x << " " << result->Tail->value.y << endl;
    
    /*
    for(int i=0;i<10;i++){
        cout<<testp[i].x<<" ";
        cout<<testp[i].y<<endl;
    }
    */
    /*
    point_set tests;
    for(int i =0;i<10;i++){
        tests.push(testp[i]);
        cout<<tests.size()<<endl;
    }
    cout<<tests.getDconer().x<<" "<<tests.getDconer().y<<endl;
    cout<<tests.getUconer().x<<" "<<tests.getUconer().y<<endl;
    cout<<tests.getRconer().x<<" "<<tests.getRconer().y<<endl;
    cout<<tests.getLconer().x<<" "<<tests.getLconer().y<<endl;
    */
    //straight_line testl(1,1,1);
    //cout<<testl.A<<" "<<testl.B<<" "<<testl.C<<endl;

    /*
    straight_line testl = straight_line(testp[0], testp[9]);
    cout << testl.A << " " << testl.B << " " << testl.C << endl;
    /*
    POINT testlp(0,1);
    straight_line testlpl = testl.get_parallel(testlp);
    cout<<testlpl.A<<" "<<testlpl.B<<" "<<testlpl.C<<endl;
    */
    /*
    straight_line testla(__POINT(1, 1), __POINT(0, 0));
    straight_line testlb(__POINT(1, 0), __POINT(0, 1));
    __POINT resp = testla.cross(testlb);
    cout << testlb.A << " " << testlb.B << " " << testlb.C << endl;
    cout << resp.x << " " << resp.y << endl;
    */
    /*
    straight_line testlb(__POINT(0, 1), __POINT(1, 0));
    cout << testlb.A << " " << testlb.B << " " << testlb.C << endl;
    __POINT testp1(2,2);
    cout<<testlb.get_dis(testp1)<<endl;
    cout << 1 << endl;
    */
    /*
    __POINT testpa(1,2);
    Node* testna = new Node(testpa);
    __POINT testpb(2,2);
    Node* testnb = new Node(testpb);
    __POINT testpc(2,1);
    Node* testnc = new Node(testpc);
    __POINT testpd(1,1);
    Node* testnd = new Node(testpd);
    Dlist * list = new Dlist;
    list->Head = testna;
    list->Tail = testna;
    list->insert(testnb);
    list->insert(testnc);
    list->insert(testnd);
    Node* testxiaosan = new Node(__POINT(0,0));
    Node* testxiaosi = new Node(__POINT(0,-1));
    testna->pre->next = testxiaosan;
    testna->next->pre = testxiaosi;
    testxiaosan->pre = testna->pre;
    testxiaosan->next = testxiaosi;
    testxiaosi->pre = testxiaosan;
    testxiaosi->next = testna->next;
    if(testna == list->Head){
        list->Head = testxiaosan;

    }
    delete testna;
    for(Node* temp = list->Head ; temp != list->Tail;temp=temp->next){
        cout<<temp->value.x<<" "<<temp->value.y<<endl;
    };
    cout<<list->Tail->value.x<<" "<<list->Tail->value.y<<endl;
    */
}