#include "Todo.h"
#include<qstyle.h>
#include<qdebug.h>
#include<qgroupbox.h>
#include<QKeyEvent>
#include<qmenu.h>
#include<qalgorithms.h>
#include<algorithm>
#include<QDate>


Todo::Todo(QWidget *parent)
	: QMainWindow(parent), m_closeClicked(false), m_show(0), m_show2(0)
{
	ui.setupUi(this);
	

	
	//初始化数据库
	initDatabase();

	m_textEditList = this->findChildren<QTextEdit*>();


	////读取数据库
	//readFromDB();
	//
	////初始化我的首页
	//initMyPage();

	//默认点击第一个按钮
	m_lastClickedButton.push_back(ui.pushButton);
	ui.pushButton->setProperty("clicked", true);
	ui.pushButton->style()->unpolish(ui.pushButton);
	ui.pushButton->style()->polish(ui.pushButton);
	ui.stackedWidget->setCurrentIndex(0); 
	ui.stackedWidget_2->setCurrentIndex(0);

	//添加输入框
	myTextEdit = new MyTextEdit(ui.page);
	myTextEdit->setType("我的待办");
	myTextEdit_2 = new MyTextEdit(ui.page_2);
	myTextEdit_2->setType("我的待办");
	myTextEdit_3 = new MyTextEdit(ui.page_3);
	myTextEdit_3->setType("共享分组");


	//为输入框添加消息过滤
	ui.page->installEventFilter(this);
	ui.page_2->installEventFilter(this);
	ui.page_3->installEventFilter(this);
	//myTextEdit->viewport()->installEventFilter(this);
	myTextEdit->installEventFilter(this);
	myTextEdit_2->installEventFilter(this);
	myTextEdit_3->installEventFilter(this);
	
	foreach(QTextEdit * textEdit, m_textEditList) {
		textEdit->installEventFilter(this);
	}


	//设置优先级菜单
	setPriority();

	//设置排序菜单
	setSort();

	//连接槽函数
	(void)connect(ui.pushButton, &QPushButton::clicked, this, [this] {on_pushButton_clicked(ui.pushButton); ui.stackedWidget->setCurrentIndex(0); ui.stackedWidget_2->setCurrentIndex(0); });
	(void)connect(ui.pushButton_2, &QPushButton::clicked, this, [this] {on_pushButton_clicked(ui.pushButton_2); ui.stackedWidget->setCurrentIndex(1); ui.stackedWidget_2->setCurrentIndex(0); });
	(void)connect(ui.pushButton_3, &QPushButton::clicked, this, [this] {on_pushButton_clicked(ui.pushButton_3); ui.stackedWidget->setCurrentIndex(2); ui.stackedWidget_2->setCurrentIndex(0); });
	(void)connect(ui.pushButton_6, &QPushButton::clicked, this, &Todo::on_closeButton_clicked);
	(void)connect(ui.pushButton_15, &QPushButton::clicked, this, &Todo::on_changeName_clicked);
	(void)connect(ui.pushButton_7, &QPushButton::clicked, this, & Todo::initMyPage);
	(void)connect(ui.pushButton_16, &QPushButton::clicked, this, &Todo::readFromDB);
	(void)connect(ui.pushButton_19, &QPushButton::clicked, this, &Todo::readFromDB);
	(void)connect(ui.pushButton_12, &QPushButton::clicked, this, &Todo::on_done_clicked);
	(void)connect(ui.pushButton_4, &QPushButton::clicked, this, [=] {on_showButton_clicked(ui.pushButton_4); });
	(void)connect(ui.pushButton_5, &QPushButton::clicked, this, [=] {on_showButton_clicked(ui.pushButton_5); });

	//读取数据库
	readFromDB();

	//初始化我的首页
	initMyPage();
}

void Todo::initDatabase() {
	m_db = QSqlDatabase::addDatabase("QSQLITE");
	m_db.setDatabaseName("todo.db");
	if (!m_db.open()) {
		qDebug() << __FUNCTION__ << m_db.lastError().text();
		return;
	}
	m_sqlTable = new QSqlTableModel(this);
	m_sqlTable->setTable("list");
}

