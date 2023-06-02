#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Product.h"
#include"newwidget.h"

class Product : public QMainWindow
{
	Q_OBJECT

public:
	Product(QWidget *parent = Q_NULLPTR);

private:
	Ui::ProductClass ui;
	NewWidget* newWidget;
	QString username;
	QString password;

private slots:
	bool on_login_clicked();

};
