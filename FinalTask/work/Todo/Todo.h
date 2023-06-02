#pragma once

#include <QtWidgets/QMainWindow>
#include<qpushbutton.h>
#include "ui_Todo.h"
#include<qlist.h>
#include"mytextedit.h"
#include"mypushbutton.h"
#include<qsqldatabase.h>
#include<qsqlerror.h>
#include<qsqlquery.h>
#include<qsqltablemodel.h>
#include<qvector.h>
#include<qaction.h>



class Todo : public QMainWindow
{
	Q_OBJECT

public:
	Todo(QWidget *parent = Q_NULLPTR);
	void resizeEvent(QResizeEvent* event);
	bool eventFilter(QObject* watched, QEvent* event) override;
	//bool m_closeClicked;
	void initDatabase();
	void readFromDB();
	void setPriority();	//设置优先级菜单
	void setSort();		//设置排序方式菜单
	void quickSort(QString* mat, int start, int end);
	void addToLayout(MyPushButton* button, QVBoxLayout* layout, QSqlQuery query);
	void addToLayout(MyPushButton* button, QVBoxLayout* layout);
	void initMyPage();
	void connectMyButton();	//根据vector中的索引连接对应的button
	void on_showButton_clicked(QPushButton* button);

private:
	Ui::TodoClass ui;
	QList<QPushButton*>m_lastClickedButton;
	QList<QTextEdit* >m_textEditList;
	MyTextEdit* myTextEdit;
	MyTextEdit* myTextEdit_2;
	MyTextEdit* myTextEdit_3;
	QSqlDatabase m_db;
	QSqlTableModel* m_sqlTable;
	int m_todoNumber = 0;
	int m_shareNumber = 0;
	int m_finishTodo = 0;
	int m_finishShare = 0;
	QVector<MyPushButton*>m_todoList;	//待办事件按钮
	QVector<MyPushButton*>m_shareList;	//共享事件按钮
	QVector<MyPushButton*>m_allList;	//所有事件按钮
	MyPushButton* m_currButton;
	bool m_closeClicked;	
	int m_show;	//当show为偶数时隐藏已完成
	int m_show2;
	
	
private slots:
	void on_pushButton_clicked(QPushButton* button);
	void on_closeButton_clicked();
	void on_myTodo_clicked(MyPushButton* button);
	void on_changeName_clicked();
	void on_changePriority_clicked(QAction* action);
	void on_deadTime_sort(QAction* action);
	void on_bornTime_sort();
	void on_priority_sort(QAction* action);
	void on_done_clicked();
};
