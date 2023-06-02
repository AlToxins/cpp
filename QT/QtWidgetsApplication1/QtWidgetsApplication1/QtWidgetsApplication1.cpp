#include "QtWidgetsApplication1.h"
#include<qpushbutton.h>
#include<qlineedit.h>
#include<qdebug.h>
#include<qstring.h>
#include<qlayout.h>
#include<qlabel.h>
#include<qmessagebox.h>
QtWidgetsApplication1::QtWidgetsApplication1(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    

    this->setWindowTitle("Test");

    //添加垂直布局
    QGridLayout* layout1 = new QGridLayout(this);



    //设计控件
    //QLabel* label1 = new QLabel(this);
   
    QLabel* label2 = new QLabel(this);
   
    QLabel* label3 = new QLabel(this);
    QLabel* label4 = new QLabel(this);

    
    //label1->setText("Log In");
    label2->setText("User name or Mail");
    label3->setText("Password");
    label4->setText("Source");

    //输入邮箱或者账号
    lineEdit1 = new QLineEdit(this);
    
    //输入密码
    lineEdit2 = new QLineEdit(this);

    //登录按钮
    QPushButton* button1 = new QPushButton(this);

    
    button1->setText("log in");
    

    this->resize(500, 500);
    



    //设计布局
    //layout1->addWidget(label1, 0, 0, 1, 2, Qt::AlignCenter); //将label1放在第0行第0列，跨越1行2列，居中对齐
    QWidget* widget2 = new QWidget(this);

    widget2->setGeometry(0, 0, 500, 100);

    widget2->setStyleSheet("background-color:gray;");

    QLabel* label1 = new QLabel(widget2);

    label1->setStyleSheet("color:white;");

    label1->setText("login");

    layout1->addWidget(widget2, 0, 0, Qt::AlignCenter);
    layout1->addWidget(label2, 1, 0, Qt::AlignRight); //将label2放在第1行第0列，右对齐
    layout1->addWidget(lineEdit1, 1, 1); //将lineEdit1放在第1行第1列
    layout1->addWidget(label3, 2, 0, Qt::AlignRight); //将label3放在第2行第0列，右对齐
    layout1->addWidget(lineEdit2, 2, 1); //将lineEdit2放在第2行第1列
    layout1->addWidget(label4, 3, 0, Qt::AlignRight); //将label4放在第3行第0列
    layout1->addWidget(button1, 4, 1, Qt::AlignCenter);

    //layout2->addWidget(label1);
    //layout2->addWidget(label2);

    //layout3->addWidget(lineEdit1);
    //layout3->addWidget(lineEdit2);

    //layout4->addLayout(layout1);
    //layout4->addLayout(layout2);
    

    layout1->setVerticalSpacing(10); //设置垂直间距为10像素

    QWidget* widget = new QWidget(this);

    //QWidget* widget2 = new QWidget(this);

    //widget2->setGeometry(0, 0, 500, 100);

    //widget2->setStyleSheet("background-color:gray;");

    //QLabel* label1 = new QLabel(widget2);

    //label1->setStyleSheet("color:white;");

    //label1->setText("login");

    widget->setLayout(layout1); //将layout1设置为窗口的布局

    this->setCentralWidget(widget);



    //连接槽函数
    connect(button1, SIGNAL(clicked()), this, SLOT(on_login_clicked()));
}

bool QtWidgetsApplication1::inputCorrect(){
    if (lineEdit1->text() == userName && lineEdit2->text() == passWord)return true;
    else return false;
}


void QtWidgetsApplication1::on_login_clicked() {
    QMessageBox msgBox;
    if (inputCorrect()) msgBox.setText("Success");
    else msgBox.setText("Failed");
    msgBox.exec();
}

QtWidgetsApplication1::~QtWidgetsApplication1()
{}