void Todo::initMyPage() {
	if (m_allList.length() != 0) {
		m_allList.clear();
	}

	while (QLayoutItem* item = ui.verticalLayout_5->takeAt(0)) {
		QWidget* widget = item->widget();
		if (widget) {
			widget->deleteLater();
			delete item;
		}
	}

	while (QLayoutItem* item = ui.verticalLayout_6->takeAt(0)) {
		QWidget* widget = item->widget();
		if (widget) {
			widget->deleteLater();
			delete item;
		}
	}

	while (QLayoutItem* item = ui.verticalLayout_7->takeAt(0)) {
		QWidget* widget = item->widget();
		if (widget) {
			widget->deleteLater();
			delete item;
		}
	}

	QSqlQuery query("SELECT * FROM list");
	QString date = QDate::currentDate().toString();
	date = date.right(date.length() - 3);
	date = date.left(date.length() - 4);
	date = date.right(2);
	qDebug() << date;
	while (query.next()) {
		QString string = query.value(3).toString();
		MyPushButton* button = new MyPushButton(ui.page_10);
		button->setText(query.value(1).toString());
		button->m_priority = query.value(2).toInt();
		button->type = query.value(0).toString();
		if (query.value(8).toString()!="0") {
			button->done = true;
			QString styleSheet = "QPushButton{icon:url(Resources/finish.png)}";
			button->setStyleSheet(button->m_styleSheet + styleSheet);
		}
		else {
			button->done = false;
		}
		//未安排
		if (string == "") {
			addToLayout(button, ui.verticalLayout_5, query);
		}
		//未来七天
		else if(string != "" && string.right(2) <QString::number(date.toInt()+7)){
			addToLayout(button, ui.verticalLayout_6, query);
		}
		//以后
		else if (string != "" && string.right(2)> QString::number(date.toInt() + 7)) {
			addToLayout(button, ui.verticalLayout_7, query);
		}
		m_allList.push_back(button);
	}
	int i = 0;
	while (i < m_allList.length()) {
		(void)connect(m_allList[i], &MyPushButton::clicked, this, [=]() {on_myTodo_clicked(m_allList[i]), ui.stackedWidget_2->setCurrentIndex(1); });
		i++;
	}
}

void Todo::readFromDB() {
	if (m_todoList.length()!=0) {
		//disconnectMyButton();
		m_todoList.clear();
		m_shareList.clear();
	}
	m_todoNumber = 0;
	m_shareNumber = 0;
	m_finishTodo = 0;
	m_finishShare = 0;
	//清空垂直布局中的内容
	while (QLayoutItem* item = ui.verticalLayout->takeAt(0)) {
		QWidget* widget = item->widget();
		if (widget) {
			widget->deleteLater();
			delete item;
		}
	}
	while (QLayoutItem* item = ui.verticalLayout_2->takeAt(0)) {
		QWidget* widget = item->widget();
		if (widget) {
			widget->deleteLater();
			delete item;
		}
	}
	while (QLayoutItem* item = ui.verticalLayout_4->takeAt(0)) {
		QWidget* widget = item->widget();
		if (widget) {
			widget->deleteLater();
			delete item;
		}
	}
	while (QLayoutItem* item = ui.verticalLayout_3->takeAt(0)) {
		QWidget* widget = item->widget();
		if (widget) {
			widget->deleteLater();
			delete item;
		}
	}
	QSqlQuery query("SELECT * FROM list");
	while (query.next()) {
		if (query.value(0) == "我的待办"&&query.value(8).toString()=="0") {
			MyPushButton* button = new MyPushButton(ui.layoutWidget);
			button->setText(query.value(1).toString());
			button->m_priority = query.value(2).toInt();
			button->done = false;
			//button->type = query.value(0).toString();
			//ui.verticalLayout->addWidget(button);
			addToLayout(button, ui.verticalLayout, query);

			m_todoList.push_back(button);
			m_todoNumber++;
		}
		else if(query.value(0)=="共享分组" && query.value(8).toString() == "0") {
			MyPushButton* button = new MyPushButton(ui.layoutWidget_2);
			button->setText(query.value(1).toString());
			button->m_priority = query.value(2).toInt();
			button->done = false;
			//button->type = query.value(0).toString();
			//ui.verticalLayout_2->addWidget(button);
			addToLayout(button, ui.verticalLayout_2, query);

			m_shareList.push_back(button);
			m_shareNumber++;
		}
		else if (query.value(0) == "我的待办" && query.value(8) != "0") {
			MyPushButton* button = new MyPushButton(ui.verticalLayoutWidget_2);
			button->setText(query.value(1).toString());
			button->m_priority = query.value(2).toInt();
			button->done = true;
			//button->type = query.value(0).toString();
			addToLayout(button, ui.verticalLayout_4, query);
			m_todoList.push_back(button);
			m_finishTodo++;
			//button->setIcon(QIcon(":/Todo/finish.png"));
			//button->setStyleSheet("QPushButton{icon:url(Resources/finish.png)}");
			QString styleSheet = "QPushButton{icon:url(Resources/finish.png)}";
			button->setStyleSheet(button->m_styleSheet + styleSheet);
		}
		else if (query.value(0) == "共享分组" && query.value(8) != "0") {
			MyPushButton* button = new MyPushButton(ui.verticalLayoutWidget);
			button->setText(query.value(1).toString());
			button->m_priority = query.value(2).toInt();
			button->done = true;
			
			addToLayout(button, ui.verticalLayout_3, query);
			m_todoList.push_back(button);
			m_finishShare++;
			//button->setIcon(QIcon(":/Todo/finish.png"));
			//button->setStyleSheet("QPushButton{icon:url(Resources/finish.png)}");
			QString styleSheet = "QPushButton{icon:url(Resources/finish.png)}";
			button->setStyleSheet(button->m_styleSheet + styleSheet);
		}
	}
	connectMyButton();
	QResizeEvent* event;
	resizeEvent(event);
}


