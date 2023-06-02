/********************************************************************************
** Form generated from reading UI file 'Product.ui'
**
** Created by: Qt User Interface Compiler version 5.9.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PRODUCT_H
#define UI_PRODUCT_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ProductClass
{
public:
    QWidget *centralWidget;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QTextEdit *textEdit;
    QTextEdit *textEdit_2;
    QPushButton *pushButton;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *ProductClass)
    {
        if (ProductClass->objectName().isEmpty())
            ProductClass->setObjectName(QStringLiteral("ProductClass"));
        ProductClass->resize(600, 400);
        QFont font;
        font.setPointSize(15);
        ProductClass->setFont(font);
        centralWidget = new QWidget(ProductClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(90, 30, 431, 61));
        QFont font1;
        font1.setFamily(QStringLiteral("Microsoft YaHei"));
        font1.setPointSize(25);
        label->setFont(font1);
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(120, 110, 91, 31));
        QFont font2;
        font2.setFamily(QStringLiteral("Microsoft YaHei"));
        font2.setPointSize(15);
        label_2->setFont(font2);
        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(120, 160, 91, 31));
        label_3->setFont(font2);
        textEdit = new QTextEdit(centralWidget);
        textEdit->setObjectName(QStringLiteral("textEdit"));
        textEdit->setGeometry(QRect(210, 100, 191, 41));
        textEdit_2 = new QTextEdit(centralWidget);
        textEdit_2->setObjectName(QStringLiteral("textEdit_2"));
        textEdit_2->setGeometry(QRect(210, 160, 191, 41));
        pushButton = new QPushButton(centralWidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(230, 220, 101, 41));
        pushButton->setFont(font2);
        pushButton->setStyleSheet(QStringLiteral("QPushButton{border-radius: 5px; background-color:rgb(255, 255, 255);border-color:rgb(210, 210, 210);border-width:1px;border-style:solid;}QPushButton:hover { background-color: rgb(250,250,250);}QPushButton:pressed{background-color:rgb(245, 245, 245);color:rgb(100, 100,100)}"));
        ProductClass->setCentralWidget(centralWidget);
        mainToolBar = new QToolBar(ProductClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        ProductClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(ProductClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        ProductClass->setStatusBar(statusBar);

        retranslateUi(ProductClass);

        QMetaObject::connectSlotsByName(ProductClass);
    } // setupUi

    void retranslateUi(QMainWindow *ProductClass)
    {
        ProductClass->setWindowTitle(QApplication::translate("ProductClass", "Product", Q_NULLPTR));
        label->setText(QApplication::translate("ProductClass", "\346\254\242 \350\277\216 \350\277\233 \345\205\245 \345\225\206 \345\223\201 \347\256\241 \347\220\206 \347\263\273 \347\273\237", Q_NULLPTR));
        label_2->setText(QApplication::translate("ProductClass", "\347\256\241 \347\220\206 \345\221\230\357\274\232", Q_NULLPTR));
        label_3->setText(QApplication::translate("ProductClass", "\345\217\243     \344\273\244\357\274\232", Q_NULLPTR));
        pushButton->setText(QApplication::translate("ProductClass", "\347\231\273 \345\275\225", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class ProductClass: public Ui_ProductClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PRODUCT_H
