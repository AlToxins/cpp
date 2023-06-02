#include "Product.h"
#include<qmessagebox.h>

Product::Product(QWidget *parent)
	: QMainWindow(parent), username("zhangsan"), password("123456")
{

	ui.setupUi(this);

	newWidget = new NewWidget();
	//设置登录界面
	this->setWindowTitle("登 录");
	
	

	//槽函数
	(void)connect(ui.pushButton, &QPushButton::clicked, this, &Product::on_login_clicked);
}

bool Product::on_login_clicked() {
	if (ui.textEdit->toPlainText() == username && ui.textEdit_2->toPlainText() == password) {
		newWidget->show();
		this->hide();
		return true;
	}
	else if (ui.textEdit->toPlainText() != username) {
		QMessageBox::information(this, "用户错误", "请输入正确的用户名", QMessageBox::Ok);
		return false;
	}
	else if (ui.textEdit_2->toPlainText() != password&& ui.textEdit->toPlainText() == username) {
		QMessageBox::information(this, "密码错误", "请输入正确的密码", QMessageBox::Ok);
		return false;
	}
	return false;
}

//void QTextEdit::keyPressEvent(QKeyEvent* event)
//{
//    // 如果按下的键是数字键
//    if (event->key() >= Qt::Key_0 && event->key() <= Qt::Key_9)
//    {
//        event->ignore();
//    }
//    // 否则忽略该事件
//    else
//    {
//        event->ignore();
//    }
//}
