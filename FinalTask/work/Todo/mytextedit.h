#pragma execution_character_set("utf-8")

#include<qtextedit.h>
#include<qdebug.h>
#include<qfont.h>


class MyTextEdit :public QTextEdit {
	Q_OBJECT
public:
	friend class Todo;

	MyTextEdit(QWidget* parent = nullptr) :QTextEdit(parent), m_enterable(false) {
		//this->setStyleSheet("QTextEdit{color:rgb(75, 179, 175);border-color:rgb(242, 242, 242);border-style:solid;border-width;3px}");
		this->setStyleSheet("QTextEdit{color:rgb(75, 179, 175);border-color:rgb(210, 210, 210);border-width:1px;border-style:solid;}QTextEdit:hover{border-color:rgb(175, 175, 175);}");
		QFont font;
		font.setFamily("Microsoft YaHei");
		font.setPointSize(10);
		font.setBold(false);
		this->setFont(font);
		this->setGeometry(20, 70, 510, 31);
		this->setText("+ 点击新建待办");
		this->setPlaceholderText("输入内容后，回车创建成功");
		//initDataBase();
	};
	void mousePressEvent(QMouseEvent* event) override {
		this->setReadOnly(false);
		//qDebug() << "text edit";
		if (this->toPlainText() == "+ 点击新建待办") {
			this->setText("");
			this->setStyleSheet("color:rgb(0,0,0);border-color:rgb(75, 179, 175);border-width:1px;border-style:solid;");
		}
		else
			this->setStyleSheet("color:rgb(0,0,0);border-color:rgb(75, 179, 175);border-width:1px;border-style:solid;");
		m_enterable = true;
		qDebug() << "you can enter";
		QTextEdit::mousePressEvent(event);
	}


	void setType(QString type) {
		this->m_type = type;
	}
	
private:
	bool m_enterable;
	//QString m_string;
	//QSqlDatabase m_db;
	QString m_type;
};