void Todo::addToLayout(MyPushButton* button, QVBoxLayout* layout, QSqlQuery query) {
	layout->addWidget(button);
	button->type = query.value(0).toString();
	button->name = query.value(1).toString();
	button->deadTime = query.value(3).toString();
	button->remind = query.value(4).toString();
	button->describe = query.value(5).toString();
	button->location = query.value(6).toString();
	button->note = query.value(7).toString();
}

void Todo::addToLayout(MyPushButton* button, QVBoxLayout* layout) {
	layout->addWidget(button);
}



void Todo::resizeEvent(QResizeEvent* event) {
	QWidget::resizeEvent(event);
	int w = this->width();
	int h = this->height();
	if (!m_closeClicked) {
		if (w >= 600) {
			ui.frame_4->setGeometry(w - 350, 60, 1, 1000);
			ui.stackedWidget->setGeometry(260, 70, w - 610, h - 70);
			ui.stackedWidget_2->setGeometry(w - 334, 70, 321, h-70);

			//QGroupBox* groupBox = new QGroupBox();
			
			myTextEdit->setGeometry(20, 70, w - 650, 31);
			myTextEdit_2->setGeometry(20, 70, w - 650, 31);
			myTextEdit_3->setGeometry(20, 70, w - 650, 31);
			ui.pushButton_7->setGeometry(w - 681, 20, 51, 24);
			ui.pushButton_16->setGeometry(w-751, 20, 51, 24);
			ui.toolButton_17->setGeometry(w-681, 20, 51, 24);
			ui.pushButton_19->setGeometry(w-751, 20, 51, 24);
			ui.toolButton_18->setGeometry(w-681, 20, 51, 24);

			//ui.scrollArea->setGeometry(10, 110, w- 650, 300);
			ui.layoutWidget->setGeometry(QRect(30,  120, w-650, (m_todoNumber+1)*30));
			ui.layoutWidget_2->setGeometry(QRect(30, 120, w - 650, (m_shareNumber+1) * 30));
			
			ui.layoutWidget_3->setGeometry(QRect(30, (m_shareNumber + 5) * 30, w - 650, 40));
			ui.widget->setGeometry(QRect(30, (m_todoNumber + 5) * 30, w - 650, 40));
			if(m_show2%2==1)
				ui.verticalLayoutWidget->setGeometry(QRect(30, (m_shareNumber + 5) * 30+50, w - 650, (m_finishShare + 1) * 30));
			else if(m_show2%2==0){
				ui.verticalLayoutWidget->setGeometry(QRect(30, 50, w - 650, 1));
			}
			if(m_show%2==1)
				ui.verticalLayoutWidget_2->setGeometry(QRect(30, (m_todoNumber + 5) * 30 + 50, w - 650, (m_finishTodo + 1) * 30));
			else if(m_show%2==0){
				ui.verticalLayoutWidget_2->setGeometry(QRect(30, 50, w - 650, 1));
			}
			

			QRect rect = ui.verticalLayout->geometry();
			
		}
		else
			ui.frame_4->setGeometry(250, 60, 1, 1000);
	}
	else {
		ui.stackedWidget->setGeometry(260, 70, w - 250, h - 70);
		myTextEdit->setGeometry(20, 70, w - 300, 31);
		myTextEdit_2->setGeometry(20, 70, w - 300, 31);
		myTextEdit_3->setGeometry(20, 70, w - 300, 31);
		ui.pushButton_7->setGeometry(w - 331, 20, 51, 24);
		ui.pushButton_16->setGeometry(w - 401, 20, 51, 24);
		ui.toolButton_17->setGeometry(w - 331, 20, 51, 24);
		ui.pushButton_19->setGeometry(w - 401, 20, 51, 24);
		ui.toolButton_18->setGeometry(w - 331, 20, 51, 24);
		ui.layoutWidget->setGeometry(QRect(30, 120, w - 300, m_todoNumber * 30));
		ui.layoutWidget_2->setGeometry(QRect(30, 120, w - 300, m_shareNumber * 30));
		ui.widget->setGeometry(QRect(30, (m_todoNumber + 5) * 30, w - 300, 40));
		ui.layoutWidget_3->setGeometry(QRect(30, (m_shareNumber + 5) * 30, w - 300, 40));
		if (m_show2 % 2 == 1)
			ui.verticalLayoutWidget->setGeometry(QRect(30, (m_shareNumber + 5) * 30+50, w - 300, (m_finishShare + 1) * 30));
		else if (m_show2 % 2 == 0) {
			ui.verticalLayoutWidget->setGeometry(QRect(30, 50, w - 650, 1));
		}
		if (m_show % 2 == 1)
			ui.verticalLayoutWidget_2->setGeometry(QRect(30, (m_todoNumber + 5) * 30 + 50, w - 300, (m_finishTodo + 1) * 30));
		else if (m_show % 2 == 0) {
			ui.verticalLayoutWidget_2->setGeometry(QRect(30, 50, w - 650, 1));
		}
	}
}

