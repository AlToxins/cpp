#pragma once

#include <QtWidgets/QMainWindow>
#include<iostream>
#include "ui_QtWidgetsApplication1.h"
#include<qlineedit.h>

class QtWidgetsApplication1 : public QMainWindow
{
    Q_OBJECT

public:
    QtWidgetsApplication1(QWidget *parent = nullptr);
    ~QtWidgetsApplication1();
    bool inputCorrect();


private:
    Ui::QtWidgetsApplication1Class ui;
    const QString userName = "zhangsan";
    const QString passWord = "123456";
    QLineEdit* lineEdit1;
    QLineEdit* lineEdit2;


private slots:
    void on_login_clicked();

};
