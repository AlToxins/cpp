/********************************************************************************
** Form generated from reading UI file 'NewWindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NEWWINDOW_H
#define UI_NEWWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLayout>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableView>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QToolBox>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QLabel *label;
    QToolBox *toolBox;
    QWidget *page;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_5;
    QLabel *label_6;
    QToolButton *toolButton;
    QLabel *label_7;
    QLabel *label_8;
    QSpinBox *spinBox;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QTableView *tableView;
    QLabel *label_9;
    QLineEdit *lineEdit;
    QLineEdit *lineEdit_2;
    QLineEdit *lineEdit_3;
    QWidget *page_2;
    QLabel *label_10;
    QLabel *label_11;
    QLabel *label_12;
    QLabel *label_13;
    QLabel *label_14;
    QLabel *label_15;
    QLineEdit *lineEdit_4;
    QTextEdit *textEdit;
    QTextEdit *textEdit_2;
    QSpinBox *spinBox_2;
    QTextEdit *textEdit_3;
    QLabel *label_16;
    QLabel *label_17;
    QLabel *label_18;
    QToolButton *toolButton_2;
    QTextEdit *textEdit_4;
    QPushButton *pushButton_3;
    QPushButton *pushButton_4;
    QPushButton *pushButton_5;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(900, 486);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        label = new QLabel(centralwidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(300, 10, 271, 41));
        QFont font;
        font.setFamily(QStringLiteral("Microsoft YaHei"));
        font.setPointSize(25);
        label->setFont(font);
        toolBox = new QToolBox(centralwidget);
        toolBox->setObjectName(QStringLiteral("toolBox"));
        toolBox->setGeometry(QRect(0, 60, 781, 401));
        toolBox->setStyleSheet(QStringLiteral(""));
        page = new QWidget();
        page->setObjectName(QStringLiteral("page"));
        page->setGeometry(QRect(0, 0, 781, 341));
        label_2 = new QLabel(page);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(20, 20, 53, 16));
        label_3 = new QLabel(page);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(20, 60, 53, 16));
        label_4 = new QLabel(page);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(20, 110, 53, 16));
        label_5 = new QLabel(page);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(20, 160, 53, 16));
        label_6 = new QLabel(page);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(20, 210, 71, 16));
        toolButton = new QToolButton(page);
        toolButton->setObjectName(QStringLiteral("toolButton"));
        toolButton->setGeometry(QRect(60, 20, 75, 24));
        label_7 = new QLabel(page);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setGeometry(QRect(150, 110, 53, 16));
        label_8 = new QLabel(page);
        label_8->setObjectName(QStringLiteral("label_8"));
        label_8->setGeometry(QRect(180, 110, 53, 16));
        spinBox = new QSpinBox(page);
        spinBox->setObjectName(QStringLiteral("spinBox"));
        spinBox->setGeometry(QRect(60, 160, 81, 22));
        pushButton = new QPushButton(page);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(40, 270, 75, 24));
        pushButton_2 = new QPushButton(page);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        pushButton_2->setGeometry(QRect(40, 310, 75, 24));
        tableView = new QTableView(page);
        tableView->setObjectName(QStringLiteral("tableView"));
        tableView->setGeometry(QRect(340, 0, 441, 341));
        label_9 = new QLabel(page);
        label_9->setObjectName(QStringLiteral("label_9"));
        label_9->setGeometry(QRect(310, 110, 53, 16));
        lineEdit = new QLineEdit(page);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        lineEdit->setGeometry(QRect(60, 60, 251, 31));
        lineEdit_2 = new QLineEdit(page);
        lineEdit_2->setObjectName(QStringLiteral("lineEdit_2"));
        lineEdit_2->setGeometry(QRect(60, 110, 91, 31));
        lineEdit_3 = new QLineEdit(page);
        lineEdit_3->setObjectName(QStringLiteral("lineEdit_3"));
        lineEdit_3->setGeometry(QRect(220, 110, 91, 31));
        toolBox->addItem(page, QString::fromUtf8("\346\226\260 \345\223\201 \345\205\245 \345\272\223"));
        label_9->raise();
        label_2->raise();
        label_3->raise();
        label_4->raise();
        label_5->raise();
        label_6->raise();
        toolButton->raise();
        label_7->raise();
        label_8->raise();
        spinBox->raise();
        pushButton->raise();
        pushButton_2->raise();
        tableView->raise();
        lineEdit->raise();
        lineEdit_2->raise();
        lineEdit_3->raise();
        page_2 = new QWidget();
        page_2->setObjectName(QStringLiteral("page_2"));
        page_2->setGeometry(QRect(0, 0, 781, 341));
        label_10 = new QLabel(page_2);
        label_10->setObjectName(QStringLiteral("label_10"));
        label_10->setGeometry(QRect(20, 20, 53, 16));
        label_11 = new QLabel(page_2);
        label_11->setObjectName(QStringLiteral("label_11"));
        label_11->setGeometry(QRect(20, 60, 53, 16));
        label_12 = new QLabel(page_2);
        label_12->setObjectName(QStringLiteral("label_12"));
        label_12->setGeometry(QRect(20, 100, 53, 16));
        label_13 = new QLabel(page_2);
        label_13->setObjectName(QStringLiteral("label_13"));
        label_13->setGeometry(QRect(180, 100, 53, 16));
        label_14 = new QLabel(page_2);
        label_14->setObjectName(QStringLiteral("label_14"));
        label_14->setGeometry(QRect(20, 140, 53, 16));
        label_15 = new QLabel(page_2);
        label_15->setObjectName(QStringLiteral("label_15"));
        label_15->setGeometry(QRect(180, 140, 53, 16));
        lineEdit_4 = new QLineEdit(page_2);
        lineEdit_4->setObjectName(QStringLiteral("lineEdit_4"));
        lineEdit_4->setGeometry(QRect(60, 60, 211, 31));
        textEdit = new QTextEdit(page_2);
        textEdit->setObjectName(QStringLiteral("textEdit"));
        textEdit->setGeometry(QRect(60, 100, 91, 31));
        textEdit->setStyleSheet(QStringLiteral("background-color:rgb(227, 227, 227)"));
        textEdit_2 = new QTextEdit(page_2);
        textEdit_2->setObjectName(QStringLiteral("textEdit_2"));
        textEdit_2->setGeometry(QRect(220, 100, 91, 31));
        textEdit_2->setStyleSheet(QStringLiteral("background-color:rgb(227, 227, 227)"));
        spinBox_2 = new QSpinBox(page_2);
        spinBox_2->setObjectName(QStringLiteral("spinBox_2"));
        spinBox_2->setGeometry(QRect(60, 140, 81, 22));
        textEdit_3 = new QTextEdit(page_2);
        textEdit_3->setObjectName(QStringLiteral("textEdit_3"));
        textEdit_3->setGeometry(QRect(220, 140, 91, 31));
        textEdit_3->setStyleSheet(QStringLiteral("background-color:rgb(227, 227, 227)"));
        label_16 = new QLabel(page_2);
        label_16->setObjectName(QStringLiteral("label_16"));
        label_16->setGeometry(QRect(150, 100, 53, 16));
        label_17 = new QLabel(page_2);
        label_17->setObjectName(QStringLiteral("label_17"));
        label_17->setGeometry(QRect(310, 100, 53, 16));
        label_18 = new QLabel(page_2);
        label_18->setObjectName(QStringLiteral("label_18"));
        label_18->setGeometry(QRect(310, 140, 53, 16));
        toolButton_2 = new QToolButton(page_2);
        toolButton_2->setObjectName(QStringLiteral("toolButton_2"));
        toolButton_2->setGeometry(QRect(60, 20, 75, 24));
        textEdit_4 = new QTextEdit(page_2);
        textEdit_4->setObjectName(QStringLiteral("textEdit_4"));
        textEdit_4->setGeometry(QRect(340, 20, 441, 321));
        pushButton_3 = new QPushButton(page_2);
        pushButton_3->setObjectName(QStringLiteral("pushButton_3"));
        pushButton_3->setGeometry(QRect(40, 230, 75, 24));
        pushButton_4 = new QPushButton(page_2);
        pushButton_4->setObjectName(QStringLiteral("pushButton_4"));
        pushButton_4->setGeometry(QRect(40, 270, 75, 24));
        pushButton_5 = new QPushButton(page_2);
        pushButton_5->setObjectName(QStringLiteral("pushButton_5"));
        pushButton_5->setGeometry(QRect(280, 60, 31, 31));
        toolBox->addItem(page_2, QString::fromUtf8("\351\242\204 \345\224\256 \350\256\242 \345\215\225"));
        MainWindow->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        toolBox->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", Q_NULLPTR));
        label->setText(QApplication::translate("MainWindow", "\345\225\206 \345\223\201 \347\256\241 \347\220\206", Q_NULLPTR));
        label_2->setText(QApplication::translate("MainWindow", "\347\261\273 \345\210\253\357\274\232", Q_NULLPTR));
        label_3->setText(QApplication::translate("MainWindow", "\345\220\215 \347\247\260\357\274\232", Q_NULLPTR));
        label_4->setText(QApplication::translate("MainWindow", "\350\277\233 \344\273\267\357\274\232", Q_NULLPTR));
        label_5->setText(QApplication::translate("MainWindow", "\346\225\260 \351\207\217\357\274\232", Q_NULLPTR));
        label_6->setText(QApplication::translate("MainWindow", "\345\225\206 \345\223\201 \350\257\246 \346\203\205\357\274\232", Q_NULLPTR));
        toolButton->setText(QApplication::translate("MainWindow", "...", Q_NULLPTR));
        label_7->setText(QApplication::translate("MainWindow", "\357\277\245", Q_NULLPTR));
        label_8->setText(QApplication::translate("MainWindow", "\345\224\256 \344\273\267\357\274\232", Q_NULLPTR));
        pushButton->setText(QApplication::translate("MainWindow", "\345\205\245 \345\272\223", Q_NULLPTR));
        pushButton_2->setText(QApplication::translate("MainWindow", "\346\270\205 \344\273\223", Q_NULLPTR));
        label_9->setText(QApplication::translate("MainWindow", "\357\277\245", Q_NULLPTR));
        toolBox->setItemText(toolBox->indexOf(page), QApplication::translate("MainWindow", "\346\226\260 \345\223\201 \345\205\245 \345\272\223", Q_NULLPTR));
        label_10->setText(QApplication::translate("MainWindow", "\347\261\273 \345\210\253\357\274\232", Q_NULLPTR));
        label_11->setText(QApplication::translate("MainWindow", "\345\220\215 \347\247\260\357\274\232", Q_NULLPTR));
        label_12->setText(QApplication::translate("MainWindow", "\345\215\225 \344\273\267\357\274\232", Q_NULLPTR));
        label_13->setText(QApplication::translate("MainWindow", "\345\272\223 \345\255\230\357\274\232", Q_NULLPTR));
        label_14->setText(QApplication::translate("MainWindow", "\346\225\260 \351\207\217\357\274\232", Q_NULLPTR));
        label_15->setText(QApplication::translate("MainWindow", "\346\200\273 \344\273\267\357\274\232", Q_NULLPTR));
        label_16->setText(QApplication::translate("MainWindow", "\357\277\245", Q_NULLPTR));
        label_17->setText(QApplication::translate("MainWindow", "\344\273\266", Q_NULLPTR));
        label_18->setText(QApplication::translate("MainWindow", "\357\277\245", Q_NULLPTR));
        toolButton_2->setText(QApplication::translate("MainWindow", "...", Q_NULLPTR));
        pushButton_3->setText(QApplication::translate("MainWindow", "\345\207\272 \345\224\256", Q_NULLPTR));
        pushButton_4->setText(QApplication::translate("MainWindow", "\344\270\213 \345\215\225", Q_NULLPTR));
        pushButton_5->setText(QApplication::translate("MainWindow", "ok", Q_NULLPTR));
        toolBox->setItemText(toolBox->indexOf(page_2), QApplication::translate("MainWindow", "\351\242\204 \345\224\256 \350\256\242 \345\215\225", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NEWWINDOW_H