//事件过滤器
bool Todo::eventFilter(QObject* watched, QEvent* event){
	//鼠标事件处理,实现输入框点击效果
	if (event->type() == QEvent::MouseButtonPress) {
		MyTextEdit* textEdit;
		if (watched == ui.page)textEdit = myTextEdit;
		else if (watched == ui.page_2)textEdit = myTextEdit_2;
		else if (watched == ui.page_3)textEdit = myTextEdit_3;
		else return false;
		textEdit->m_enterable = false;
		qDebug() << watched;
		qDebug() << "you can't enter"; 
		if (textEdit->toPlainText() == "") {
			textEdit->setText("+ 点击新建待办");
			textEdit->setStyleSheet("QTextEdit{color:rgb(75, 179, 175);border-color:rgb(210, 210, 210);border-width:1px;border-style:solid;}QTextEdit:hover{border-color:rgb(175, 175, 175);}");
			textEdit->setReadOnly(true);
			//return true;
		}
		else if (textEdit->toPlainText() != "" && textEdit->toPlainText() != "+ 点击新建待办") {
			textEdit->setStyleSheet("QTextEdit{border-color:rgb(210, 210, 210);border-width:1px;border-style:solid;}QTextEdit:hover{border-color:rgb(175, 175, 175);}");
			textEdit->setReadOnly(true);
			//return true;
		}
		return true;
	}

	//键盘回车事件处理
	if ((watched == myTextEdit || watched == myTextEdit_2 || watched == myTextEdit_3) && event->type() == QEvent::KeyPress) {
		QKeyEvent* keyEvent = static_cast<QKeyEvent*>(event);
		MyTextEdit* textEdit = static_cast<MyTextEdit*>(watched);
		if (textEdit->m_enterable && textEdit->toPlainText()!="" && keyEvent->key() == 16777220) {
			// 回车动作函数
			QString qstring = textEdit->toPlainText();
			qDebug() << "I have entered: " << qstring;
			
			//下面将qstring加入数据库
			QSqlQuery sqlQuery;
			sqlQuery.prepare("INSERT INTO list(type, value) VALUES(:type, :value)");
			sqlQuery.bindValue(":type", textEdit->m_type);
			sqlQuery.bindValue(":value", qstring);
			if (!sqlQuery.exec()) {
				qDebug() << __FUNCTION__ << "error" << m_db.lastError().text();
				qDebug() << sqlQuery.executedQuery();
			}
			readFromDB();
			initMyPage();
			//更新页面
			QResizeEvent* event1;
			resizeEvent(event1);
			
			textEdit->setText("");
			textEdit->setStyleSheet("color:rgb(0,0,0);border-color:rgb(75, 179, 175);border-width:1px;border-style:solid;");
			textEdit->m_enterable = true;
			return true;
		}
	}
	else if ((watched == ui.textEdit_18) && event->type() == QEvent::KeyPress) {
		QKeyEvent* keyEvent = static_cast<QKeyEvent*>(event);
		QTextEdit* textEdit = static_cast<QTextEdit*>(watched);
		if (keyEvent->key() == 16777220) {
			//m_currButton->deadTime->setText(textEdit->toPlainText());
			m_currButton->deadTime = textEdit->toPlainText();
			textEdit->setText(m_currButton->deadTime);
			m_sqlTable->setFilter(QString("value = '%1'").arg(m_currButton->text()));
			if (!m_sqlTable->select()) {
				qDebug() << "未找到目标数据";
				return false;
			}
			if (m_sqlTable->rowCount() > 0) {
				//m_sqlTable->setData(m_sqlTable->index(0, 3), m_currButton->deadTime->toPlainText());
				m_sqlTable->setData(m_sqlTable->index(0, 3), m_currButton->deadTime);
				if (!m_sqlTable->submitAll()) {
					qDebug() << "Failed to submit changes:" << m_sqlTable->lastError().text();
					return false;
				}
				//textEdit
			}
			return true;
		}
		return false;
	}
	else if (( watched == ui.textEdit_17) && event->type() == QEvent::KeyPress) {
		QKeyEvent* keyEvent = static_cast<QKeyEvent*>(event);
		QTextEdit* textEdit = static_cast<QTextEdit*>(watched);
		if (keyEvent->key() == 16777220) {
			//m_currButton->remind->setText(textEdit->toPlainText());
			m_currButton->remind = textEdit->toPlainText();
			textEdit->setText(m_currButton->remind);
			m_sqlTable->setFilter(QString("value = '%1'").arg(m_currButton->text()));
			if (!m_sqlTable->select()) {
				qDebug() << "未找到目标数据";
				return false;
			}
			if (m_sqlTable->rowCount() > 0) {
				//m_sqlTable->setData(m_sqlTable->index(0, 4), m_currButton->remind->toPlainText());
				m_sqlTable->setData(m_sqlTable->index(0, 4), m_currButton->remind);
				if (!m_sqlTable->submitAll()) {
					qDebug() << "Failed to submit changes:" << m_sqlTable->lastError().text();
					return false;
				}
			}
			return true;
		}
		return false;
	}
	else if (( watched == ui.textEdit_13) && event->type() == QEvent::KeyPress) {
		QKeyEvent* keyEvent = static_cast<QKeyEvent*>(event);
		QTextEdit* textEdit = static_cast<QTextEdit*>(watched);
		if (keyEvent->key() == 16777220) {
			//m_currButton->describe->setText(textEdit->toPlainText());
			m_currButton->describe = textEdit->toPlainText();
			textEdit->setText(m_currButton->describe);
			m_sqlTable->setFilter(QString("value = '%1'").arg(m_currButton->text()));
			if (!m_sqlTable->select()) {
				qDebug() << "未找到目标数据";
				return false;
			}
			if (m_sqlTable->rowCount() > 0) {
				//m_sqlTable->setData(m_sqlTable->index(0, 5), m_currButton->describe->toPlainText());
				m_sqlTable->setData(m_sqlTable->index(0, 5), m_currButton->describe);
				if (!m_sqlTable->submitAll()) {
					qDebug() << "Failed to submit changes:" << m_sqlTable->lastError().text();
					return false;
				}
			}
			return true;
		}
		return false;
	}
	else if ((watched == ui.textEdit_15) && event->type() == QEvent::KeyPress) {
		QKeyEvent* keyEvent = static_cast<QKeyEvent*>(event);
		QTextEdit* textEdit = static_cast<QTextEdit*>(watched);
		if (keyEvent->key() == 16777220) {
			//m_currButton->location->setText(textEdit->toPlainText());
			m_currButton->location = textEdit->toPlainText();
			textEdit->setText(m_currButton->location);
			m_sqlTable->setFilter(QString("value = '%1'").arg(m_currButton->text()));
			if (!m_sqlTable->select()) {
				qDebug() << "未找到目标数据";
				return false;
			}
			if (m_sqlTable->rowCount() > 0) {
				//m_sqlTable->setData(m_sqlTable->index(0, 6), m_currButton->location->toPlainText());
				m_sqlTable->setData(m_sqlTable->index(0, 6), m_currButton->location);
				if (!m_sqlTable->submitAll()) {
					qDebug() << "Failed to submit changes:" << m_sqlTable->lastError().text();
					return false;
				}
			}
			return true;
		}
		return false;
	}
	else if (( watched == ui.textEdit_14) && event->type() == QEvent::KeyPress) {
		QKeyEvent* keyEvent = static_cast<QKeyEvent*>(event);
		QTextEdit* textEdit = static_cast<QTextEdit*>(watched);
		if (keyEvent->key() == 16777220) {
			//m_currButton->note->setText(textEdit->toPlainText());
			m_currButton->note = textEdit->toPlainText();
			textEdit->setText(m_currButton->note);
			m_sqlTable->setFilter(QString("value = '%1'").arg(m_currButton->text()));
			if (!m_sqlTable->select()) {
				qDebug() << "未找到目标数据";
				return false;
			}
			if (m_sqlTable->rowCount() > 0) {
				//m_sqlTable->setData(m_sqlTable->index(0, 7), m_currButton->note->toPlainText());
				m_sqlTable->setData(m_sqlTable->index(0, 7), m_currButton->note);
				if (!m_sqlTable->submitAll()) {
					qDebug() << "Failed to submit changes:" << m_sqlTable->lastError().text();
					return false;
				}
			}
			return true;
		}
	return false;
	}

	return QWidget::eventFilter(watched, event);
}

