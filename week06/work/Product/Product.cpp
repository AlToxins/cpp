#include "Product.h"
#include<qmessagebox.h>

Product::Product(QWidget *parent)
	: QMainWindow(parent), username("zhangsan"), password("123456")
{

	ui.setupUi(this);

	newWidget = new NewWidget();
	//���õ�¼����
	this->setWindowTitle("�� ¼");
	
	

	//�ۺ���
	(void)connect(ui.pushButton, &QPushButton::clicked, this, &Product::on_login_clicked);
}

bool Product::on_login_clicked() {
	if (ui.textEdit->toPlainText() == username && ui.textEdit_2->toPlainText() == password) {
		newWidget->show();
		this->hide();
		return true;
	}
	else if (ui.textEdit->toPlainText() != username) {
		QMessageBox::information(this, "�û�����", "��������ȷ���û���", QMessageBox::Ok);
		return false;
	}
	else if (ui.textEdit_2->toPlainText() != password&& ui.textEdit->toPlainText() == username) {
		QMessageBox::information(this, "�������", "��������ȷ������", QMessageBox::Ok);
		return false;
	}
	return false;
}

//void QTextEdit::keyPressEvent(QKeyEvent* event)
//{
//    // ������µļ������ּ�
//    if (event->key() >= Qt::Key_0 && event->key() <= Qt::Key_9)
//    {
//        event->ignore();
//    }
//    // ������Ը��¼�
//    else
//    {
//        event->ignore();
//    }
//}
