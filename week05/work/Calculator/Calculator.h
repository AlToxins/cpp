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
    void resizeEvent(QResizeEvent* event) override;     //������д�ĺ���
    QString calculate();   //�����׺���ʽ�����ؽ��
    
    //�жϵ�ǰ������Ƿ���ջ
    bool operatorInStack(QString text);



private:
    Ui::CalculatorClass ui;
    stack<QString>m_stack;     //�洢��׺���ʽ
    bool m_operatorClicked;       //��һ�ΰ����������ť
    bool m_equalClicked;
    bool m_dotClicked;        //��һ�ΰ���С����
    QString m_string;   //��¼����ʽ
    QString m_number;   //��¼ÿ������


    stack<QString>m_operatorStack;  //�����ջ
    stack<QString>m_numberStack;    //�м���ջ


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