//设置优先级菜单
void Todo::setPriority() {
	ui.toolButton_4->setPopupMode(QToolButton::InstantPopup);
	ui.toolButton_4->setText("无优先级");
	QMenu* menu = new QMenu(ui.stackedWidget_2);
	QAction* action1 = new QAction("!!! 高", ui.stackedWidget_2);
	QAction* action2 = new QAction("!! 中", ui.stackedWidget_2);
	QAction* action3 = new QAction("! 低", ui.stackedWidget_2);
	QAction* action4 = new QAction("无", ui.stackedWidget_2);
	QActionGroup* group = new QActionGroup(ui.stackedWidget_2);
	QList<QAction*>actionList;
	actionList = ui.stackedWidget_2->findChildren<QAction*>();
	foreach(QAction * action, actionList) {
		group->addAction(action);
		action->setCheckable(true);
		menu->addAction(action);
	}
	group->setExclusive(true);
	ui.toolButton_4->setMenu(menu);
	(void)connect(action1, &QAction::triggered, this, [=] {on_changePriority_clicked(action1); });
	(void)connect(action2, &QAction::triggered, this, [=] {on_changePriority_clicked(action2); });
	(void)connect(action3, &QAction::triggered, this, [=] {on_changePriority_clicked(action3); });
	(void)connect(action4, &QAction::triggered, this, [=] {on_changePriority_clicked(action4); });
}


