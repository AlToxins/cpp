#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Calculator.h"
#include<stack>

using std::stack;

class Calculator : public QMainWindow
{
    Q_OBJECT

public:
    Calculator(QWidget *parent = nullptr);
    ~Calculator();
    void resizeEvent(QResizeEvent* event) override;     //声明重写的函数
    QString calculate();   //计算后缀表达式并返回结果
    
    //判断当前运算符是否入栈
    bool operatorInStack(QString text);



private:
    Ui::CalculatorClass ui;
    stack<QString>m_stack;     //存储后缀表达式
    bool m_operatorClicked;       //第一次按下运算符按钮
    bool m_equalClicked;
    bool m_dotClicked;        //第一次按下小数点
    QString m_string;   //记录运算式
    QString m_number;   //记录每个数字


    stack<QString>m_operatorStack;  //运算符栈
    stack<QString>m_numberStack;    //中间结果栈


private slots:
    void on_negative_clicked();
    void on_dot_clicked();
    void on_delete_clicked();
    void on_clear_clicked();
    void on_operator_clicked(QPushButton* button);
    void on_number_clicked(QPushButton* button);
    void on_reciprocal_clicked();
    void on_square_clicked();
    void on_extract_clicked();
    void on_absolute_clicked();
    void on_percent_clicked();
};
