#pragma execution_character_set("utf-8")

#include<qpushbutton.h>
#include<qdebug.h>
#include<qtoolbutton.h>
#include<qtextedit.h>
#include<qfont.h>

class MyPushButton :public QPushButton {
	Q_OBJECT
		friend class Todo;

public:
	MyPushButton(QWidget* parent = nullptr)
		:QPushButton(parent)
	{
		//this->deadTime = new QTextEdit(this);
		QFont font;
		font.setFamily("Microsoft YaHei");
		font.setPointSize(10);
		font.setBold(false);
		this->setFont(font);
		QString styleSheet_1 = "QPushButton{background-color:transparent;border:none;border-radius:3px}";
		QString styleSheet_2 = "QPushButton{icon:url(Resources/MyButton.png)}";
		QString styleSheet_3 = "QPushButton:hover { background-color: rgb(245,245,245);icon:url(Resources/MyButton_gray.png)}";
		QString styleSheet_4 = "QPushButton{text-align:left}";
		QString styleSheet = styleSheet_1 + styleSheet_2 + styleSheet_3 + styleSheet_4;
		m_styleSheet = styleSheet_1 + styleSheet_4;
		this->setStyleSheet(styleSheet);
	}


private:

	bool done;
	QString name;
	QString priority;
	QString deadTime;
	QString remind;
	QString describe;
	QString location;
	QString note;
	QString type;
	QString m_styleSheet;
	int m_priority = 0;
};