//设置排序菜单
void Todo::setSort() {
	ui.toolButton_17->setPopupMode(QToolButton::InstantPopup);
	ui.toolButton_18->setPopupMode(QToolButton::InstantPopup);
	QMenu* menu = new QMenu(ui.toolButton_17);
	QAction* action1 = new QAction("到期时间排序", menu);
	QAction* action2 = new QAction("创建时间排序", menu);
	QAction* action3 = new QAction("优先级排序", menu);
	QActionGroup* group = new QActionGroup(menu);
	QList<QAction*>actionList;
	actionList = menu->findChildren<QAction*>();
	foreach(QAction * action, actionList) {
		action->setCheckable(true);
		menu->addAction(action);
		group->addAction(action);
	}
	group->setExclusive(true);

	QMenu* menu2 = new QMenu(ui.toolButton_18);
	QAction* action4 = new QAction("到期时间排序", menu2);
	QAction* action5 = new QAction("创建时间排序", menu2);
	QAction* action6 = new QAction("优先级排序", menu2);
	QActionGroup* group2 = new QActionGroup(menu2);
	QList<QAction*>actionList2;
	actionList2 = menu2->findChildren<QAction*>();
	foreach(QAction* action, actionList2) {
		action->setCheckable(true);
		menu2->addAction(action);
		group2->addAction(action);
	}
	group2->setExclusive(true);
	
	ui.toolButton_17->setMenu(menu);
	ui.toolButton_18->setMenu(menu2);
	(void)connect(action2, &QAction::triggered, this, &Todo::on_bornTime_sort);
	(void)connect(action3, &QAction::triggered, this, [=] {on_priority_sort(action3); });
	(void)connect(action1, &QAction::triggered, this, [=] {on_deadTime_sort(action1); });
	(void)connect(action5, &QAction::triggered, this, &Todo::on_bornTime_sort);
	(void)connect(action6, &QAction::triggered, this, [=] {on_priority_sort(action6); });
	(void)connect(action4, &QAction::triggered, this, [=] {on_deadTime_sort(action4); });
	
}

//关闭右侧菜单
void Todo::on_closeButton_clicked() {
	m_closeClicked = true;
	ui.stackedWidget_2->setGeometry(0, 0, 0, 0);
	ui.frame_4->setGeometry(0, 0, 0, 0);
	ui.stackedWidget->setGeometry(260, 70, this->width() - 250, 1000);
	
	myTextEdit->setGeometry(20, 70, this->width() - 300, 31);
	myTextEdit_2->setGeometry(20, 70, this->width() - 300, 31);
	myTextEdit_3->setGeometry(20, 70, this->width() - 300, 31);
	ui.pushButton_7->setGeometry(this->width() - 331, 20, 51, 24);
	ui.pushButton_16->setGeometry(this->width() - 401, 20, 51, 24);
	ui.toolButton_17->setGeometry(this->width() - 331, 20, 51, 24);
	ui.pushButton_19->setGeometry(this->width() - 401, 20, 51, 24);
	ui.toolButton_18->setGeometry(this->width() - 331, 20, 51, 24);
	
	ui.layoutWidget_3->setGeometry(QRect(30, (m_shareNumber + 5) * 30, this->width() - 300, 40));
	ui.widget->setGeometry(QRect(30, (m_todoNumber + 5) * 30, this->width() - 300, 40));
	ui.verticalLayoutWidget->setGeometry(QRect(30, (m_shareNumber + 5) * 30+50, this->width() - 300, (m_finishShare + 1) * 30));
	ui.verticalLayoutWidget_2->setGeometry(QRect(30, (m_todoNumber + 5) * 30 + 50, this->width() - 300, (m_finishTodo + 1) * 30));
}

//点击左侧按钮
void Todo::on_pushButton_clicked(QPushButton* button) {
	button->setProperty("clicked", true);
	button->style()->unpolish(button);
	button->style()->polish(button);

	m_lastClickedButton.front()->setProperty("clicked", false);
	m_lastClickedButton.front()->style()->unpolish(m_lastClickedButton.front());
	m_lastClickedButton.front()->style()->polish(m_lastClickedButton.front());


	m_lastClickedButton.pop_back();
	m_lastClickedButton.push_back(button);
}

//点击待办事件按钮
void Todo::on_myTodo_clicked(MyPushButton* button) {
	m_currButton = button;
	//button->name->setText(button->text());
	ui.textEdit_16->setText(button->text());
	QList<QAction*>actionList;
	actionList = ui.stackedWidget_2->findChildren<QAction*>();
	foreach(QAction * action, actionList) {
		action->setChecked(false);
	}
	//设置过滤条件
	m_sqlTable->setFilter(QString("value = '%1' and type = '%2'").arg(m_currButton->text(), m_currButton->type));
	if (!m_sqlTable->select()) {
		qDebug() << "未找到目标数据";
		return;
	}
	if (m_sqlTable->rowCount() > 0) {
		if (m_sqlTable->index(0, 2).data().toString() == "4")
			//button->priority->setText("!!! 高");
			ui.toolButton_4->setText("!!! 高");
		else if (m_sqlTable->index(0, 2).data().toString() == "3")
			//button->priority->setText("!! 中");
			ui.toolButton_4->setText("!! 中");
		else if (m_sqlTable->index(0, 2).data().toString() == "2")
			//button->priority->setText("! 低");
			ui.toolButton_4->setText("! 低");
		else
			//button->priority->setText("无优先级");
			ui.toolButton_4->setText("无优先级");
		ui.textEdit_18->setText(m_sqlTable->index(0, 3).data().toString());
		ui.textEdit_17->setText(m_sqlTable->index(0, 4).data().toString());
		ui.textEdit_13->setText(m_sqlTable->index(0, 5).data().toString());
		ui.textEdit_15->setText(m_sqlTable->index(0, 6).data().toString());
		ui.textEdit_14->setText(m_sqlTable->index(0, 7).data().toString());
		//若已完成
		if (m_sqlTable->index(0, 8).data().toString() != "0") {
			ui.pushButton_12->setStyleSheet("QPushButton{image:url(Resources/finish);border:none;}");
		}
		else {
			ui.pushButton_12->setStyleSheet("QPushButton{image:url(Resources/MyButton.png);border:none}");
		}
	}
}

