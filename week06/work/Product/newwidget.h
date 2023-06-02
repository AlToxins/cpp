#pragma once
#include <QtWidgets/QMainWindow>
#include "ui_NewWindow.h"
#include<qsqldatabase.h>
#include<qsqlquery.h>
#include<qsqlerror.h>
#include<qsqltablemodel.h>

class NewWidget : public QMainWindow {
	Q_OBJECT
public:
	NewWidget(QWidget* parent = Q_NULLPTR);
	~NewWidget();
	void initDataBase();
	void initTableView();
private:
	Ui::MainWindow ui;
	QSqlDatabase m_db;
	QSqlTableModel* m_sqlTableModel;
	int m_selledNumber;	//¶©µ¥ºÅ
	
private slots:
	void on_fuzhuang_triggered();
	void on_shipin_triggered();
	void on_ruku_clicked();
	void on_qingkong_clicked();
	void on_fuzhuang2_triggered();
	void on_shipin2_triggered();
	void on_ok_clicked();
	void on_shouchu_clicked();
	void on_xiadan_clicked();
	void on_spinBox_clicked();
};