//点击待完成清单
void Todo::connectMyButton() {
	//qDebug() << "this:             " << this;
	int i = 0;
	while (i < m_todoList.length()) {
		(void)connect(m_todoList[i], &MyPushButton::clicked, this, [=]() {on_myTodo_clicked(m_todoList[i]), ui.stackedWidget_2->setCurrentIndex(1); });
		i++;
	}
	i = 0;
	while (i < m_shareList.length()) {
		(void)connect(m_shareList[i], &MyPushButton::clicked, this, [=]() {on_myTodo_clicked(m_shareList[i]), ui.stackedWidget_2->setCurrentIndex(1); });
		i++;
	}
}

//修改名字
void Todo::on_changeName_clicked() {
	//设置过滤条件
	m_sqlTable->setFilter(QString("value = '%1' and type = '%2'").arg(m_currButton->text(), m_currButton->type));
	if (!m_sqlTable->select()) {
		qDebug() << "未找到目标数据";
		return;
	}
	if (m_sqlTable->rowCount() > 0) {
		m_sqlTable->setData(m_sqlTable->index(0, 1), ui.textEdit_16->toPlainText());
		if (!m_sqlTable->submitAll()) {
			qDebug() << "Failed to submit changes:" << m_sqlTable->lastError().text();
			return;
		}
	}
	m_currButton->setText(ui.textEdit_16->toPlainText());
}


//更改优先级
void Todo::on_changePriority_clicked(QAction* action) {
	m_currButton->priority = action->text();
	ui.toolButton_4->setText(action->text());
	//设置过滤条件
	m_sqlTable->setFilter(QString("value = '%1' and type = '%2'").arg(m_currButton->text(), m_currButton->type));
	if (!m_sqlTable->select()) {
		qDebug() << "未找到目标数据";
		return;
	}
	if (m_sqlTable->rowCount() > 0) {
		//m_sqlTable->setData(m_sqlTable->index(0, 2), m_currButton->priority->text());
		if(m_currButton->priority=="!!! 高")
			m_sqlTable->setData(m_sqlTable->index(0, 2), "4");
		else if(m_currButton->priority == "!! 中")
			m_sqlTable->setData(m_sqlTable->index(0, 2), "3");
		else if (m_currButton->priority == "! 低")
			m_sqlTable->setData(m_sqlTable->index(0, 2), "2");
		else if (m_currButton->priority == "无优先级")
			m_sqlTable->setData(m_sqlTable->index(0, 2), "1");
		if (!m_sqlTable->submitAll()) {
			qDebug() << "Failed to submit changes:" << m_sqlTable->lastError().text();
			return;
		}
	}
}

//点击完成按钮
void Todo::on_done_clicked() {
	if (!m_currButton->done) {
		m_currButton->done = true;
		ui.pushButton_12->setStyleSheet("QPushButton{image:url(Resources/finish);border:none;}");
		//设置过滤条件
		m_sqlTable->setFilter(QString("value = '%1' and type = '%2'").arg(m_currButton->text(), m_currButton->type));
		if (!m_sqlTable->select()) {
			qDebug() << "未找到目标数据";
			return;
		}
		if (m_sqlTable->rowCount() > 0) {
			if (m_sqlTable->index(0, 0).data().toString() == "我的待办") {
				ui.verticalLayout->removeWidget(m_currButton);
				addToLayout(m_currButton, ui.verticalLayout_4);
			}
			else if (m_sqlTable->index(0, 0).data().toString() == "共享分组") {
				ui.verticalLayout_2->removeWidget(m_currButton);
				addToLayout(m_currButton, ui.verticalLayout_3);
			}
			m_sqlTable->setData(m_sqlTable->index(0, 8), 1);
			if (!m_sqlTable->submitAll()) {
				qDebug() << "Failed to submit changes:" << m_sqlTable->lastError().text();
				return;
			}
			//m_currButton->setIcon(QIcon(":/Todo/finish.png"));
			//m_currButton->setStyleSheet("QPushButton{icon:url(Resources/finish.png)}");
			QString styleSheet = "QPushButton{icon:url(Resources/finish.png)}";
			m_currButton->setStyleSheet(m_currButton->m_styleSheet + styleSheet);
		}
	}
	else {
		m_currButton->done = false;
		ui.pushButton_12->setStyleSheet("QPushButton{image:url(Resources/MyButton);border:none;}");
		//设置过滤条件
		m_sqlTable->setFilter(QString("value = '%1' and type = '%2'").arg(m_currButton->text(), m_currButton->type));
		if (!m_sqlTable->select()) {
			qDebug() << "未找到目标数据";
			return;
		}
		if (m_sqlTable->rowCount() > 0) {
			if (m_sqlTable->index(0, 0).data().toString() == "我的待办") {
				m_todoNumber++;
				m_finishTodo--;
				ui.verticalLayout_4->removeWidget(m_currButton);
				addToLayout(m_currButton, ui.verticalLayout);
				
			}
			else if (m_sqlTable->index(0, 0).data().toString() == "共享分组") {
				m_shareNumber++;
				m_finishTodo--;
				ui.verticalLayout_3->removeWidget(m_currButton);
				addToLayout(m_currButton, ui.verticalLayout_2);
			}
			m_sqlTable->setData(m_sqlTable->index(0, 8), 0);
			if (!m_sqlTable->submitAll()) {
				qDebug() << "Failed to submit changes:" << m_sqlTable->lastError().text();
				return;
			}
			//m_currButton->setIcon(QIcon(":/Todo/MyButton.png"));
			//m_currButton->setStyleSheet("QPushButton{icon:url(Resources/MyButton.png)}");
			QString styleSheet = "QPushButton{icon:url(Resources/MyButton.png)}";
			m_currButton->setStyleSheet(m_currButton->m_styleSheet + styleSheet);
		}
	}
	readFromDB();
	initMyPage();
}

void Todo::on_bornTime_sort() {
	initMyPage();
	readFromDB();
}

void Todo::on_deadTime_sort(QAction* action) {
	QVector<MyPushButton* >n_todoList;
	if (qobject_cast<QToolButton*>(qobject_cast<QMenu*>(action->parent())->parent()) == ui.toolButton_17) {
		int i = 0;
		int length = m_todoList.length();
		qDebug() << length;
		while (i < length) {
			if (m_todoList[i]->done == false) {
				//qDebug() << m_todoList[i]->name;
				n_todoList.push_back(m_todoList[i]);
			}
			i++;
		}
	}
	else if (qobject_cast<QToolButton*>(qobject_cast<QMenu*>(action->parent())->parent()) == ui.toolButton_18) {
		int i = 0;
		int length = m_todoList.length();
		qDebug() << length;
		while (i < length) {
			if (m_todoList[i]->done == false) {
				//qDebug() << m_todoList[i]->name;
				n_todoList.push_back(m_todoList[i]);
			}
			i++;
		}
	}
		
	std::sort(n_todoList.begin(), n_todoList.end(), [](const MyPushButton* a, const MyPushButton* b) {return a->deadTime < b->deadTime; });


	while (QLayoutItem* item = ui.verticalLayout->takeAt(0)) {
		ui.verticalLayout->removeItem(item);
	}
	int i = 0;
	while (i < n_todoList.length()) {
		n_todoList[i]->setParent(ui.layoutWidget);
		addToLayout(n_todoList[i], ui.verticalLayout);
		qDebug() << n_todoList[i]->name;
		i++;
	}

	
	QResizeEvent* event;
	resizeEvent(event);
	/*qDebug() << qobject_cast<QToolButton*>(qobject_cast<QMenu*>(action->parent())->parent());*/
}

void Todo::on_priority_sort(QAction* action) {
	QVector<MyPushButton* >n_todoList;
	if (qobject_cast<QToolButton*>(qobject_cast<QMenu*>(action->parent())->parent()) == ui.toolButton_17) {
		int i = 0;
		int length = m_todoList.length();
		qDebug() << length;
		while (i < length) {
			if (m_todoList[i]->done == false) {
				//qDebug() << m_todoList[i]->name;
				n_todoList.push_back(m_todoList[i]);
			}
			i++;
		}
	}
	else if (qobject_cast<QToolButton*>(qobject_cast<QMenu*>(action->parent())->parent()) == ui.toolButton_18) {
		int i = 0;
		int length = m_todoList.length();
		qDebug() << length;
		while (i < length) {
			if (m_todoList[i]->done == false) {
				//qDebug() << m_todoList[i]->name;
				n_todoList.push_back(m_todoList[i]);
			}
			i++;
		}
	}

	std::sort(n_todoList.begin(), n_todoList.end(), [](const MyPushButton* a, const MyPushButton* b) {return a->m_priority > b->m_priority; });


	while (QLayoutItem* item = ui.verticalLayout->takeAt(0)) {
		ui.verticalLayout->removeItem(item);
	}
	int i = 0;
	while (i < n_todoList.length()) {
		n_todoList[i]->setParent(ui.layoutWidget);
		addToLayout(n_todoList[i], ui.verticalLayout);
		qDebug() << n_todoList[i]->m_priority;
		i++;
	}
	QResizeEvent* event;
	resizeEvent(event);
}

void Todo::on_showButton_clicked(QPushButton* button) {
	QResizeEvent* event;
	if (button == ui.pushButton_4) {
		m_show++;
		resizeEvent(event);
	}
	else if (button == ui.pushButton_5) {
		m_show2++;
		resizeEvent(event);
	}
	if (m_show % 2 == 0)
		ui.pushButton_4->setText("显示已完成");
	else
		ui.pushButton_4->setText("隐藏已完成");
	if (m_show2 % 2 == 0)
		ui.pushButton_5->setText("显示已完成");
	else
		ui.pushButton_5->setText("隐藏已完成");
}




